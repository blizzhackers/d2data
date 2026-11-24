/**
 * Sorceress leveling optimizer.
 *
 *   sorcbuild <level> [options]          Best build and areas for experience per mana, as JSON.
 *   sorcbuild skill <name> <hard> [Skill=N ...] [options]
 *                                        Damage of one skill for an allocation.
 *   sorcbuild monster <id> [options]     Hit points, EHP and experience of a monster.
 *
 * Compiles with:
 *   g++ sorcbuild.cpp sorcskills.cpp monsters.cpp txtrotw.cpp -o sorcbuild -std=c++17 -O3 -pthread
 *
 * See sorcbuild.md for the model and its assumptions.
 */

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "monsters.h"
#include "sorcskills.h"

namespace {

    struct Options {
        std::vector<std::string> positional;
        std::map<std::string, std::string> values;
        std::vector<std::string> flags;

        bool has(const std::string& k) const {
            return values.count(k) || std::find(flags.begin(), flags.end(), k) != flags.end();
        }
        double num(const std::string& k, double fallback) const {
            auto it = values.find(k);
            return it == values.end() ? fallback : std::atof(it->second.c_str());
        }
        std::string str(const std::string& k, const std::string& fallback = "") const {
            auto it = values.find(k);
            return it == values.end() ? fallback : it->second;
        }
    };

    const double kNoSynergy[2] = { 0, 0 };

    const std::vector<std::string> kFlagOptions = { "--allow-thunderstorm", "--online", "--epm", "--rush", "--fire", "--lightning", "--cold", "--progression", "--hybrid", "--help" };

    // Skill trees a build may spend points in: --fire, --lightning, --cold,
    // any combination; none means all three. Indexed like SkillInfo::tree.
    using Trees = std::array<bool, 3>;

    // Progression gates. The Ancients at the Arreat Summit let you into the
    // Worldstone Keep at level 20 in Normal, 40 in Nightmare and 60 in Hell,
    // and beating Baal there opens the next difficulty and the Cow Level.
    // Without --rush, an area is only considered if it is reachable that way.
    bool reachable(const Mon::Area& area, int clvl) {
        static const int ancients[3] = { 20, 40, 60 };
        int d = std::clamp(area.difficulty, 0, 2);
        if (d > 0 && clvl < ancients[d - 1]) {
            return false; // The previous difficulty's Ancients come first.
        }
        bool pastAncients = (area.id >= 128 && area.id <= 132) || area.id == 39; // Worldstone Keep to Baal; the Cow Level.
        if (pastAncients && clvl < ancients[d]) {
            return false;
        }
        bool pandemonium = area.id >= 133 && area.id <= 136; // Uber areas exist only in Hell.
        return !pandemonium || d == Mon::Hell;
    }

    Options parseArgs(int argc, char* argv[]) {
        Options o;
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            if (a.rfind("--", 0) == 0) {
                size_t eq = a.find('=');
                if (eq != std::string::npos) {
                    o.values[a.substr(0, eq)] = a.substr(eq + 1);
                }
                else if (std::find(kFlagOptions.begin(), kFlagOptions.end(), a) != kFlagOptions.end() || i + 1 >= argc) {
                    o.flags.push_back(a);
                }
                else {
                    o.values[a] = argv[++i];
                }
            }
            else {
                o.positional.push_back(a);
            }
        }
        return o;
    }

    void usage(const char* self) {
        std::cerr <<
            "Usage:\n"
            "  " << self << " <level> [options]\n"
            "      Best sorceress build at <level> and the areas with the most experience per mana, as JSON.\n"
            "  " << self << " skill \"<skill>\" <hard points> [\"<Skill>=<points>\" ...] [options]\n"
            "      Damage, mana and per-cast pack damage for one skill and allocation.\n"
            "  " << self << " monster <monstats id> [--diff normal|nightmare|hell] [--mlvl N]\n"
            "                [--quality normal|champion|unique|minion|superunique] [--clvl N] [--pierce N]\n"
            "      Hit points, resistances, EHP per element and experience.\n"
            "\n"
            "Character:\n"
            "  --skills N  --fire-skills N  --lightning-skills N  --cold-skills N   Bonus skill levels.\n"
            "  --quest-skills N     Extra hard skill points (quests).\n"
            "  --players N          Players setting (default 1).\n"
            "  --online             Multiplayer game: Hell monsters use monlvl.txt L-HP (single player uses HP).\n"
            "  --fcr N              Faster cast rate (default 37).\n"
            "Optimizer:\n"
            "  --top N              Areas to list (default 5).\n"
            "  --skill \"<name>\"     Only consider this main skill.\n"
            "  --fire --lightning --cold  Only spend points in these trees (any combination; default all).\n"
            "  --require \"A,B\"      Every build must put a point in these skills (and their prerequisites).\n"
            "  --prev \"<build>\"     The previous level's build, as printed after \"Points:\"; no point may be removed.\n"
            "  --allow-thunderstorm Let Thunder Storm be the main skill.\n"
            "  --hybrid, --progression\n"
            "                       (Same thing.) Builds must be able to kill what progression needs\n"
            "                       (Travincal's Council, Chaos Sanctuary, the Throne and Baal's waves), and\n"
            "                       two main skills cast together are tried too: different elements, one\n"
            "                       timed (cooldown, summon, Thunder Storm) with one that isn't, or Thunder\n"
            "                       Storm with anything (--hybrid-step N: point budget step, default 1).\n"
            "  --epm                Rank by experience per mana instead of per second.\n"
            "  --rush               Consider every area, ignoring the level 20/40/60 Ancients gates.\n"
            "Model (see sorcbuild.md):\n"
            "  --dwell S  --trail S  --pack-area A  --cast-distance D  --cb-hit P\n"
            "  --hydra-interval F  --uptime P  --teleport-range D\n";
    }

    Sorc::Assumptions assumptionsFrom(const Options& o) {
        Sorc::Assumptions a;
        a.fcr = static_cast<int>(o.num("--fcr", a.fcr));
        a.dwell = o.num("--dwell", a.dwell);
        a.trail = o.num("--trail", a.trail);
        a.packAreaPerMonster = o.num("--pack-area", a.packAreaPerMonster);
        a.castDistance = o.num("--cast-distance", a.castDistance);
        a.teleportRange = o.num("--teleport-range", a.teleportRange);
        a.chargedBoltHit = o.num("--cb-hit", a.chargedBoltHit);
        a.hydraInterval = o.num("--hydra-interval", a.hydraInterval);
        a.summonUptime = o.num("--uptime", a.summonUptime);
        a.thunderStorm = o.has("--allow-thunderstorm");
        return a;
    }

    Sorc::SkillBonuses bonusesFrom(const Options& o) {
        Sorc::SkillBonuses b;
        b.all = static_cast<int>(o.num("--skills", 0));
        b.fire = static_cast<int>(o.num("--fire-skills", 0));
        b.lightning = static_cast<int>(o.num("--lightning-skills", 0));
        b.cold = static_cast<int>(o.num("--cold-skills", 0));
        return b;
    }

    std::string fmt(double v, int decimals = 0) {
        char buf[64];
        std::snprintf(buf, sizeof buf, "%.*f", decimals, v);
        return buf;
    }

    std::string pad(std::string s, size_t w) {
        if (s.size() < w) {
            s.append(w - s.size(), ' ');
        }
        return s;
    }

    // Minimal pretty-printing JSON writer.
    class Json {
    public:
        explicit Json(std::ostream& out) : out(out) {}

        Json& begin(char bracket) {
            item();
            out << bracket;
            empty.push_back(true);
            return *this;
        }

        Json& end(char bracket) {
            bool wasEmpty = empty.back();
            empty.pop_back();
            if (!wasEmpty) {
                newline();
            }
            out << bracket;
            return *this;
        }

        Json& key(const std::string& k) {
            item();
            string(k);
            out << ": ";
            afterKey = true;
            return *this;
        }

        Json& value(const std::string& v) { item(); string(v); return *this; }
        Json& value(const char* v) { return value(std::string(v)); }
        Json& value(bool v) { item(); out << (v ? "true" : "false"); return *this; }
        Json& value(int v) { item(); out << v; return *this; }
        Json& value(int64_t v) { item(); out << v; return *this; }

        Json& value(double v) {
            item();
            if (!std::isfinite(v)) {
                out << "null";
                return *this;
            }
            char buf[64];
            std::snprintf(buf, sizeof buf, "%.4f", v);
            std::string n = buf;
            n.erase(n.find_last_not_of('0') + 1);
            if (n.back() == '.') {
                n.pop_back();
            }
            out << (n == "-0" ? "0" : n);
            return *this;
        }

    private:
        std::ostream& out;
        std::vector<bool> empty;
        bool afterKey = false;

        void newline() {
            out << "\n" << std::string(empty.size() * 2, ' ');
        }

        // Separator and indentation before a value or key.
        void item() {
            if (afterKey) {
                afterKey = false;
                return;
            }
            if (!empty.empty()) {
                if (!empty.back()) {
                    out << ",";
                }
                empty.back() = false;
                newline();
            }
        }

        void string(const std::string& v) {
            out << '"';
            for (char ch : v) {
                switch (ch) {
                    case '"': out << "\\\""; break;
                    case '\\': out << "\\\\"; break;
                    case '\n': out << "\\n"; break;
                    case '\t': out << "\\t"; break;
                    default:
                        if (static_cast<unsigned char>(ch) < 0x20) {
                            char buf[8];
                            std::snprintf(buf, sizeof buf, "\\u%04x", ch);
                            out << buf;
                        }
                        else {
                            out << ch;
                        }
                }
            }
            out << '"';
        }
    };

    // ------------------------------------------------------------------
    // Area scoring
    // ------------------------------------------------------------------

    struct MemberStat {
        double count = 0;
        double hp = 0;
        int res[3] = { 0, 0, 0 };
        double exp = 0; // After the level penalty for the character.
        bool box = false; // 3x3 collision footprint (monstats2 SizeX 3).
    };

    struct PackStat {
        double packs = 0;
        double size = 1;
        std::vector<MemberStat> members;
    };

    struct AreaStat {
        int area = -1;
        double travelRun = 0;      // Seconds from the waypoint and around every pack, on foot.
        double travelTeleport = 0; // The same with Teleport.
        double approachRun = 0;    // Of which, from the nearest waypoint to the area, on foot.
        double approachTeleport = 0;
        double possible = 0;       // Experience if every monster could be killed.
        std::vector<PackStat> packs;
    };

    // runSpeed and teleportSpeed are in subtiles per second. The route
    // through N packs spread over A walkable subtiles is the expected
    // shortest tour through N random points, 0.7124 * sqrt(N * A).
    std::vector<AreaStat> prepareAreas(const Mon::Library& mon, int clvl, int players, double runSpeed, double teleportSpeed) {
        std::vector<AreaStat> out;
        const auto& areas = mon.areas();
        for (size_t i = 0; i < areas.size(); i++) {
            AreaStat as;
            as.area = static_cast<int>(i);
            double route = 0.7124 * std::sqrt(areas[i].packCount * areas[i].walkable);
            as.approachRun = mon.approachSeconds(areas[i].id, runSpeed, 0);
            as.approachTeleport = mon.approachSeconds(areas[i].id, runSpeed, teleportSpeed);
            as.travelRun = as.approachRun + (runSpeed > 0 ? route / runSpeed : 0);
            as.travelTeleport = as.approachTeleport + (teleportSpeed > 0 ? route / teleportSpeed : route / std::max(runSpeed, 1e-9));
            for (const auto& p : areas[i].packs) {
                PackStat ps;
                ps.packs = p.packs;
                ps.size = p.size;
                for (const auto& m : p.members) {
                    if (!mon.killable(m.monster)) {
                        continue;
                    }
                    MemberStat ms;
                    ms.count = m.count;
                    ms.hp = mon.hp(m.monster, areas[i].difficulty, m.mlvl, m.quality, players);
                    for (int e = 0; e < 3; e++) {
                        ms.res[e] = mon.resist(m.monster, areas[i].difficulty, e);
                    }
                    ms.exp = mon.experience(m.monster, areas[i].difficulty, m.mlvl, m.quality, players) * mon.expShare(clvl, m.mlvl);
                    ms.box = mon.sizeX(m.monster) >= 3;
                    ps.members.push_back(ms);
                }
                if (!ps.members.empty()) {
                    for (const auto& m : ps.members) {
                        as.possible += ps.packs * m.count * m.exp;
                    }
                    as.packs.push_back(std::move(ps));
                }
            }
            out.push_back(std::move(as));
        }
        return out;
    }

    struct Score {
        int area = -1;
        double exp = 0;      // Experience per full clear.
        double mana = 0;     // Mana per full clear.
        double seconds = 0;  // Combat time per full clear.
        double travel = 0;   // Time moving per full clear: from the waypoint, then between packs.
        double approach = 0; // Of which, from the waypoint to the area.
        double possible = 0; // Experience if every monster could be killed.
        double perMana() const { return mana > 0 ? exp / mana : 0; }
        double perSecond() const { return seconds + travel > 0 ? exp / (seconds + travel) : 0; }
        // The objective: experience per second, or per mana with --epm.
        double value(bool epm) const { return epm ? perMana() : perSecond(); }
    };

    // Casts to kill a pack. Each cast deals `aimed` to the monster you aim at
    // and `other` to every other member. Group g has c members needing h
    // damage each. Every cast lands on `other` members, so after T casts a
    // member has taken other*T; if that's short of h, it needs targeted casts
    // of its own: t = (h - other*T) / (aimed - other), and at least `unit`,
    // the smallest share of a cast you can spend (1 for whole casts, less
    // for channeling). T is the sum of the targeted casts. A pack always
    // costs at least one unit.
    double castsToKill(const std::vector<std::pair<double, double>>& groups, double aimed, double other, double unit) {
        if (aimed <= 0 || groups.empty()) {
            return 0;
        }
        double floor = unit;
        double hmax = 0;
        for (const auto& [c, h] : groups) {
            floor = std::max(floor, h / aimed * std::min(1.0, c));
            hmax = std::max(hmax, h);
        }
        if (other >= aimed * (1 - 1e-9)) {
            return std::max(unit, hmax / aimed);
        }

        // T solves T = f(T), the targeted casts the pack still needs after T
        // casts. Each group is long (need >= gap*unit: (h - other*T)/gap
        // casts), short (one unit) or dead (need <= 0), so f is piecewise
        // linear and non-increasing, breaking where a group turns short or
        // dead. Walk the pieces in order: the root is either inside a piece
        // or at a breakpoint where f drops below T.
        double gap = aimed - other;
        std::vector<double> breaks = { 0.0 };
        if (other > 0) {
            for (const auto& [c, h] : groups) {
                breaks.push_back((h - gap * unit) / other); // Long -> short.
                breaks.push_back(h / other);                // Short -> dead.
            }
        }
        std::sort(breaks.begin(), breaks.end());
        for (size_t i = 0; i < breaks.size(); i++) {
            double lo = breaks[i];
            double hi = i + 1 < breaks.size() ? breaks[i + 1] : HUGE_VAL;
            if (lo < 0 || hi <= lo) {
                continue;
            }
            // f(T) = a - b*T on (lo, hi); classify groups at its midpoint.
            double at = std::isfinite(hi) ? (lo + hi) / 2 : lo + 1;
            double a = 0;
            double b = 0;
            for (const auto& [c, h] : groups) {
                double need = h - other * at;
                if (need <= 0) {
                    continue;
                }
                if (need < gap * unit) {
                    a += c * unit;
                }
                else {
                    a += c * h / gap;
                    b += c * other / gap;
                }
            }
            double t = a / (1 + b);
            if (t < lo) {
                return std::max(lo, floor); // f dropped below T at this breakpoint.
            }
            if (t < hi) {
                return std::max(t, floor);
            }
        }
        return floor;
    }

    // Cost of one fight, per pack: combat time, mana and experience gained.
    struct Part {
        double seconds = 0;
        double mana = 0;
        double exp = 0;
        void add(const Part& o, double times = 1) {
            seconds += o.seconds * times;
            mana += o.mana * times;
            exp += o.exp * times;
        }
    };

    // What it costs `d` to kill the members of a pack that `want` picks and
    // `d` can damage. The fight's geometry uses the whole pack, or only the
    // picked members when the rest are already dead (`alone`).
    template <class Want>
    Part packCost(const Sorc::Library& lib, const Sorc::Damage& d, const Sorc::Assumptions& a, const PackStat& p, Want want, bool alone) {
        Part out;
        double count = 0;
        for (const auto& m : p.members) {
            int res = d.element < 3 ? m.res[d.element] : 0;
            if (res < 100 && want(m)) {
                count += m.count;
            }
        }
        if (count <= 0) {
            return out;
        }
        Sorc::PackHit h = lib.packHit(d, alone ? std::max(1.0, count) : p.size, a);
        if (h.aimed <= 0) {
            return out;
        }
        std::vector<std::pair<double, double>> groups;
        for (const auto& m : p.members) {
            int res = d.element < 3 ? m.res[d.element] : 0;
            if (res >= 100 || !want(m)) {
                continue; // Immune: skipped, no experience.
            }
            int effective = std::max(-100, res - d.pierce);
            double ehp = m.hp * 100.0 / (100.0 - effective);
            // Geometry hits 3x3 monsters harder; fold that into what they need.
            groups.emplace_back(m.count, (ehp + h.overshoot) / (m.box ? h.boxScale : 1.0));
            out.exp += m.count * m.exp;
        }
        double casts = castsToKill(groups, h.aimed, h.other, d.minCast);
        out.mana = casts * d.mana + d.packMana;
        // The last cast still has to land: Frozen Orb's flight, time in a wall, Meteor's fall.
        out.seconds = (casts - 1) * d.secondsPerCast + d.deliverySeconds + d.packSeconds;
        return out;
    }

    Score scoreArea(const Sorc::Library& lib, const Sorc::Damage& d, const AreaStat& as, const Sorc::Assumptions& a, bool teleport) {
        Score s;
        s.area = as.area;
        s.travel = teleport ? as.travelTeleport : as.travelRun;
        s.approach = teleport ? as.approachTeleport : as.approachRun;
        Part total;
        for (const auto& p : as.packs) {
            for (const auto& m : p.members) {
                s.possible += p.packs * m.count * m.exp;
            }
            total.add(packCost(lib, d, a, p, [](const MemberStat&) { return true; }, false), p.packs);
        }
        s.exp = total.exp;
        s.mana = total.mana;
        s.seconds = total.seconds;
        return s;
    }

    // Several areas taken together, as one long run.
    void accumulate(Score& total, const Score& sc) {
        total.exp += sc.exp;
        total.mana += sc.mana;
        total.seconds += sc.seconds;
        total.travel += sc.travel;
        total.approach += sc.approach;
        total.possible += sc.possible;
    }

    // What a build is judged by: with `focus` (positions in `areas`), clearing
    // those areas together; otherwise its best single area.
    template <class ScoreOf>
    Score judge(const std::vector<AreaStat>& areas, const std::vector<size_t>& focus, bool epm, ScoreOf scoreOf) {
        Score best;
        if (!focus.empty()) {
            best.area = -1;
            for (size_t pos : focus) {
                accumulate(best, scoreOf(areas[pos]));
            }
            return best;
        }
        for (const auto& as : areas) {
            Score sc = scoreOf(as);
            if (sc.value(epm) > best.value(epm)) {
                best = sc;
            }
        }
        return best;
    }

    std::vector<Score> scoreAll(const Sorc::Library& lib, const Sorc::Damage& d, const std::vector<AreaStat>& areas, const Sorc::Assumptions& a,
                                bool teleport, bool epm) {
        std::vector<Score> out;
        out.reserve(areas.size());
        for (const auto& as : areas) {
            out.push_back(scoreArea(lib, d, as, a, teleport));
        }
        std::sort(out.begin(), out.end(), [&](const Score& x, const Score& y) { return x.value(epm) > y.value(epm); });
        return out;
    }

    // ------------------------------------------------------------------
    // Optimizer
    // ------------------------------------------------------------------

    struct Plan {
        int skill = -1;
        int skill2 = -1;            // Hybrid: the skill that cleans up what the first is immune to.
        std::vector<int> hard;
        Sorc::Damage damage;
        Sorc::Damage damage2;
        Score best;
        std::vector<Score> ranked;  // Hybrid: every area, best first.
        int unspent = 0;
        bool teleport = false;
        bool valid = false;
    };

    // A candidate allocation for one main skill, summarized by its effect:
    // damage multipliers for each component and cold pierce.
    struct Candidate {
        double effect[3] = { 0, 0, 0 };
        int used = 0;
        std::vector<int> hard;
    };

    bool dominates(const Candidate& a, const Candidate& b) {
        bool better = false;
        for (int i = 0; i < 3; i++) {
            if (a.effect[i] < b.effect[i] - 1e-9) {
                return false;
            }
            if (a.effect[i] > b.effect[i] + 1e-9) {
                better = true;
            }
        }
        return better || a.used <= b.used;
    }

    void paretoAdd(std::vector<Candidate>& list, Candidate c) {
        for (const auto& e : list) {
            if (dominates(e, c)) {
                return;
            }
        }
        list.erase(std::remove_if(list.begin(), list.end(), [&](const Candidate& e) { return dominates(c, e); }), list.end());
        list.push_back(std::move(c));
    }

    // Synergy points beyond the first in each active synergy skill.
    struct SynPoint {
        double v[2] = { 0, 0 };
        std::vector<int> extra;
    };

    bool synDominates(const SynPoint& a, const SynPoint& b) {
        return a.v[0] >= b.v[0] - 1e-9 && a.v[1] >= b.v[1] - 1e-9;
    }

    void synAdd(std::vector<SynPoint>& list, SynPoint p) {
        for (const auto& e : list) {
            if (synDominates(e, p)) {
                return;
            }
        }
        list.erase(std::remove_if(list.begin(), list.end(), [&](const SynPoint& e) { return synDominates(p, e); }), list.end());
        list.push_back(std::move(p));
    }

    Plan optimizeSkill(const Sorc::Library& lib, int s, int clvl, int budget, const Sorc::SkillBonuses& bonus,
                       const Sorc::Assumptions& a, const std::vector<AreaStat>& areas, const std::vector<int>& required,
                       const std::vector<int>& floorPoints, bool epm, int teleportSkill, const Trees& trees,
                       const std::vector<size_t>& focus) {
        Plan plan;
        const Sorc::SkillInfo& info = lib.skill(s);
        // Skills outside the allowed trees get no points beyond what
        // --prev and --require already put in them.
        auto cap = [&](int x) {
            int c = std::clamp(clvl - lib.skill(x).reqlevel + 1, 0, 20);
            return trees[lib.skill(x).tree] ? c : std::min(c, std::max(floorPoints[x], 1));
        };
        if (cap(s) < 1) {
            return plan;
        }
        int m = info.mastery;

        // Hard points a skill in the build keeps: the previous build's, and at least one.
        auto keep = [&](int x) { return std::max(1, floorPoints[x]); };
        auto include = [&](std::vector<int>& set, int skill) {
            for (int x : lib.closure(skill)) {
                if (std::find(set.begin(), set.end(), x) == set.end()) {
                    set.push_back(x);
                }
            }
        };
        // Points a set of skills fixes, apart from the main skill and its
        // mastery, whose levels are chosen below.
        auto fixedCost = [&](const std::vector<int>& set) {
            int cost = 0;
            for (int x : set) {
                if (x != s && x != m) {
                    cost += keep(x);
                }
            }
            return cost;
        };

        // The main skill's prerequisites, required skills, and everything in the previous build.
        std::vector<int> q;
        include(q, s);
        for (int r : required) {
            include(q, r);
        }
        for (int x = 0; x < lib.size(); x++) {
            if (floorPoints[x] > 0) {
                include(q, x);
            }
        }
        int minS = keep(s);
        int minM = m >= 0 ? floorPoints[m] : 0;
        if (fixedCost(q) + minS + minM > budget) {
            return plan;
        }

        std::vector<int> synergies;
        for (int y = 0; y < lib.size(); y++) {
            if (y != s && (info.synergy[0][y] > 0 || info.synergy[1][y] > 0) && cap(y) >= 1) {
                synergies.push_back(y);
            }
        }
        // Synergies that need unlocking; only allowed trees can be unlocked.
        std::vector<int> optional;
        for (int y : synergies) {
            if (std::find(q.begin(), q.end(), y) == q.end() && trees[lib.skill(y).tree]) {
                optional.push_back(y);
            }
        }

        int capM = m >= 0 ? cap(m) : 0;
        std::vector<int> masteryValue(capM + 1, 0);
        for (int lm = 1; lm <= capM; lm++) {
            masteryValue[lm] = lib.masteryValue(m, lib.effectiveLevel(m, lm, bonus));
        }

        int capS = cap(s);
        std::vector<std::vector<Candidate>> byLevel(capS + 1);

        for (unsigned mask = 0; mask < (1u << optional.size()); mask++) {
            std::vector<int> set = q;
            for (size_t j = 0; j < optional.size(); j++) {
                if (mask & (1u << j)) {
                    include(set, optional[j]);
                }
            }
            int base = fixedCost(set);
            if (base + minS + minM > budget) {
                continue;
            }

            // Knapsack DP over the active synergy skills: F[b] holds the
            // Pareto-best synergy totals reachable with b extra points.
            std::vector<int> active;
            double baseSyn[2] = { 0, 0 };
            for (int y : synergies) {
                if (std::find(set.begin(), set.end(), y) != set.end()) {
                    active.push_back(y);
                    baseSyn[0] += info.synergy[0][y] * keep(y);
                    baseSyn[1] += info.synergy[1][y] * keep(y);
                }
            }
            int maxExtra = 0;
            for (int y : active) {
                maxExtra += std::max(0, cap(y) - keep(y));
            }
            std::vector<std::vector<SynPoint>> f(maxExtra + 1);
            SynPoint zero;
            zero.extra.assign(active.size(), 0);
            f[0].push_back(zero);
            for (size_t j = 0; j < active.size(); j++) {
                int y = active[j];
                std::vector<std::vector<SynPoint>> next(maxExtra + 1);
                for (int b = 0; b <= maxExtra; b++) {
                    for (const auto& p : f[b]) {
                        for (int t = 0; t <= cap(y) - keep(y) && b + t <= maxExtra; t++) {
                            SynPoint r = p;
                            r.v[0] += t * info.synergy[0][y];
                            r.v[1] += t * info.synergy[1][y];
                            r.extra[j] = t;
                            synAdd(next[b + t], std::move(r));
                        }
                    }
                }
                f = std::move(next);
            }
            // Best with at most b extra points.
            for (int b = 1; b <= maxExtra; b++) {
                for (const auto& p : f[b - 1]) {
                    synAdd(f[b], p);
                }
            }

            for (int lm = minM; lm <= capM; lm++) {
                for (int ls = minS; ls <= capS; ls++) {
                    int rest = budget - base - ls - lm;
                    if (rest < 0) {
                        break;
                    }
                    for (const auto& p : f[std::min(rest, maxExtra)]) {
                        Candidate c;
                        double syn0 = 100.0 + baseSyn[0] + p.v[0];
                        double syn1 = 100.0 + baseSyn[1] + p.v[1];
                        if (info.element == Sorc::Cold) {
                            c.effect[0] = syn0;
                            c.effect[1] = syn1;
                            c.effect[2] = masteryValue[lm];
                        }
                        else {
                            c.effect[0] = syn0 * (100.0 + masteryValue[lm]);
                            c.effect[1] = syn1 * (100.0 + masteryValue[lm]);
                        }
                        c.hard.assign(lib.size(), 0);
                        for (int x : set) {
                            c.hard[x] = keep(x);
                        }
                        for (size_t j = 0; j < active.size(); j++) {
                            c.hard[active[j]] += p.extra[j];
                        }
                        c.hard[s] = ls;
                        if (m >= 0) {
                            c.hard[m] = lm;
                        }
                        for (int h : c.hard) {
                            c.used += h;
                        }
                        paretoAdd(byLevel[ls], std::move(c));
                    }
                }
            }
        }

        for (int ls = 1; ls <= capS; ls++) {
            for (const auto& c : byLevel[ls]) {
                Sorc::Damage d = lib.compute(s, c.hard, bonus, a);
                bool teleport = teleportSkill >= 0 && c.hard[teleportSkill] > 0;
                Score best = judge(areas, focus, epm, [&](const AreaStat& as) { return scoreArea(lib, d, as, a, teleport); });
                bool better = !plan.valid || best.value(epm) > plan.best.value(epm) * (1 + 1e-9);
                if (better) {
                    plan.valid = true;
                    plan.skill = s;
                    plan.hard = c.hard;
                    plan.damage = d;
                    plan.best = best;
                    plan.unspent = budget - c.used;
                    plan.teleport = teleport;
                }
            }
        }
        return plan;
    }

    std::string damageLine(const Sorc::Library& lib, const Sorc::Damage& d) {
        const auto& info = lib.skill(d.skill);
        std::string per = info.geometry == Sorc::Geometry::Wall || info.geometry == Sorc::Geometry::Trail ||
                          info.geometry == Sorc::Geometry::Channel ? " per second" : "";
        std::string out = fmt(d.hitMin, 1) + "-" + fmt(d.hitMax, 1) + " " + Sorc::elementName(d.element) + per;
        if (d.dotMax > 0) {
            out += " + " + fmt(d.dotMin, 1) + "-" + fmt(d.dotMax, 1) + " burning per second for " + fmt(d.dotSeconds, 1) + "s";
        }
        switch (info.geometry) {
            case Sorc::Geometry::ChargedBolt: out += ", " + std::to_string(d.count) + " bolts"; break;
            case Sorc::Geometry::Chain: out += ", " + std::to_string(d.count) + " hits"; break;
            case Sorc::Geometry::Summon: out += ", ~" + std::to_string(d.count) + " shots over " + fmt(d.dotSeconds, 0) + "s"; break;
            case Sorc::Geometry::Storm: out += ", ~" + std::to_string(d.count) + " bolts over " + fmt(d.dotSeconds, 0) + "s"; break;
            case Sorc::Geometry::Splash:
            case Sorc::Geometry::Meteor: out += ", radius " + fmt(d.radius * 2 / 3, 1) + " yards"; break;
            default: break;
        }
        out += "; " + fmt(d.mana, 1) + " mana" + (info.geometry == Sorc::Geometry::Channel ? "/s" : "");
        if (d.synergyPct[0] > 0) {
            out += ", synergy +" + fmt(d.synergyPct[0]) + "%";
        }
        if (d.synergyPct[1] > 0) {
            out += " (burn +" + fmt(d.synergyPct[1]) + "%)";
        }
        if (d.masteryPct > 0) {
            out += ", mastery +" + fmt(d.masteryPct) + "%";
        }
        if (d.pierce > 0) {
            out += ", -" + std::to_string(d.pierce) + "% enemy cold res";
        }
        return out;
    }

    // What a build must be able to kill to progress through the difficulty it
    // levels in (Normal below 20, Nightmare to 39, Hell from 40): Act 3's
    // Council in Travincal, all of Chaos Sanctuary, and all of the Throne of
    // Destruction with Baal's waves once that difficulty's Ancients are passed
    // (20/40/60). At exactly 20 and 40 the previous difficulty's Throne counts
    // too, since that is when it gets cleared. Kept as resistance triples.
    struct Progression {
        bool enforced = false;
        int difficulty = 0;
        std::vector<int> areas; // Indices into Mon::Library::areas().
        std::vector<std::array<int, 3>> resists;
    };

    // Seconds to clear the progression areas, from per-area scores.
    double progressionSeconds(const Progression& pr, const std::vector<Score>& scores) {
        double total = 0;
        for (int ai : pr.areas) {
            for (const Score& sc : scores) {
                if (sc.area == ai) {
                    total += sc.seconds + sc.travel;
                }
            }
        }
        return total;
    }

    Progression progressionFor(const Mon::Library& mon, int clvl) {
        static const int ancients[3] = { 20, 40, 60 };
        Progression pr;
        pr.enforced = true;
        pr.difficulty = clvl < 20 ? 0 : clvl < 40 ? 1 : 2;
        const auto& list = mon.areas();
        for (size_t i = 0; i < list.size(); i++) {
            const auto& ar = list[i];
            bool current = ar.difficulty == pr.difficulty;
            bool council = current && ar.id == 83;
            bool chaos = current && ar.id == 108;
            bool throne = ar.id == 131 && ((current && clvl >= ancients[ar.difficulty]) ||
                                           (ar.difficulty == pr.difficulty - 1 && clvl == ancients[ar.difficulty]));
            if (!council && !chaos && !throne) {
                continue;
            }
            pr.areas.push_back(static_cast<int>(i));
            for (const auto& p : ar.packs) {
                for (const auto& m : p.members) {
                    if (!mon.killable(m.monster) || (council && mon.id(m.monster).rfind("councilmember", 0) != 0)) {
                        continue;
                    }
                    std::array<int, 3> r = { mon.resist(m.monster, ar.difficulty, 0), mon.resist(m.monster, ar.difficulty, 1),
                                             mon.resist(m.monster, ar.difficulty, 2) };
                    if (std::find(pr.resists.begin(), pr.resists.end(), r) == pr.resists.end()) {
                        pr.resists.push_back(r);
                    }
                }
            }
        }
        return pr;
    }

    // Whether skills of elements e1 and e2 (-1 for none) can kill every
    // monster progression needs.
    bool covers(const Progression& pr, int e1, int e2) {
        if (!pr.enforced) {
            return true;
        }
        for (const auto& r : pr.resists) {
            bool ok = (e1 >= 0 && e1 < 3 && r[e1] < 100) || (e2 >= 0 && e2 < 3 && r[e2] < 100);
            if (!ok) {
                return false;
            }
        }
        return true;
    }

    // One skill in a rotation against a pack: casts per second and its hit.
    struct Source {
        const Sorc::Damage* d = nullptr;
        double rate = 0;
        Sorc::PackHit hit;
    };

    // Damage effectiveness of a skill on a member: 0 if immune, else
    // (100 - resistance after pierce)%, and the 3x3 footprint bonus.
    double effectiveness(const Sorc::Damage& d, const Sorc::PackHit& h, const MemberStat& m) {
        int res = d.element < 3 ? m.res[d.element] : 0;
        if (res >= 100) {
            return 0;
        }
        int eff = std::max(-100, res - d.pierce);
        return (100.0 - eff) / 100.0 * (m.box ? h.boxScale : 1.0);
    }

    // Seconds and mana to kill the members of a pack that `alive` marks and
    // the sources can damage, with every source cast at its rate the whole
    // fight. The same fluid model as castsToKill, per second and with each
    // member taking its own mix of the sources' damage: after T seconds a
    // member has taken other*T; the rest needs (h - other*T)/(aimed - other)
    // seconds aimed at it, at least one cast of the quickest source. Members
    // killed are cleared in `alive`.
    Part rotationCost(const PackStat& p, const Source* src, int n, std::vector<char>& alive) {
        struct Group {
            double c, h, a, o;
        };
        std::vector<Group> groups;
        Part out;
        double unit = HUGE_VAL;
        double tail = 0;
        for (int s = 0; s < n; s++) {
            if (src[s].rate > 0) {
                unit = std::min(unit, src[s].d->secondsPerCast * src[s].d->minCast);
                tail = std::max(tail, src[s].d->deliverySeconds - src[s].d->secondsPerCast + src[s].d->packSeconds);
            }
        }
        if (!std::isfinite(unit)) {
            return out;
        }
        for (size_t i = 0; i < p.members.size(); i++) {
            if (!alive[i]) {
                continue;
            }
            const MemberStat& m = p.members[i];
            double a = 0, o = 0, over = 0;
            for (int s = 0; s < n; s++) {
                if (src[s].rate <= 0) {
                    continue;
                }
                double e = effectiveness(*src[s].d, src[s].hit, m);
                a += src[s].rate * src[s].hit.aimed * e;
                o += src[s].rate * src[s].hit.other * e;
                over += src[s].rate * src[s].hit.aimed * e * src[s].hit.overshoot * e;
            }
            if (a <= 0) {
                continue; // Nothing here can damage it.
            }
            groups.push_back({ m.count, m.hp + over / a, a, std::min(o, a) });
            out.exp += m.count * m.exp;
            alive[i] = 0;
        }
        if (groups.empty()) {
            return out;
        }
        auto demand = [&](double t) {
            double sum = 0;
            for (const auto& g : groups) {
                double need = g.h - g.o * t;
                double gap = g.a - g.o;
                if (need <= 0 || gap <= 1e-12) {
                    continue;
                }
                sum += g.c * (need < gap * unit ? unit : need / gap);
            }
            return sum;
        };
        double lo = 0, hi = demand(0) + unit;
        for (int i = 0; i < 60; i++) {
            double mid = (lo + hi) / 2;
            (demand(mid) >= mid ? lo : hi) = mid;
        }
        double t = std::max(lo, unit);
        for (const auto& g : groups) {
            t = std::max(t, g.h / g.a * std::min(1.0, g.c));
        }
        double manaRate = 0;
        double packMana = 0;
        for (int s = 0; s < n; s++) {
            if (src[s].rate > 0) {
                manaRate += src[s].rate * src[s].d->mana;
                packMana += src[s].d->packMana;
            }
        }
        out.seconds = t + tail;
        out.mana = t * manaRate + packMana;
        return out;
    }

    // A hybrid against one pack: the fastest of casting one skill at its
    // rate with the other filling its downtime (both orders), or one skill
    // alone and then the other on what it couldn't kill.
    Part hybridPack(const Sorc::Library& lib, const Sorc::Damage& d1, const Sorc::Damage& d2, const PackStat& p,
                    const Sorc::Assumptions& a, bool epm) {
        Sorc::PackHit h1 = lib.packHit(d1, p.size, a);
        Sorc::PackHit h2 = lib.packHit(d2, p.size, a);
        auto busy = [](const Sorc::Damage& d) { return d.castFrames / 25.0; };
        auto fill = [&](const Sorc::Damage& first, const Sorc::Damage& second) {
            double spare = 1.0 - busy(first) / first.secondsPerCast;
            return std::max(0.0, std::min(1.0 / second.secondsPerCast, spare / std::max(busy(second), 1e-9)));
        };
        Part best;
        bool have = false;
        for (int plan = 0; plan < 4; plan++) {
            Source first[2] = { { &d1, 1.0 / d1.secondsPerCast, h1 }, { &d2, 0, h2 } };
            switch (plan) {
                case 0: first[1].rate = fill(d1, d2); break;         // d1 on cooldown, d2 fills.
                case 1: first[0].rate = fill(d2, d1); first[1].rate = 1.0 / d2.secondsPerCast; break;
                case 2: break;                                        // d1 alone, then d2.
                case 3: first[0].rate = 0; first[1].rate = 1.0 / d2.secondsPerCast; break; // d2 alone, then d1.
            }
            std::vector<char> alive(p.members.size(), 1);
            Part cost = rotationCost(p, first, 2, alive);
            // Clean up what the first phase couldn't damage with the skill left out of it, or either.
            Source rest[2] = { { &d1, 1.0 / d1.secondsPerCast, h1 }, { &d2, 1.0 / d2.secondsPerCast, h2 } };
            if (first[0].rate > 0) {
                rest[0].rate = 0;
            }
            if (first[1].rate > 0) {
                rest[1].rate = 0;
            }
            cost.add(rotationCost(p, rest, 2, alive));
            double v = epm ? cost.mana : cost.seconds;
            if (!have || v < (epm ? best.mana : best.seconds)) {
                best = cost;
                have = true;
            }
        }
        return best;
    }

    Score hybridArea(const Sorc::Library& lib, const Sorc::Damage& d1, const Sorc::Damage& d2, const AreaStat& as,
                     const Sorc::Assumptions& a, bool teleport, bool epm) {
        Score sc;
        sc.area = as.area;
        sc.travel = teleport ? as.travelTeleport : as.travelRun;
        sc.approach = teleport ? as.approachTeleport : as.approachRun;
        sc.possible = as.possible;
        Part total;
        for (const auto& p : as.packs) {
            total.add(hybridPack(lib, d1, d2, p, a, epm), p.packs);
        }
        sc.exp = total.exp;
        sc.mana = total.mana;
        sc.seconds = total.seconds;
        return sc;
    }

    // A timed skill can't be cast back to back: it has a cooldown (Frozen
    // Orb, Blizzard, Meteor, Fire Wall) or lasts (Hydra, Thunder Storm), so
    // another skill can fill its downtime.
    bool timed(const Sorc::Damage& d) {
        return d.secondsPerCast > d.castFrames / 25.0 + 1e-9;
    }

    // Two main skills used together. A pair is worth trying if its skills
    // have different elements (immunities) or one is timed and the other
    // isn't (one fills the other's downtime). For each skill and each point
    // budget (every `step` points below the full budget), the single-skill
    // optimizer finds its best allocation. Each pair tries each budget for
    // the first skill with the largest budget for the second that still fits
    // once shared points (prerequisites, Teleport, --require, --prev) are
    // counted once, scored on every area. The `keep` best pairs are scored
    // again with the combined allocation, so cross synergies count.
    std::vector<Plan> searchHybrids(const Sorc::Library& lib, const std::vector<int>& mains, int clvl, int budget,
                                    const Sorc::SkillBonuses& bonus, const Sorc::Assumptions& a, const std::vector<AreaStat>& areas,
                                    const std::vector<int>& required, const std::vector<int>& floorPoints, bool epm,
                                    int teleportSkill, const Trees& trees, int step, size_t keep, const Progression& progression,
                                    const std::vector<size_t>& focus) {
        struct Component {
            Plan plan;
        };
        std::vector<int> budgets;
        for (int b = budget; b >= 1; b -= step) {
            budgets.push_back(b);
        }
        std::vector<std::vector<Component>> comps(mains.size(), std::vector<Component>(budgets.size()));
        auto parallel = [&](size_t total, const std::function<void(size_t)>& job) {
            std::atomic<size_t> next{ 0 };
            std::vector<std::thread> workers;
            unsigned threads = std::max(1u, std::thread::hardware_concurrency());
            for (unsigned t = 0; t < threads; t++) {
                workers.emplace_back([&]() {
                    for (size_t i; (i = next++) < total;) {
                        job(i);
                    }
                });
            }
            for (auto& w : workers) {
                w.join();
            }
        };
        parallel(mains.size() * budgets.size(), [&](size_t job) {
            size_t i = job / budgets.size();
            size_t k = job % budgets.size();
            Component& c = comps[i][k];
            c.plan = optimizeSkill(lib, mains[i], clvl, budgets[k], bonus, a, areas, required, floorPoints, epm, teleportSkill, trees, focus);
        });

        struct Pick {
            size_t i1 = 0, i2 = 0, k1 = 0, k2 = 0;
            double value = 0;
        };
        std::vector<std::pair<size_t, size_t>> pairs;
        for (size_t i1 = 0; i1 < mains.size(); i1++) {
            for (size_t i2 = i1 + 1; i2 < mains.size(); i2++) {
                int e1 = lib.skill(mains[i1]).element;
                int e2 = lib.skill(mains[i2]).element;
                if (e1 >= 3 || e2 >= 3 || !covers(progression, e1, e2)) {
                    continue;
                }
                // Timing doesn't depend on points; check it at the full budget.
                const Plan& p1 = comps[i1][0].plan;
                const Plan& p2 = comps[i2][0].plan;
                bool overlap = p1.valid && p2.valid && timed(p1.damage) != timed(p2.damage);
                // Thunder Storm needs no casting while it runs, so it pairs with anything.
                bool storm = lib.skill(mains[i1]).geometry == Sorc::Geometry::Storm || lib.skill(mains[i2]).geometry == Sorc::Geometry::Storm;
                if (e1 != e2 || overlap || storm) {
                    pairs.push_back({ i1, i2 });
                }
            }
        }
        std::vector<Pick> best(pairs.size());
        parallel(pairs.size(), [&](size_t pi) {
            auto [i1, i2] = pairs[pi];
            for (size_t k1 = 0; k1 < budgets.size(); k1++) {
                const Component& c1 = comps[i1][k1];
                if (!c1.plan.valid) {
                    continue;
                }
                for (size_t k2 = 0; k2 < budgets.size(); k2++) {
                    const Component& c2 = comps[i2][k2];
                    if (!c2.plan.valid) {
                        continue;
                    }
                    int cost = 0;
                    for (int x = 0; x < lib.size(); x++) {
                        cost += std::max(c1.plan.hard[x], c2.plan.hard[x]);
                    }
                    if (cost > budget) {
                        continue;
                    }
                    bool teleport = c1.plan.teleport || c2.plan.teleport;
                    double value = judge(areas, focus, epm, [&](const AreaStat& as) {
                        return hybridArea(lib, c1.plan.damage, c2.plan.damage, as, a, teleport, epm);
                    }).value(epm);
                    if (value > best[pi].value) {
                        best[pi] = { i1, i2, k1, k2, value };
                    }
                    break; // The largest second budget that fits.
                }
            }
        });
        std::vector<Pick> picks;
        for (const Pick& pk : best) {
            if (pk.value > 0) {
                picks.push_back(pk);
            }
        }
        std::sort(picks.begin(), picks.end(), [](const Pick& x, const Pick& y) { return x.value > y.value; });
        if (picks.size() > keep) {
            picks.resize(keep);
        }

        std::vector<Plan> out(picks.size());
        parallel(picks.size(), [&](size_t n) {
            const Pick& pk = picks[n];
            const Plan& p1 = comps[pk.i1][pk.k1].plan;
            const Plan& p2 = comps[pk.i2][pk.k2].plan;
            Plan& h = out[n];
            h.skill = mains[pk.i1];
            h.skill2 = mains[pk.i2];
            h.hard.assign(lib.size(), 0);
            int used = 0;
            for (int x = 0; x < lib.size(); x++) {
                h.hard[x] = std::max(p1.hard[x], p2.hard[x]);
                used += h.hard[x];
            }
            h.unspent = budget - used;
            h.teleport = p1.teleport || p2.teleport;
            // List the stronger skill on its own first.
            if (p2.best.value(epm) > p1.best.value(epm)) {
                std::swap(h.skill, h.skill2);
            }
            h.damage = lib.compute(h.skill, h.hard, bonus, a);
            h.damage2 = lib.compute(h.skill2, h.hard, bonus, a);
            for (const auto& as : areas) {
                h.ranked.push_back(hybridArea(lib, h.damage, h.damage2, as, a, h.teleport, epm));
            }
            std::sort(h.ranked.begin(), h.ranked.end(), [&](const Score& x, const Score& y) { return x.value(epm) > y.value(epm); });
            if (!h.ranked.empty()) {
                h.best = judge(areas, focus, epm, [&](const AreaStat& as) {
                    for (const Score& sc : h.ranked) {
                        if (sc.area == as.area) {
                            return sc;
                        }
                    }
                    return Score();
                });
                h.valid = true;
            }
        });
        return out;
    }

    int runOptimizer(const Options& o, const Sorc::Library& lib, const Mon::Library& mon) {
        int clvl = std::atoi(o.positional[0].c_str());
        if (clvl < 1 || clvl > 99) {
            std::cerr << "Level must be 1-99.\n";
            return 1;
        }
        int quest = static_cast<int>(o.num("--quest-skills", 0));
        int players = std::clamp(static_cast<int>(o.num("--players", 1)), 1, 8);
        int top = std::max(1, static_cast<int>(o.num("--top", 5)));
        Sorc::Assumptions a = assumptionsFrom(o);
        Sorc::SkillBonuses bonus = bonusesFrom(o);
        int budget = clvl - 1 + quest;
        bool epm = o.has("--epm");

        std::vector<std::string> warnings;

        // Skills every build must have a point in, such as Teleport.
        std::vector<int> required;
        std::string requireList = o.str("--require");
        for (size_t start = 0; start < requireList.size();) {
            size_t comma = requireList.find(',', start);
            std::string name = requireList.substr(start, comma == std::string::npos ? std::string::npos : comma - start);
            start = comma == std::string::npos ? requireList.size() : comma + 1;
            name.erase(0, name.find_first_not_of(' '));
            name.erase(name.find_last_not_of(' ') + 1);
            if (name.empty()) {
                continue;
            }
            int r = lib.find(name);
            if (r < 0) {
                std::cerr << "Unknown skill in --require: " << name << "\n";
                return 1;
            }
            if (lib.skill(r).reqlevel > clvl) {
                warnings.push_back(lib.skill(r).name + " needs level " + std::to_string(lib.skill(r).reqlevel) + "; not required at level " + std::to_string(clvl) + ".");
                continue;
            }
            required.push_back(r);
        }

        // The previous level's build: every skill keeps at least these hard
        // points. Accepts the "Points:" format ("Fire Ball 6, Fire Bolt 11 (12); 2 unspent")
        // or "Fire Ball=6,Fire Bolt=11".
        std::vector<int> floorPoints(lib.size(), 0);
        std::string prevList = o.str("--prev");
        for (size_t start = 0; start < prevList.size();) {
            size_t end = prevList.find_first_of(",;", start);
            std::string item = prevList.substr(start, end == std::string::npos ? std::string::npos : end - start);
            start = end == std::string::npos ? prevList.size() : end + 1;
            size_t paren = item.find('(');
            if (paren != std::string::npos) {
                item.erase(paren); // Drop "(effective level)".
            }
            for (char& ch : item) {
                if (ch == '=') {
                    ch = ' ';
                }
            }
            item.erase(0, item.find_first_not_of(' '));
            item.erase(item.find_last_not_of(' ') + 1);
            const std::string unspent = "unspent";
            if (item.empty() || (item.size() >= unspent.size() && item.compare(item.size() - unspent.size(), unspent.size(), unspent) == 0)) {
                continue;
            }
            size_t space = item.find_last_of(' ');
            int r = space == std::string::npos ? -1 : lib.find(item.substr(0, item.find_last_not_of(' ', space) + 1));
            int points = space == std::string::npos ? 0 : std::atoi(item.c_str() + space + 1);
            if (r < 0 || points < 1) {
                std::cerr << "Can't read \"" << item << "\" in --prev; expected \"Skill Name 5\".\n";
                return 1;
            }
            int skillCap = std::clamp(clvl - lib.skill(r).reqlevel + 1, 0, 20);
            if (points > skillCap) {
                std::cerr << lib.skill(r).name << " can have at most " << skillCap << " hard points at level " << clvl << ".\n";
                return 1;
            }
            floorPoints[r] = std::max(floorPoints[r], points);
        }
        int prevPoints = 0;
        for (int x = 0; x < lib.size(); x++) {
            prevPoints += floorPoints[x];
        }
        if (prevPoints > budget) {
            std::cerr << "The previous build has " << prevPoints << " points; level " << clvl << " only has " << budget << ".\n";
            return 1;
        }

        Trees trees = { o.has("--fire"), o.has("--lightning"), o.has("--cold") };
        if (!trees[0] && !trees[1] && !trees[2]) {
            trees = { true, true, true };
        }

        std::vector<int> mains;
        if (o.values.count("--skill")) {
            int s = lib.find(o.str("--skill"));
            if (s < 0 || !lib.skill(s).killer()) {
                std::cerr << "Not a damage skill: " << o.str("--skill") << "\n";
                return 1;
            }
            if (!trees[lib.skill(s).tree]) {
                std::cerr << lib.skill(s).name << " is outside the trees allowed by --fire/--lightning/--cold.\n";
                return 1;
            }
            mains.push_back(s);
        }
        else {
            // Blaze only burns where you walk, so it's too awkward to level with;
            // it stays available as Fire Wall's prerequisite.
            for (int s = 0; s < lib.size(); s++) {
                const auto& g = lib.skill(s).geometry;
                if (lib.skill(s).killer() && trees[lib.skill(s).tree] && g != Sorc::Geometry::Trail &&
                    (g != Sorc::Geometry::Storm || a.thunderStorm)) {
                    mains.push_back(s);
                }
            }
        }

        std::vector<Plan> plans;
        std::vector<AreaStat> areas;
        Progression progression;
        // --hybrid and --progression are the same mode: hybrids, with progression's requirements.
        bool hybridMode = o.has("--progression") || o.has("--hybrid");
        if (hybridMode) {
            progression = progressionFor(mon, clvl);
        }
        if (budget < 1) {
            warnings.push_back("No skill points to spend yet. The first one comes at level 2 (or use --quest-skills).");
        }
        else {
            // Travel: base run speed on foot; Teleport covers its range once per cast.
            int teleportSkill = lib.find("Teleport");
            double castSeconds = teleportSkill >= 0 ? lib.compute(teleportSkill, 1, kNoSynergy, 0, a).castFrames / 25.0 : 0.4;
            a.runSpeed = lib.runVelocity() / 16.0; // Players move RunVelocity * 256 / 4096 subtiles a frame.
            double runSpeed = a.runSpeed * 25.0;
            double teleportSpeed = castSeconds > 0 ? a.teleportRange / castSeconds : 0;
            areas = prepareAreas(mon, clvl, players, runSpeed, teleportSpeed);
            if (!o.has("--rush")) {
                areas.erase(std::remove_if(areas.begin(), areas.end(),
                                           [&](const AreaStat& as) { return !reachable(mon.areas()[as.area], clvl); }),
                            areas.end());
            }

            // With experience per second, Teleport is worth points: try each
            // main skill with and without it, and keep the better build.
            // Teleport is open to every build, whatever the trees: like
            // --require, it may sit outside them.
            bool canTeleport = !epm && teleportSkill >= 0 && lib.skill(teleportSkill).reqlevel <= clvl &&
                               std::find(required.begin(), required.end(), teleportSkill) == required.end();
            std::vector<int> withTeleport = required;
            withTeleport.push_back(teleportSkill);

            // In hybrid/progression mode builds are judged by clearing the
            // progression areas together; otherwise by their best area.
            std::vector<size_t> focus;
            for (int ai : progression.areas) {
                for (size_t k = 0; k < areas.size(); k++) {
                    if (areas[k].area == ai) {
                        focus.push_back(k);
                    }
                }
            }

            plans.resize(mains.size());
            std::vector<std::thread> workers;
            unsigned threads = std::max(1u, std::thread::hardware_concurrency());
            for (unsigned t = 0; t < threads; t++) {
                workers.emplace_back([&, t]() {
                    for (size_t i = t; i < mains.size(); i += threads) {
                        plans[i] = optimizeSkill(lib, mains[i], clvl, budget, bonus, a, areas, required, floorPoints, epm, teleportSkill, trees, focus);
                        if (canTeleport) {
                            Plan alt = optimizeSkill(lib, mains[i], clvl, budget, bonus, a, areas, withTeleport, floorPoints, epm, teleportSkill, trees, focus);
                            if (alt.valid && (!plans[i].valid || alt.best.value(epm) > plans[i].best.value(epm))) {
                                plans[i] = alt;
                            }
                        }
                    }
                });
            }
            for (auto& w : workers) {
                w.join();
            }
            // With --progression, builds that can't kill what progression
            // needs are dropped, and hybrids of two elements that can are
            // searched too.
            auto planCovers = [&](const Plan& p) {
                return covers(progression, lib.skill(p.skill).element, p.skill2 >= 0 ? lib.skill(p.skill2).element : -1);
            };
            plans.erase(std::remove_if(plans.begin(), plans.end(), [&](const Plan& p) { return p.valid && !planCovers(p); }), plans.end());
            if (hybridMode) {
                int step = std::max(1, static_cast<int>(o.num("--hybrid-step", 1)));
                // Thunder Storm runs in the background of the other skill, so
                // it can be half of a hybrid even when it can't be a main skill.
                std::vector<int> partners = mains;
                int storm = lib.find("Thunder Storm");
                if (storm >= 0 && trees[lib.skill(storm).tree] && std::find(partners.begin(), partners.end(), storm) == partners.end() &&
                    !o.values.count("--skill")) {
                    partners.push_back(storm);
                }
                std::vector<Plan> hybrids = searchHybrids(lib, partners, clvl, budget, bonus, a, areas, canTeleport ? withTeleport : required,
                                                          floorPoints, epm, teleportSkill, trees, step, 5, progression, focus);
                // Keep only hybrids that beat both of their skills on their own.
                auto single = [&](int skill) {
                    double v = 0;
                    for (const Plan& p : plans) {
                        if (p.valid && p.skill == skill && p.skill2 < 0) {
                            v = std::max(v, p.best.value(epm));
                        }
                    }
                    return v;
                };
                for (const Plan& h : hybrids) {
                    if (h.best.value(epm) > std::max(single(h.skill), single(h.skill2)) * (1 + 1e-9)) {
                        plans.push_back(h);
                    }
                }
            }
            plans.erase(std::remove_if(plans.begin(), plans.end(), [&](const Plan& p) { return !p.valid || p.best.value(epm) <= 0; }), plans.end());
            std::sort(plans.begin(), plans.end(), [&](const Plan& x, const Plan& y) { return x.best.value(epm) > y.best.value(epm); });
            if (plans.empty()) {
                warnings.push_back(progression.enforced
                                       ? "No build available at this level can kill what progression needs."
                                       : "No damage skill is available at this level.");
            }
        }

        int64_t need = mon.expToNext(clvl);
        Json j(std::cout);
        j.begin('{');
        j.key("objective").value(epm ? "expPerMana" : "expPerSecond");
        j.key("rush").value(o.has("--rush"));
        j.key("progression").begin('{');
        j.key("enforced").value(progression.enforced);
        j.key("difficulty").value(Mon::difficultyName(progression.difficulty));
        j.key("areas").begin('[');
        for (int ai : progression.areas) {
            j.value(mon.areas()[ai].name + " (" + Mon::difficultyName(mon.areas()[ai].difficulty) + ")");
        }
        j.end(']');
        j.end('}');
        j.key("trees").begin('[');
        for (int t = 0; t < 3; t++) {
            if (trees[t]) {
                j.value(t == 0 ? "fire" : t == 1 ? "lightning" : "cold");
            }
        }
        j.end(']');
        j.key("level").value(clvl);
        j.key("points").value(budget);
        j.key("questSkills").value(quest);
        j.key("bonus").begin('{');
        j.key("all").value(bonus.all);
        j.key("fire").value(bonus.fire);
        j.key("lightning").value(bonus.lightning);
        j.key("cold").value(bonus.cold);
        j.end('}');
        j.key("players").value(players);
        j.key("fcr").value(a.fcr);
        j.key("required").begin('[');
        for (int r : required) {
            j.value(lib.skill(r).name);
        }
        j.end(']');
        j.key("previous").begin('[');
        for (int x = 0; x < lib.size(); x++) {
            if (floorPoints[x] > 0) {
                j.begin('{').key("skill").value(lib.skill(x).name).key("points").value(floorPoints[x]).end('}');
            }
        }
        j.end(']');
        j.key("warnings").begin('[');
        for (const auto& w : warnings) {
            j.value(w);
        }
        j.end(']');
        j.key("expToNext").value(need);

        // One build per main skill, best first.
        j.key("builds").begin('[');
        auto writeDamage = [&](const Sorc::Damage& d) {
            const auto& info = lib.skill(d.skill);
            bool perSecond = info.geometry == Sorc::Geometry::Wall || info.geometry == Sorc::Geometry::Trail ||
                             info.geometry == Sorc::Geometry::Channel;
            j.begin('{');
            j.key("skill").value(info.name);
            j.key("element").value(Sorc::elementName(d.element));
            j.key("min").value(d.hitMin);
            j.key("max").value(d.hitMax);
            j.key("perSecond").value(perSecond);
            j.key("burnMin").value(d.dotMin);
            j.key("burnMax").value(d.dotMax);
            j.key("burnSeconds").value(d.dotMax > 0 ? d.dotSeconds : 0.0);
            j.key("count").value(d.count);
            j.key("radiusYards").value(d.radius * 2 / 3);
            j.key("mana").value(d.mana);
            j.key("manaPerSecond").value(info.geometry == Sorc::Geometry::Channel);
            j.key("synergy").value(d.synergyPct[0]);
            j.key("burnSynergy").value(d.synergyPct[1]);
            j.key("mastery").value(d.masteryPct);
            j.key("pierce").value(d.pierce);
            j.key("castFrames").value(d.castFrames);
            j.key("cooldownFrames").value(d.cooldownFrames);
            j.key("secondsPerCast").value(d.secondsPerCast);
            j.end('}');
        };
        for (const Plan& p : plans) {
            const Sorc::Damage& d = p.damage;
            bool hybrid = p.skill2 >= 0;
            j.begin('{');
            j.key("skill").value(lib.skill(p.skill).name + (hybrid ? " + " + lib.skill(p.skill2).name : std::string()));
            j.key("hybrid").value(hybrid);
            // Every area judged against this build, best first; its leveling
            // numbers come from the best one.
            std::vector<Score> ranked = hybrid ? p.ranked : scoreAll(lib, d, areas, a, p.teleport, epm);
            Score lev = ranked.empty() ? Score() : ranked.front();
            j.key("expPerSecond").value(lev.perSecond());
            j.key("expPerMana").value(lev.perMana());
            j.key("secondsToNext").value(need > 0 && lev.perSecond() > 0 ? need / lev.perSecond() : 0.0);
            j.key("manaToNext").value(need > 0 && lev.perMana() > 0 ? need / lev.perMana() : 0.0);
            j.key("teleport").value(p.teleport);
            j.key("unspent").value(p.unspent);

            // Main skills first, then the rest in skill order.
            std::vector<int> order = { p.skill };
            if (hybrid) {
                order.push_back(p.skill2);
            }
            for (int x = 0; x < lib.size(); x++) {
                if (x != p.skill && x != p.skill2 && p.hard[x] > 0) {
                    order.push_back(x);
                }
            }
            j.key("allocation").begin('[');
            for (int x : order) {
                j.begin('{').key("skill").value(lib.skill(x).name).key("points").value(p.hard[x])
                    .key("level").value(lib.effectiveLevel(x, p.hard[x], bonus)).end('}');
            }
            j.end(']');
            j.key("added").begin('[');
            for (int x : order) {
                if (p.hard[x] > floorPoints[x]) {
                    j.begin('{').key("skill").value(lib.skill(x).name).key("points").value(p.hard[x] - floorPoints[x]).end('}');
                }
            }
            j.end(']');

            j.key("damage");
            writeDamage(d);
            if (hybrid) {
                j.key("secondaryDamage");
                writeDamage(p.damage2);
            }

            // Time to clear what progression needs, with this build.
            j.key("progressionSeconds").value(progressionSeconds(progression, ranked));
            j.key("areas").begin('[');
            for (int i = 0; i < top && i < static_cast<int>(ranked.size()) && ranked[i].value(epm) > 0; i++) {
                const Score& sc = ranked[i];
                const auto& ar = mon.areas()[sc.area];
                j.begin('{');
                j.key("id").value(ar.id);
                j.key("name").value(ar.name);
                j.key("act").value(ar.act);
                j.key("difficulty").value(Mon::difficultyName(ar.difficulty));
                j.key("areaLevel").value(ar.areaLevel);
                j.key("expPerMana").value(sc.perMana());
                j.key("expPerSecond").value(sc.perSecond());
                j.key("expPerClear").value(sc.exp);
                j.key("combatSeconds").value(sc.seconds);
                j.key("travelSeconds").value(sc.travel);
                j.key("approachSeconds").value(sc.approach);
                j.key("manaPerClear").value(sc.mana);
                j.key("killable").value(sc.possible > 0 ? sc.exp / sc.possible : 0.0);
                j.end('}');
            }
            j.end(']');
            j.end('}');
        }
        j.end(']');
        j.end('}');
        std::cout << "\n";
        return 0;
    }

    // ------------------------------------------------------------------
    // Utilities
    // ------------------------------------------------------------------

    int runSkill(const Options& o, const Sorc::Library& lib) {
        if (o.positional.size() < 3) {
            usage("sorcbuild");
            return 1;
        }
        int s = lib.find(o.positional[1]);
        if (s < 0) {
            std::cerr << "Unknown sorceress skill: " << o.positional[1] << "\n";
            return 1;
        }
        Sorc::Assumptions a = assumptionsFrom(o);
        Sorc::SkillBonuses bonus = bonusesFrom(o);
        std::vector<int> hard(lib.size(), 0);
        hard[s] = std::atoi(o.positional[2].c_str());
        for (size_t i = 3; i < o.positional.size(); i++) {
            const std::string& arg = o.positional[i];
            size_t eq = arg.find('=');
            int y = eq == std::string::npos ? -1 : lib.find(arg.substr(0, eq));
            if (y < 0) {
                std::cerr << "Expected \"Skill Name=points\", got: " << arg << "\n";
                return 1;
            }
            hard[y] = std::atoi(arg.c_str() + eq + 1);
        }

        const auto& info = lib.skill(s);
        Sorc::Damage d = lib.compute(s, hard, bonus, a);
        std::cout << info.name << " level " << d.level << " (" << hard[s] << " hard), " << Sorc::elementName(info.element)
                  << ", requires level " << info.reqlevel << "\n";
        if (d.level <= 0) {
            std::cout << "  Needs at least one hard point.\n";
            return 0;
        }
        if (!info.killer()) {
            std::cout << "  Not modeled as a killer; it only matters here as a synergy or prerequisite.\n";
            return 0;
        }
        std::cout << "  " << damageLine(lib, d) << "\n";
        std::cout << "  Cast: " << d.castFrames << " frames at " << a.fcr << "% FCR";
        if (d.cooldownFrames) {
            std::cout << ", cooldown " << fmt(d.cooldownFrames / 25.0, 2) << "s";
        }
        std::cout << "; " << fmt(d.secondsPerCast, 2) << "s per cast for exp/s\n";
        std::cout << "  Expected damage per cast by pack size (aimed / each other member), plus-shaped and 3x3 monsters:\n";
        for (double k : { 1.0, 2.0, 3.0, 5.0, 8.0 }) {
            Sorc::PackHit h = lib.packHit(d, k, a);
            std::cout << "    " << pad(fmt(k) + (k == 1 ? " monster" : " monsters"), 12) << pad(fmt(h.aimed, 1) + " / " + fmt(h.other, 1), 20)
                      << fmt(h.aimed * h.boxScale, 1) << " / " << fmt(h.other * h.boxScale, 1) << "\n";
        }
        return 0;
    }

    int runMonster(const Options& o, const Mon::Library& mon) {
        if (o.positional.size() < 2) {
            usage("sorcbuild");
            return 1;
        }
        int m = mon.find(o.positional[1]);
        if (m < 0) {
            std::cerr << "Unknown monstats Id: " << o.positional[1] << "\n";
            return 1;
        }
        int diff = Mon::parseDifficulty(o.str("--diff", "normal"));
        int quality = Mon::parseQuality(o.str("--quality", "normal"));
        if (diff < 0 || quality < 0) {
            std::cerr << "Bad --diff or --quality.\n";
            return 1;
        }
        int players = std::clamp(static_cast<int>(o.num("--players", 1)), 1, 8);
        int mlvl = static_cast<int>(o.num("--mlvl", mon.baseLevel(m, diff) + Mon::levelBonus(quality)));
        int pierce = static_cast<int>(o.num("--pierce", 0));

        double hp = mon.hp(m, diff, mlvl, quality, players);
        std::cout << mon.id(m) << ", " << Mon::difficultyName(diff) << ", level " << mlvl << ", " << Mon::qualityName(quality)
                  << ", players " << players << "\n";
        std::cout << "  HP: " << fmt(mon.hpMin(m, diff, mlvl, quality, players)) << "-" << fmt(mon.hpMax(m, diff, mlvl, quality, players))
                  << " (average " << fmt(hp) << ")\n";
        std::cout << "  EHP:";
        for (int e = 0; e < 3; e++) {
            int res = mon.resist(m, diff, e);
            std::cout << "  " << Sorc::elementName(static_cast<Sorc::Element>(e)) << " " << res << "% ";
            if (res >= 100) {
                std::cout << "immune";
            }
            else {
                int eff = std::max(-100, res - (e == Sorc::Cold ? pierce : 0));
                std::cout << fmt(hp * 100.0 / (100.0 - eff));
            }
        }
        std::cout << "\n";
        double exp = mon.experience(m, diff, mlvl, quality, players);
        std::cout << "  Experience: " << fmt(exp);
        if (o.values.count("--clvl")) {
            int clvl = static_cast<int>(o.num("--clvl", 1));
            double share = mon.expShare(clvl, mlvl);
            std::cout << "; a level " << clvl << " character gets " << fmt(share * 100, 1) << "% = " << fmt(exp * share);
        }
        std::cout << "\n";
        return 0;
    }

}

int main(int argc, char* argv[]) {
    Options o = parseArgs(argc, argv);
    if (o.positional.empty() || o.has("--help")) {
        usage(argv[0]);
        return o.has("--help") ? 0 : 1;
    }

    std::filesystem::path exeDir = std::filesystem::path(argv[0]).parent_path();
    std::string root = o.str("--data", exeDir.empty() ? "." : exeDir.string());
    std::string txt = root + "/txt/";
    std::string pop = root + "/pop/d2r-rotw_population.json";

    try {
        const std::string& cmd = o.positional[0];
        if (cmd == "skill") {
            Sorc::Library lib(txt);
            return runSkill(o, lib);
        }
        if (cmd == "monster") {
            Mon::Library mon(txt, pop);
            mon.setOnline(o.has("--online"));
            return runMonster(o, mon);
        }
        Sorc::Library lib(txt);
        Mon::Library mon(txt, pop);
        mon.setOnline(o.has("--online"));
        return runOptimizer(o, lib, mon);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
