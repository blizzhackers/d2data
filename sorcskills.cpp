#include "sorcskills.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <functional>
#include <stdexcept>

#include "d2calc.h"

namespace Sorc {

    namespace {

        std::string lower(std::string s) {
            for (char& ch : s) {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            return s;
        }

        // Base value plus per-level increments in the game's level brackets.
        int64_t bracket(int64_t base, const int64_t inc[5], int lvl) {
            int64_t v = base;
            for (int i = 2; i <= lvl; i++) {
                v += i <= 8 ? inc[0] : i <= 16 ? inc[1] : i <= 22 ? inc[2] : i <= 28 ? inc[3] : inc[4];
            }
            return v;
        }

        // Frames per cast at a given FCR: {fcr, frames} breakpoints.
        int framesAt(const std::vector<std::pair<int, int>>& table, int fcr) {
            int frames = table.front().second;
            for (const auto& [bp, f] : table) {
                if (fcr >= bp) {
                    frames = f;
                }
            }
            return frames;
        }

        const std::vector<std::pair<int, int>> kSorcFrames = {
            {0, 13}, {9, 12}, {20, 11}, {37, 10}, {63, 9}, {105, 8}, {200, 7},
        };
        const std::vector<std::pair<int, int>> kSorcLightningFrames = {
            {0, 19}, {7, 18}, {15, 17}, {23, 16}, {35, 15}, {52, 14}, {78, 13}, {117, 12}, {194, 11},
        };

        // The mechanics layer: how each sorceress skill delivers damage.
        Geometry geometryFor(const std::string& name) {
            static const std::vector<std::pair<const char*, Geometry>> table = {
                {"Fire Bolt", Geometry::Single},
                {"Ice Bolt", Geometry::Single},
                {"Ice Blast", Geometry::Single},
                {"Charged Bolt", Geometry::ChargedBolt},
                {"Fire Ball", Geometry::Splash},
                {"Glacial Spike", Geometry::Splash},
                {"Lightning", Geometry::Pierce},
                {"Inferno", Geometry::Channel},
                {"Nova", Geometry::Ring},
                {"Frost Nova", Geometry::Ring},
                {"Chain Lightning", Geometry::Chain},
                {"Frozen Orb", Geometry::FrozenOrb},
                {"Blizzard", Geometry::Blizzard},
                {"Fire Wall", Geometry::Wall},
                {"Blaze", Geometry::Trail},
                {"Meteor", Geometry::Meteor},
                {"Hydra", Geometry::Summon},
                {"Thunder Storm", Geometry::Storm},
            };
            for (const auto& [n, g] : table) {
                if (name == n) {
                    return g;
                }
            }
            return Geometry::None;
        }

        const double kPi = 3.14159265358979323846;

        using Cells = std::vector<std::pair<int, int>>;

        // Collision shapes in subtiles (GetInteractSize, CheckCollision_BlockAll_Width):
        // size 0-1 is one cell, 2 a plus, 3 or more a 3x3 box. Monsters with
        // monstats2 SizeX 1-2 are plus-shaped and SizeX 3 are boxes.
        Cells shapeCells(int size) {
            if (size <= 1) {
                return { { 0, 0 } };
            }
            if (size == 2) {
                return { { 0, 0 }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
            }
            Cells c;
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    c.push_back({ x, y });
                }
            }
            return c;
        }

        // Offsets from a missile's centre to a monster's centre at which
        // their shapes share a cell.
        Cells overlapOffsets(int missileSize, int monsterSize) {
            Cells out;
            for (auto [ax, ay] : shapeCells(missileSize)) {
                for (auto [bx, by] : shapeCells(monsterSize)) {
                    std::pair<int, int> d = { ax - bx, ay - by };
                    if (std::find(out.begin(), out.end(), d) == out.end()) {
                        out.push_back(d);
                    }
                }
            }
            return out;
        }

        // Shape facts per (missile size 0-3, monster footprint 2-3), computed once.
        struct ShapeFacts {
            double halfWidth = 0; // Half the average width of the overlap offsets: how close a line must pass.
            double cells = 0;     // Number of overlap offsets.
            double perRow = 0;    // Offsets per occupied row: segments of a straight wall touching the monster.
        };

        const ShapeFacts& shapeFacts(int missileSize, int monsterSize) {
            static const auto table = [] {
                std::array<std::array<ShapeFacts, 2>, 4> t{};
                for (int ms = 0; ms < 4; ms++) {
                    for (int fs = 0; fs < 2; fs++) {
                        Cells c = overlapOffsets(ms, fs + 2);
                        double sum = 0;
                        const int steps = 90;
                        for (int i = 0; i < steps; i++) {
                            double ux = std::cos(kPi * i / steps);
                            double uy = std::sin(kPi * i / steps);
                            double lo = 1e9;
                            double hi = -1e9;
                            for (auto [x, y] : c) {
                                for (double cx : { x - 0.5, x + 0.5 }) {
                                    for (double cy : { y - 0.5, y + 0.5 }) {
                                        lo = std::min(lo, cx * ux + cy * uy);
                                        hi = std::max(hi, cx * ux + cy * uy);
                                    }
                                }
                            }
                            sum += hi - lo;
                        }
                        std::vector<int> rows;
                        for (auto [x, y] : c) {
                            if (std::find(rows.begin(), rows.end(), y) == rows.end()) {
                                rows.push_back(y);
                            }
                        }
                        t[ms][fs].halfWidth = sum / steps / 2;
                        t[ms][fs].cells = static_cast<double>(c.size());
                        t[ms][fs].perRow = static_cast<double>(c.size()) / rows.size();
                    }
                }
                return t;
            }();
            return table[std::clamp(missileSize, 0, 3)][monsterSize >= 3 ? 1 : 0];
        }

        // Meteor's burning ground: one meteorfire at each of these subtile
        // offsets from the impact (MISSILES_SpawnRadialPattern18, sHitPar2 1).
        const int kMeteorFires[18][2] = {
            { 2, -2 }, { -2, -2 }, { 0, 2 }, { 0, 5 }, { -3, 3 }, { 0, 3 }, { 3, 3 }, { -1, 2 }, { 1, 1 },
            { -1, -1 }, { 2, -1 }, { -4, -2 }, { -3, -2 }, { -1, -3 }, { 0, -4 }, { 1, -3 }, { 3, -3 }, { 4, -2 },
        };

        // Points spread evenly over the unit disk (equal-area rings).
        const std::vector<std::pair<double, double>>& unitDisk() {
            static const auto points = [] {
                std::vector<std::pair<double, double>> p;
                const int rings = 8;
                const int spokes = 16;
                for (int i = 0; i < rings; i++) {
                    double r = std::sqrt((i + 0.5) / rings);
                    for (int j = 0; j < spokes; j++) {
                        double t = 2 * kPi * (j + 0.5 * (i % 2)) / spokes;
                        p.push_back({ r * std::cos(t), r * std::sin(t) });
                    }
                }
                return p;
            }();
            return points;
        }

        // For a bolt fired from the centre of subtile (0,0) in `dirs` evenly
        // spaced directions, the share of directions whose path enters a
        // cell of a monster footprint centred at subtile (dx, dy). Collision
        // is only tested on subtiles a missile enters, so the spawn subtile
        // itself never counts.
        struct BoltTable {
            int reach = 0;
            std::vector<double> share;
            double at(int dx, int dy) const {
                if (dx < -reach || dx > reach || dy < -reach || dy > reach) {
                    return 0.0;
                }
                return share[(dy + reach) * (2 * reach + 1) + (dx + reach)];
            }
        };

        BoltTable boltTable(double range, int dirs, int footprint) {
            BoltTable t;
            t.reach = static_cast<int>(std::ceil(range)) + 2;
            int side = 2 * t.reach + 1;
            t.share.assign(static_cast<size_t>(side) * side, 0.0);
            Cells foot = shapeCells(footprint);
            std::vector<char> hit(t.share.size());
            for (int i = 0; i < dirs && range > 0; i++) {
                double ux = std::cos(2 * kPi * i / dirs);
                double uy = std::sin(2 * kPi * i / dirs);
                // Walk the grid cells the path enters (Amanatides-Woo).
                int cx = 0;
                int cy = 0;
                int sx = ux > 0 ? 1 : -1;
                int sy = uy > 0 ? 1 : -1;
                double dx = std::fabs(ux) > 1e-12 ? 1.0 / std::fabs(ux) : HUGE_VAL;
                double dy = std::fabs(uy) > 1e-12 ? 1.0 / std::fabs(uy) : HUGE_VAL;
                double tx = 0.5 * dx;
                double ty = 0.5 * dy;
                std::fill(hit.begin(), hit.end(), 0);
                for (;;) {
                    double next = std::min(tx, ty);
                    if (next > range) {
                        break;
                    }
                    if (tx < ty) {
                        cx += sx;
                        tx += dx;
                    }
                    else {
                        cy += sy;
                        ty += dy;
                    }
                    for (auto [fx, fy] : foot) {
                        int ox = cx - fx;
                        int oy = cy - fy;
                        if (ox >= -t.reach && ox <= t.reach && oy >= -t.reach && oy <= t.reach) {
                            hit[(oy + t.reach) * side + (ox + t.reach)] = 1;
                        }
                    }
                }
                for (size_t j = 0; j < hit.size(); j++) {
                    t.share[j] += hit[j];
                }
            }
            for (double& v : t.share) {
                v /= std::max(1, dirs);
            }
            return t;
        }

        // Missile speed in subtiles per frame: (Vel + VelLev*lvl/8) * 0.75/16.
        double missileSpeed(const D2::ROTW::t_missiles& m, int lvl) {
            return (m.Vel + m.VelLev * lvl / 8.0) * 0.75 / 16.0;
        }

        Element elementOf(const std::string& etype) {
            if (etype == "fire") {
                return Fire;
            }
            if (etype == "ltng") {
                return Lightning;
            }
            if (etype == "cold") {
                return Cold;
            }
            return NoElement;
        }

        int64_t skillParam(const D2::ROTW::t_skills& r, int n) {
            switch (n) {
                case 1: return r.Param1;
                case 2: return r.Param2;
                case 3: return r.Param3;
                case 4: return r.Param4;
                case 5: return r.Param5;
                case 6: return r.Param6;
                case 7: return r.Param7;
                case 8: return r.Param8;
                case 9: return r.Param9;
                case 10: return r.Param10;
                case 11: return r.Param11;
                case 12: return r.Param12;
                case 13: return r.Param13;
                case 14: return r.Param14;
                default: return 0;
            }
        }

    }

    const char* elementName(Element e) {
        switch (e) {
            case Fire: return "fire";
            case Lightning: return "lightning";
            case Cold: return "cold";
            default: return "none";
        }
    }

    Library::Library(const std::string& dir) {
        skillRows = D2::ROTW::t_skills::readfile(dir + "skills.txt");
        missileRows = D2::ROTW::t_missiles::readfile(dir + "missiles.txt");
        descRows = D2::ROTW::t_skilldesc::readfile(dir + "skilldesc.txt");

        if (skillRows.empty() || missileRows.empty() || descRows.empty()) {
            throw std::runtime_error("Could not read skills.txt, missiles.txt or skilldesc.txt from " + dir);
        }
        for (const auto& c : D2::ROTW::t_charstats::readfile(dir + "charstats.txt")) {
            if (c._class == "Sorceress") {
                run = c.RunVelocity;
                walk = c.WalkVelocity;
            }
        }

        for (size_t row = 0; row < skillRows.size(); row++) {
            const auto& r = skillRows[row];
            if (r.charclass != "sor") {
                continue;
            }
            SkillInfo s;
            s.name = r.skill;
            s.row = static_cast<int>(row);
            s.reqlevel = std::max(1, r.reqlevel);
            s.element = elementOf(r.EType);
            s.geometry = geometryFor(r.skill);
            for (const auto& d : descRows) {
                if (d.skilldesc == r.skilldesc) {
                    s.tree = std::clamp(d.SkillPage - 1, 0, 2);
                    break;
                }
            }
            info.push_back(s);
        }

        for (auto& s : info) {
            const auto& r = skillRows[s.row];
            for (const std::string& req : { r.reqskill1, r.reqskill2 }) {
                if (!req.empty()) {
                    int p = find(req);
                    if (p < 0) {
                        throw std::runtime_error("Unknown prerequisite " + req + " for " + s.name);
                    }
                    s.prereqs.push_back(p);
                }
            }
            if (s.name == "Fire Mastery") {
                masteryByElement[Fire] = find(s.name);
            }
            else if (s.name == "Lightning Mastery") {
                masteryByElement[Lightning] = find(s.name);
            }
            else if (s.name == "Cold Mastery") {
                masteryByElement[Cold] = find(s.name);
            }
        }

        for (auto& s : info) {
            if (s.element != NoElement) {
                s.mastery = masteryByElement[s.element];
            }

            // Synergy coefficients: evaluate each formula with one hard point
            // in a single skill at a time. The formulas are linear sums.
            const auto& r = skillRows[s.row];
            std::string formulas[2] = { r.EDmgSymPerCalc, "" };
            for (const std::string& m : { r.srvmissile, r.srvmissilea }) {
                int mr = missileRow(m);
                if (mr < 0) {
                    continue;
                }
                for (const std::string& sub : { missileRows[mr].HitSubMissile1, missileRows[mr].SubMissile1 }) {
                    int sr = missileRow(sub);
                    if (sr >= 0 && missileRows[sr].EMin > 0 && !missileRows[sr].EDmgSymPerCalc.empty()) {
                        formulas[1] = missileRows[sr].EDmgSymPerCalc;
                    }
                }
            }

            s.synergy.assign(2, std::vector<double>(info.size(), 0.0));
            for (int c = 0; c < 2; c++) {
                if (formulas[c].empty()) {
                    continue;
                }
                std::vector<int> hard(info.size(), 0);
                D2Calc::Context ctx;
                ctx.ident = [&](const std::string& id) -> int64_t {
                    if (id.rfind("par", 0) == 0) {
                        return skillParam(r, std::atoi(id.c_str() + 3));
                    }
                    return 0;
                };
                ctx.ref = [&](const std::string& fn, const std::string& arg, const std::string&) -> int64_t {
                    int y = fn == "skill" ? find(arg) : -1;
                    return y >= 0 ? hard[y] : 0;
                };
                int64_t base = D2Calc::eval(formulas[c], ctx);
                for (size_t y = 0; y < info.size(); y++) {
                    hard[y] = 1;
                    s.synergy[c][y] = static_cast<double>(D2Calc::eval(formulas[c], ctx) - base);
                    hard[y] = 0;
                }
            }
        }
    }

    int Library::find(const std::string& name) const {
        std::string n = lower(name);
        for (size_t i = 0; i < info.size(); i++) {
            if (lower(info[i].name) == n) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    int Library::missileRow(const std::string& name) const {
        if (name.empty()) {
            return -1;
        }
        for (size_t i = 0; i < missileRows.size(); i++) {
            if (missileRows[i].Missile == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    std::vector<int> Library::closure(int skill) const {
        std::vector<int> out;
        std::function<void(int)> visit = [&](int s) {
            if (std::find(out.begin(), out.end(), s) != out.end()) {
                return;
            }
            out.push_back(s);
            for (int p : info[s].prereqs) {
                visit(p);
            }
        };
        visit(skill);
        return out;
    }

    int Library::effectiveLevel(int skill, int hard, const SkillBonuses& bonus) const {
        if (hard <= 0) {
            return 0; // Bonuses only apply to skills with a hard point.
        }
        int tab = info[skill].tree == 0 ? bonus.fire : info[skill].tree == 1 ? bonus.lightning : bonus.cold;
        return hard + bonus.all + tab;
    }

    int64_t Library::missileRange(int missile, int lvl) const {
        if (missile < 0) {
            return 0;
        }
        D2Calc::Context ctx;
        ctx.ident = [&](const std::string& id) -> int64_t { return id == "lvl" ? lvl : 0; };
        return D2Calc::eval(missileRows[missile].Range, ctx);
    }

    int64_t Library::evalSkill(const std::string& expr, int row, int lvl, int blvl) const {
        const auto& r = skillRows[row];
        D2Calc::Context ctx;
        ctx.ident = [&](const std::string& id) -> int64_t {
            if (id == "lvl") {
                return lvl;
            }
            if (id == "blvl") {
                return blvl;
            }
            if (id.size() == 4 && id.rfind("par", 0) == 0) {
                return skillParam(r, id[3] - '0');
            }
            if (id.size() == 4 && id.rfind("pa", 0) == 0) {
                return skillParam(r, std::atoi(id.c_str() + 2));
            }
            if (id.size() == 4 && (id[0] == 'l' || id[0] == 'd') && (id[1] == 'n' || id[1] == 'm')) {
                int a = id[2] - '0';
                int b = id[3] - '0';
                int64_t pa = skillParam(r, a);
                int64_t pb = skillParam(r, b);
                return id[0] == 'l' ? D2Calc::linear(pa, pb, lvl) : D2Calc::diminishing(pa, pb, lvl);
            }
            if (id == "clc1") return evalSkill(r.calc1, row, lvl, blvl);
            if (id == "clc2") return evalSkill(r.calc2, row, lvl, blvl);
            if (id == "clc3") return evalSkill(r.calc3, row, lvl, blvl);
            if (id == "clc4") return evalSkill(r.calc4, row, lvl, blvl);
            if (id == "len") return evalSkill(r.auralencalc, row, lvl, blvl);
            if (id == "rng") return evalSkill(r.aurarangecalc, row, lvl, blvl);
            return 0;
        };
        ctx.ref = [&](const std::string& fn, const std::string& arg, const std::string& prop) -> int64_t {
            if (fn == "miss" && prop == "rang") {
                return missileRange(missileRow(arg), lvl);
            }
            return 0; // skill() synergies are handled separately; stat() reads gear we don't model.
        };
        return D2Calc::eval(expr, ctx);
    }

    int Library::masteryValue(int masterySkill, int lvl) const {
        if (masterySkill < 0 || lvl <= 0) {
            return 0;
        }
        const auto& r = skillRows[info[masterySkill].row];
        return static_cast<int>(evalSkill(r.passivecalc1, info[masterySkill].row, lvl, lvl));
    }

    void Library::synergyFromHard(int skill, const std::vector<int>& hard, double out[2]) const {
        for (int c = 0; c < 2; c++) {
            out[c] = 0;
            for (size_t y = 0; y < info.size(); y++) {
                out[c] += info[skill].synergy[c][y] * hard[y];
            }
        }
    }

    Damage Library::compute(int skill, const std::vector<int>& hard, const SkillBonuses& bonus, const Assumptions& a) const {
        double syn[2];
        synergyFromHard(skill, hard, syn);
        int m = info[skill].mastery;
        int mlvl = m >= 0 ? effectiveLevel(m, hard[m], bonus) : 0;
        return compute(skill, effectiveLevel(skill, hard[skill], bonus), syn, mlvl, a);
    }

    Damage Library::compute(int skill, int lvl, const double synergyPct[2], int masteryLvl, const Assumptions& a) const {
        const SkillInfo& s = info[skill];
        const auto& r = skillRows[s.row];

        Damage d;
        d.skill = skill;
        d.element = s.element;
        d.level = lvl;
        if (lvl <= 0) {
            return d;
        }
        d.synergyPct[0] = synergyPct[0];
        d.synergyPct[1] = synergyPct[1];

        int mv = masteryValue(s.mastery, masteryLvl);
        if (s.element == Cold) {
            d.pierce = mv;
        }
        else {
            d.masteryPct = mv;
        }

        const int64_t minInc[5] = { r.EMinLev1, r.EMinLev2, r.EMinLev3, r.EMinLev4, r.EMinLev5 };
        const int64_t maxInc[5] = { r.EMaxLev1, r.EMaxLev2, r.EMaxLev3, r.EMaxLev4, r.EMaxLev5 };
        double shift = std::ldexp(1.0, r.HitShift);
        double min256 = static_cast<double>(bracket(r.EMin, minInc, lvl)) * shift;
        double max256 = static_cast<double>(bracket(r.EMax, maxInc, lvl)) * shift;
        double mult = (100.0 + synergyPct[0]) / 100.0 * (100.0 + d.masteryPct) / 100.0;

        // Hits are in 256ths. The per-second tooltips turn per-frame 256ths
        // straight into points per second.
        double perHit = mult / 256.0;
        double perSecond = 0;
        switch (s.geometry) {
            case Geometry::Wall:
            case Geometry::Trail:
                perSecond = mult * 75.0 / 256.0; // enms*25*3/256
                break;
            case Geometry::Channel:
                perSecond = mult * 12.5 / 256.0; // One flame every 2 frames; the tooltip truncates to enms*12/256.
                break;
            default:
                break;
        }
        d.hitMin = min256 * (perSecond > 0 ? perSecond : perHit);
        d.hitMax = max256 * (perSecond > 0 ? perSecond : perHit);

        // Mana in 256ths, never below minmana.
        double mana256 = static_cast<double>(r.mana + static_cast<int64_t>(r.lvlmana) * (lvl - 1)) * std::ldexp(1.0, r.manashift);
        mana256 = std::max(mana256, static_cast<double>(r.minmana) * 256.0);
        d.mana = mana256 / 256.0;

        bool lightningAnim = r.anim == "SQ" && r.seqnum == 12;
        d.castFrames = framesAt(lightningAnim ? kSorcLightningFrames : kSorcFrames, a.fcr);
        d.cooldownFrames = r.localdelay;
        d.secondsPerCast = std::max(d.castFrames, d.cooldownFrames) / 25.0;

        switch (s.geometry) {
            case Geometry::Splash:
                d.radius = static_cast<double>(evalSkill(r.aurarangecalc.empty() ? r.calc1 : r.aurarangecalc, s.row, lvl, lvl));
                break;
            case Geometry::Pierce: {
                int m = missileRow(r.srvmissile);
                d.missileSize = m >= 0 ? missileRows[m].Size : 1;
                break;
            }
            case Geometry::FrozenOrb: {
                // The orb fires one bolt per frame (Param1 1) in a scattered
                // spiral, then a nova of 64/sHitPar1 bolts when it expires.
                int orb = missileRow(r.srvmissile);
                int bolt = orb >= 0 ? missileRow(missileRows[orb].SubMissile1) : -1;
                int nova = orb >= 0 ? missileRow(missileRows[orb].HitSubMissile1) : -1;
                if (orb >= 0 && bolt >= 0) {
                    const auto& o = missileRows[orb];
                    d.orbSpeed = missileSpeed(o, lvl);
                    d.orbLife = static_cast<double>(missileRange(orb, lvl));
                    d.boltRange = missileSpeed(missileRows[bolt], lvl) * missileRange(bolt, lvl);
                    d.missileSize = missileRows[bolt].Size;
                    d.novaBolts = o.sHitPar1 > 0 ? 64 / o.sHitPar1 : 0;
                    d.novaRange = nova >= 0 ? missileSpeed(missileRows[nova], lvl) * missileRange(nova, lvl) : 0;
                    d.overlap[0] = orbHits(d, a, 2);
                    d.overlap[1] = orbHits(d, a, 3);
                }
                break;
            }
            case Geometry::ChargedBolt:
            case Geometry::Chain:
                d.count = static_cast<int>(evalSkill(r.calc1, s.row, lvl, lvl));
                break;
            case Geometry::Wall: {
                int m = missileRow(r.srvmissileb);
                d.dotSeconds = missileRange(m, lvl) / 25.0;
                d.missileSize = m >= 0 ? missileRows[m].Size : 1;
                break;
            }
            case Geometry::Trail: {
                int m = missileRow(r.srvmissilea);
                d.dotSeconds = missileRange(m, lvl) / 25.0;
                d.missileSize = m >= 0 ? missileRows[m].Size : 1;
                break;
            }
            case Geometry::Blizzard: {
                // One shard every calc2 frames for the center's life, landing
                // on a whole-subtile offset of -(calc1-1)..calc1-2 on each
                // axis. A shard hits a monster whose footprint overlaps its
                // own (missiles.txt Size).
                int center = missileRow(r.srvmissilea);
                int shard = center >= 0 ? missileRow(missileRows[center].SubMissile1) : -1;
                double life = static_cast<double>(missileRange(center, lvl));
                double period = static_cast<double>(std::max<int64_t>(1, evalSkill(r.calc2, s.row, lvl, lvl)));
                double width = 2.0 * static_cast<double>(std::max<int64_t>(1, evalSkill(r.calc1, s.row, lvl, lvl) - 1));
                d.count = static_cast<int>(life / period);
                d.radius = width / 2;
                d.missileSize = shard >= 0 ? missileRows[shard].Size : 1;
                d.dotSeconds = life / 25.0;
                break;
            }
            case Geometry::Channel:
                // Inferno: every start command charges the per-cast cost once.
                // While channeling the sequence repeats every 2 frames, so a
                // second holds 12.5 charges and 12.5 flames. The opening
                // sequence (15 frames) is charged but makes no flame. One
                // "cast" here is a second of channeling.
                d.mana = mana256 * 12.5 / 256.0;
                d.castFrames = 25;
                d.secondsPerCast = 1.0;
                d.minCast = 1.0 / 12.5;
                d.packMana = mana256 / 256.0;
                d.packSeconds = 15.0 / 25.0;
                {
                    int m = missileRow(r.srvmissilea);
                    d.missileSize = m >= 0 ? missileRows[m].Size : 1;
                }
                break;
            case Geometry::Meteor: {
                d.radius = static_cast<double>(evalSkill(r.aurarangecalc, s.row, lvl, lvl));
                int center = missileRow(r.srvmissilea);
                int fire = center >= 0 ? missileRow(missileRows[center].HitSubMissile1) : -1;
                // meteorcenter lands when its life runs out: Range frames.
                d.delaySeconds = missileRange(center, lvl) / 25.0;
                if (fire >= 0) {
                    const auto& m = missileRows[fire];
                    const int64_t mi[5] = { m.MinELev1, m.MinELev2, m.MinELev3, m.MinELev4, m.MinELev5 };
                    const int64_t ma[5] = { m.MaxELev1, m.MaxELev2, m.MaxELev3, m.MaxELev4, m.MaxELev5 };
                    double fs = std::ldexp(1.0, m.HitShift);
                    double fm = (100.0 + synergyPct[1]) / 100.0 * (m.ApplyMastery ? (100.0 + d.masteryPct) / 100.0 : 1.0);
                    // m1eo*25*3*(mael+100)/100/256
                    d.dotMin = static_cast<double>(bracket(m.EMin, mi, lvl)) * fs * fm * 75.0 / 256.0;
                    d.dotMax = static_cast<double>(bracket(m.EMax, ma, lvl)) * fs * fm * 75.0 / 256.0;
                    // Each fire lasts Meteor's ln34 frames, overriding meteorfire's Range.
                    int64_t life = evalSkill("ln34", s.row, lvl, lvl);
                    d.dotSeconds = (life > 0 ? life : missileRange(fire, lvl)) / 25.0;
                    d.missileSize = m.Size;
                    d.overlap[0] = meteorFires(d, a, 2);
                    d.overlap[1] = meteorFires(d, a, 3);
                }
                break;
            }
            case Geometry::Summon: {
                double life = static_cast<double>(evalSkill(r.calc1, s.row, lvl, lvl)); // Frames.
                double maxPets = std::max<int64_t>(1, evalSkill(r.petmax, s.row, lvl, lvl) / 3);
                d.count = static_cast<int>(3.0 * life / a.hydraInterval); // Three heads per cast.
                d.dotSeconds = life / 25.0;
                d.secondsPerCast = std::max(d.castFrames / 25.0, d.dotSeconds / maxPets);
                break;
            }
            case Geometry::Storm: {
                double life = static_cast<double>(evalSkill(r.auralencalc, s.row, lvl, lvl));
                double gap = static_cast<double>(std::max<int64_t>(1, evalSkill(r.perdelay, s.row, lvl, lvl)));
                d.count = static_cast<int>(life / gap);
                d.dotSeconds = life / 25.0;
                d.radius = static_cast<double>(r.Param7);
                d.secondsPerCast = std::max(d.secondsPerCast, d.dotSeconds); // One cast lasts the whole storm.
                break;
            }
            default:
                break;
        }

        // When a cast's damage has fully landed, for experience per second.
        double castSeconds = d.castFrames / 25.0;
        switch (s.geometry) {
            case Geometry::FrozenOrb:
                d.deliverySeconds = castSeconds + d.orbLife / 25.0;
                break;
            case Geometry::Blizzard:
            case Geometry::Wall:
                d.deliverySeconds = castSeconds + std::min(a.dwell, d.dotSeconds);
                break;
            case Geometry::Trail:
                d.deliverySeconds = castSeconds + std::min(a.trail, d.dotSeconds);
                break;
            case Geometry::Meteor:
                d.deliverySeconds = castSeconds + d.delaySeconds + std::min(a.dwell, d.dotSeconds);
                break;
            default:
                d.deliverySeconds = d.secondsPerCast;
                break;
        }
        d.deliverySeconds = std::max(d.deliverySeconds, d.secondsPerCast);
        return d;
    }

    const OverlapTable* Library::orbHits(const Damage& d, const Assumptions& a, int footprint) const {
        char key[256];
        std::snprintf(key, sizeof key, "orb %g %g %g %d %g %d %g %g %d", d.orbSpeed, d.orbLife, d.boltRange, d.novaBolts,
                      d.novaRange, d.missileSize, a.castDistance, a.packAreaPerMonster, footprint);
        std::lock_guard<std::mutex> lock(cacheLock);
        auto it = cache.find(key);
        if (it != cache.end()) {
            return &it->second;
        }

        // The orb flies from the caster through the centre of the aimed
        // monster's subtile, firing one bolt a frame from its current
        // subtile; the direction steps through the 64-entry table, so over
        // casts each bolt's direction is uniform over those 64. The nova
        // fires its bolts evenly spaced where the orb expires.
        BoltTable spiral = boltTable(d.boltRange, 64, footprint);
        BoltTable nova = boltTable(d.novaRange, std::max(1, d.novaBolts), footprint);
        auto hits = [&](double x, double y) {
            int mx = static_cast<int>(std::lround(x));
            int my = static_cast<int>(std::lround(y));
            double sum = 0;
            for (int f = 0; f < static_cast<int>(d.orbLife); f++) {
                int ox = static_cast<int>(std::lround(-a.castDistance + d.orbSpeed * f));
                sum += spiral.at(mx - ox, my);
            }
            int ox = static_cast<int>(std::lround(-a.castDistance + d.orbSpeed * d.orbLife));
            sum += d.novaBolts * nova.at(mx - ox, my);
            return sum;
        };

        OverlapTable t;
        t.aimed = hits(0, 0);
        t.other.assign(41, 0.0);
        for (int k = 2; k <= 40; k++) {
            double radius = std::sqrt(k * a.packAreaPerMonster / kPi);
            double sum = 0;
            for (auto [x, y] : unitDisk()) {
                sum += hits(radius * x, radius * y);
            }
            t.other[k] = sum / unitDisk().size();
        }
        return &cache.emplace(key, std::move(t)).first->second;
    }

    const OverlapTable* Library::meteorFires(const Damage& d, const Assumptions& a, int footprint) const {
        char key[128];
        std::snprintf(key, sizeof key, "meteor %d %g %d", d.missileSize, a.packAreaPerMonster, footprint);
        std::lock_guard<std::mutex> lock(cacheLock);
        auto it = cache.find(key);
        if (it != cache.end()) {
            return &it->second;
        }

        // Fires touching a monster standing at (x, y) from the impact. Each
        // is direct fire damage that hits every frame, so they stack.
        Cells touch = overlapOffsets(d.missileSize, footprint);
        auto fires = [&](double x, double y) {
            int px = static_cast<int>(std::lround(x));
            int py = static_cast<int>(std::lround(y));
            int n = 0;
            for (const auto& f : kMeteorFires) {
                if (std::find(touch.begin(), touch.end(), std::make_pair(px - f[0], py - f[1])) != touch.end()) {
                    n++;
                }
            }
            return static_cast<double>(n);
        };

        OverlapTable t;
        t.aimed = fires(0, 0);
        t.other.assign(41, 0.0);
        for (int k = 2; k <= 40; k++) {
            double radius = std::sqrt(k * a.packAreaPerMonster / kPi);
            double sum = 0;
            for (auto [x, y] : unitDisk()) {
                sum += fires(radius * x, radius * y);
            }
            t.other[k] = sum / unitDisk().size();
        }
        return &cache.emplace(key, std::move(t)).first->second;
    }

    PackHit Library::packHit(const Damage& d, double k, const Assumptions& a) const {
        PackHit plus = packHitFor(d, k, a, 2);
        PackHit box = packHitFor(d, k, a, 3);
        plus.boxScale = plus.aimed > 0 ? box.aimed / plus.aimed : 1.0;
        return plus;
    }

    PackHit Library::packHitFor(const Damage& d, double k, const Assumptions& a, int footprint) const {
        PackHit h;
        k = std::max(1.0, k);
        double mu = (d.hitMin + d.hitMax) / 2.0;
        double ex2 = (d.hitMin * d.hitMin + d.hitMin * d.hitMax + d.hitMax * d.hitMax) / 3.0;
        double overshoot = mu > 0 ? ex2 / (2.0 * mu) : 0.0;

        // Pack members spread over a disk; AoE coverage is the share of that
        // disk inside the spell's radius, a line's is the share of the strip
        // its missile must pass through to touch a monster's footprint.
        double packRadius = std::sqrt(k * a.packAreaPerMonster / kPi);
        auto coverage = [&](double r) { return k <= 1.0 ? 1.0 : std::min(1.0, r * r / (packRadius * packRadius)); };
        const ShapeFacts& shape = shapeFacts(d.missileSize, footprint);
        double line = k <= 1.0 ? 0.0 : std::min(1.0, 4.0 * shape.halfWidth / (kPi * packRadius));
        int slot = footprint >= 3 ? 1 : 0;
        auto tableOther = [&](const OverlapTable* t) {
            if (!t || k <= 1.0) {
                return 0.0;
            }
            double x = std::min(k, static_cast<double>(t->other.size() - 1));
            int lo = std::max(2, static_cast<int>(std::floor(x)));
            int hi = std::min(lo + 1, static_cast<int>(t->other.size() - 1));
            double f = std::clamp(x - lo, 0.0, 1.0);
            return t->other[lo] * (1 - f) + t->other[hi] * f;
        };

        const SkillInfo& s = info[d.skill];
        switch (s.geometry) {
            case Geometry::Single:
                h.aimed = mu;
                h.overshoot = overshoot;
                break;
            case Geometry::Splash:
                h.aimed = mu;
                h.other = mu * coverage(d.radius);
                h.overshoot = overshoot;
                break;
            case Geometry::Pierce:
                h.aimed = mu;
                h.other = mu * line;
                h.overshoot = overshoot;
                break;
            case Geometry::Ring:
                h.aimed = h.other = mu;
                h.overshoot = overshoot;
                break;
            case Geometry::ChargedBolt:
                // Bolts wander and land on whoever is near, so they spread evenly.
                h.aimed = h.other = d.count * a.chargedBoltHit * mu / k;
                h.overshoot = overshoot;
                break;
            case Geometry::Chain: {
                // Jumps go to the next unit by ID in range, wrapping, so they
                // cycle through the whole pack and can return.
                double jumps = std::max(0, d.count - 1);
                double reach = std::min(1.0, k - 1.0); // Needs a second target to jump to.
                h.aimed = mu * (1.0 + jumps * reach / k);
                h.other = mu * jumps / k;
                h.overshoot = overshoot;
                break;
            }
            case Geometry::FrozenOrb:
                h.aimed = d.overlap[slot] ? mu * d.overlap[slot]->aimed : 0.0;
                h.other = mu * tableOther(d.overlap[slot]);
                h.overshoot = overshoot;
                break;
            case Geometry::Blizzard: {
                // Each shard lands on a whole-subtile offset in a square of
                // side 2*radius and hits the monsters its plus shape touches.
                double inside = d.dotSeconds > 0 ? std::min(1.0, a.dwell / d.dotSeconds) : 1.0;
                double area = 4.0 * d.radius * d.radius;
                double chance = area > 0 ? std::min(1.0, shape.cells / area) : 0.0;
                h.aimed = h.other = mu * d.count * chance * inside;
                h.overshoot = overshoot;
                break;
            }
            case Geometry::Wall:
            case Geometry::Trail: {
                // Each segment is direct fire damage that hits every frame. The
                // tooltip counts 3 segments on a monster; one crossing a
                // straight wall touches shape.perRow on average. Walls stack.
                double time = std::min(s.geometry == Geometry::Wall ? a.dwell : a.trail, d.dotSeconds);
                h.aimed = h.other = mu * shape.perRow / 3.0 * time;
                break;
            }
            case Geometry::Meteor: {
                // Impact in a radius, plus one burn per fire touching the
                // monster (the tooltip counts 3).
                double perFire = (d.dotMin + d.dotMax) / 2.0 / 3.0 * std::min(a.dwell, d.dotSeconds);
                const OverlapTable* t = d.overlap[slot];
                h.aimed = mu + perFire * (t ? t->aimed : 3.0);
                h.other = mu * coverage(d.radius) + perFire * (t ? tableOther(t) : 0.0);
                h.overshoot = overshoot;
                break;
            }
            case Geometry::Summon:
                h.aimed = mu * d.count * a.summonUptime;
                h.overshoot = overshoot;
                break;
            case Geometry::Storm:
                // Each strike hits one enemy within Param7 subtiles, cycling
                // through them by unit ID, so the strikes spread over the pack.
                h.aimed = h.other = mu * d.count * a.summonUptime / k;
                h.overshoot = overshoot;
                break;
            case Geometry::Channel:
                h.aimed = mu;
                h.other = mu * line;
                h.overshoot = overshoot / 12.5; // The last flame, not the last second.
                break;
            case Geometry::None:
                break;
        }
        h.other = k <= 1.0 ? 0.0 : std::min(h.other, h.aimed);
        return h;
    }

}
