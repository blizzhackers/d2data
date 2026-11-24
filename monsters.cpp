#include "monsters.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_map>

#include "minijson.h"

namespace Mon {

    namespace {

        std::string lower(std::string s) {
            for (char& ch : s) {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            return s;
        }

        const char* kQualities[QualityCount] = { "normal", "champion", "unique", "minion", "superunique", "boss", "primevil" };
        const char* kDifficulties[3] = { "normal", "nightmare", "hell" };

        // Experience multipliers by quality (not in the data files).
        const double kExpMultiplier[QualityCount] = { 1, 3, 5, 5, 5, 1, 1 };

    }

    const char* qualityName(int q) {
        return q >= 0 && q < QualityCount ? kQualities[q] : "?";
    }

    int levelBonus(int quality) {
        switch (quality) {
            case Champion: return 2;
            case Unique:
            case SuperUnique:
            case Minion: return 3;
            default: return 0;
        }
    }

    const char* difficultyName(int d) {
        return d >= 0 && d < 3 ? kDifficulties[d] : "?";
    }

    int parseQuality(const std::string& s) {
        std::string l = lower(s);
        for (int q = 0; q < QualityCount; q++) {
            if (l == kQualities[q]) {
                return q;
            }
        }
        return -1;
    }

    int parseDifficulty(const std::string& s) {
        std::string l = lower(s);
        if (l == "normal" || l == "n" || l == "0") return NormalDifficulty;
        if (l == "nightmare" || l == "nm" || l == "1") return Nightmare;
        if (l == "hell" || l == "h" || l == "2") return Hell;
        return -1;
    }

    Library::Library(const std::string& txtDir, const std::string& popFile) {
        stats = D2::ROTW::t_monstats::readfile(txtDir + "monstats.txt");
        levels = D2::ROTW::t_monlvl::readfile(txtDir + "monlvl.txt");
        for (const auto& row : D2::ROTW::t_monumod::readfile(txtDir + "monumod.txt")) {
            constants.push_back(row.constants);
        }
        for (const auto& row : D2::ROTW::t_experience::readfile(txtDir + "experience.txt")) {
            if (row.Level == "MaxLvl") {
                maxLevel = static_cast<int>(row.Sorceress);
                continue;
            }
            if (row.Level.empty() || !std::isdigit(static_cast<unsigned char>(row.Level[0]))) {
                continue;
            }
            size_t lvl = static_cast<size_t>(std::stoi(row.Level));
            if (expTable.size() <= lvl) {
                expTable.resize(lvl + 1, 0);
                expRatio.resize(lvl + 1, 1024);
            }
            expTable[lvl] = row.Sorceress;
            expRatio[lvl] = row.ExpRatio;
        }

        std::unordered_map<std::string, int> sizeById;
        for (const auto& row : D2::ROTW::t_monstats2::readfile(txtDir + "monstats2.txt")) {
            sizeById[row.Id] = row.SizeX;
        }
        for (const auto& m : stats) {
            auto it = sizeById.find(m.MonStatsEx.empty() ? m.Id : m.MonStatsEx);
            sizes.push_back(it == sizeById.end() ? 2 : it->second);
        }

        if (stats.empty() || levels.empty() || constants.size() < 10 || expTable.empty() || sizeById.empty()) {
            throw std::runtime_error("Could not read monstats.txt, monlvl.txt, monumod.txt or experience.txt from " + txtDir);
        }

        loadPopulation(popFile);
        loadLevelGraph(txtDir);
    }

    void Library::loadLevelGraph(const std::string& txtDir) {
        auto rows = D2::ROTW::t_levels::readfile(txtDir + "levels.txt");
        int maxId = 0;
        for (const auto& r : rows) {
            maxId = std::max(maxId, r.Id);
        }
        graph.assign(maxId + 1, LevelNode());

        auto link = [&](int a, int b) {
            if (a <= 0 || b <= 0 || a > maxId || b > maxId || a == b) {
                return;
            }
            auto& la = graph[a].links;
            auto& lb = graph[b].links;
            if (std::find(la.begin(), la.end(), b) == la.end()) {
                la.push_back(b);
            }
            if (std::find(lb.begin(), lb.end(), a) == lb.end()) {
                lb.push_back(a);
            }
        };

        // Walkable size from the population sim where it has one, else the
        // level's tile size (5 subtiles a tile, about half of it walkable).
        std::vector<double> walkable(maxId + 1, 0.0);
        for (const auto& a : areaList) {
            if (a.id >= 0 && a.id <= maxId) {
                walkable[a.id] = std::max(walkable[a.id], a.walkable);
            }
        }
        for (const auto& r : rows) {
            if (r.Id <= 0) {
                continue;
            }
            LevelNode& n = graph[r.Id];
            double size = walkable[r.Id] > 0 ? walkable[r.Id] : std::max(0, r.SizeX) * 5.0 * std::max(0, r.SizeY) * 5.0 * 0.5;
            n.across = std::sqrt(size);
            n.waypoint = r.Waypoint != 255;
            n.teleport = r.Teleport != 0;
            for (int v : { r.Vis0, r.Vis1, r.Vis2, r.Vis3, r.Vis4, r.Vis5, r.Vis6, r.Vis7 }) {
                link(r.Id, v); // Dungeon entrances and stairs.
            }
        }
        for (int town : { 1, 40, 75, 103, 109 }) {
            if (town <= maxId) {
                graph[town].town = true;
            }
        }

        // Outdoor borders, built by the outdoor generator rather than levels.txt.
        const int chains[][9] = {
            { 1, 2, 3, 4, 5, 6, 7, 26, 0 },        // Rogue Encampment to Monastery Gate.
            { 40, 41, 42, 43, 44, 45, 0 },         // Lut Gholein to Valley of Snakes.
            { 75, 76, 77, 78, 79, 80, 81, 82, 83 },// Kurast Docks to Travincal.
            { 103, 104, 105, 106, 0 },             // Pandemonium Fortress to City of the Damned.
            { 109, 110, 111, 112, 0 },             // Harrogath to Arreat Plateau.
        };
        for (const auto& chain : chains) {
            for (int i = 0; i + 1 < 9 && chain[i + 1]; i++) {
                link(chain[i], chain[i + 1]);
            }
        }
        link(3, 17); // Burial Grounds off the Cold Plains.

        // Portals.
        link(1, 39);    // Cow Level, from the Rogue Encampment (approachSeconds adds the trip for Wirt's Leg).
        link(4, 38);    // Tristram, from the Stony Field.
        link(54, 74);   // Arcane Sanctuary, from Palace Cellar 3.
        link(74, 46);   // Canyon of the Magi, from the Summoner.
        for (int tomb = 66; tomb <= 72; tomb++) {
            link(tomb, 73); // Duriel's Lair, from the true tomb.
        }
        link(109, 121); // Nihlathak's Temple, from Harrogath.
        link(111, 125); // Abaddon, from the Frigid Highlands.
        link(112, 126); // Pit of Acheron, from the Arreat Plateau.
        link(117, 127); // Infernal Pit, from the Frozen Tundra.
        for (int uber = 133; uber <= 136; uber++) {
            link(109, uber); // Pandemonium event, from Harrogath.
        }
    }

    double Library::approachSeconds(int id, double runSpeed, double teleportSpeed) const {
        if (id <= 0 || id >= static_cast<int>(graph.size()) || graph[id].waypoint || runSpeed <= 0) {
            return 0;
        }
        auto speed = [&](const LevelNode& n) {
            return (teleportSpeed > 0 && n.teleport && !n.town) ? teleportSpeed : runSpeed;
        };

        // The Cow Level portal uses up Wirt's Leg: reach Tristram, cross it
        // to his corpse at the far end, portal home and cross town to cube
        // the leg and open the portal.
        if (id == 39 && graph.size() > 39) {
            const LevelNode& tristram = graph[38];
            const LevelNode& town = graph[1];
            return approachSeconds(38, runSpeed, teleportSpeed) + tristram.across / speed(tristram) + town.across / 2 / speed(town);
        }
        // Dijkstra outward from the target: crossing a level costs its full
        // width; the search ends at a waypoint level, crossed halfway.
        const double inf = std::numeric_limits<double>::infinity();
        std::vector<double> best(graph.size(), inf);
        using Item = std::pair<double, int>;
        std::priority_queue<Item, std::vector<Item>, std::greater<Item>> open;
        best[id] = 0;
        open.push({ 0, id });
        double answer = inf;
        while (!open.empty()) {
            auto [t, v] = open.top();
            open.pop();
            if (t > best[v] || t >= answer) {
                continue;
            }
            for (int w : graph[v].links) {
                const LevelNode& n = graph[w];
                if (n.waypoint) {
                    answer = std::min(answer, t + n.across / 2 / speed(n));
                    continue;
                }
                double next = t + n.across / speed(n);
                if (next < best[w]) {
                    best[w] = next;
                    open.push({ next, w });
                }
            }
        }
        return std::isfinite(answer) ? answer : 0;
    }

    int Library::find(const std::string& id) const {
        std::string l = lower(id);
        for (size_t i = 0; i < stats.size(); i++) {
            if (lower(stats[i].Id) == l) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    const D2::ROTW::t_monlvl* Library::levelRow(int mlvl) const {
        for (const auto& row : levels) {
            if (row.Level == mlvl) {
                return &row;
            }
        }
        return nullptr;
    }

    int Library::baseLevel(int monster, int difficulty) const {
        const auto& m = stats[monster];
        return difficulty == Hell ? m.LevelH : difficulty == Nightmare ? m.LevelN : m.Level;
    }

    double Library::hpBonus(int quality, int difficulty) const {
        // monumod.txt constants: 1-3 minion, 4-6 champion, 7-9 unique HP % bonus.
        int base = quality == Minion ? 1 : quality == Champion ? 4 : (quality == Unique || quality == SuperUnique) ? 7 : -1;
        if (base < 0) {
            return 1.0;
        }
        return 1.0 + constants[base + difficulty] / 100.0;
    }

    double Library::hpMin(int monster, int difficulty, int mlvl, int quality, int players) const {
        const auto& m = stats[monster];
        const auto* lv = levelRow(mlvl - levelBonus(quality));
        if (!lv) {
            return 0;
        }
        int base = difficulty == Hell ? m.MinHPH : difficulty == Nightmare ? m.MinHPN : m.minHP;
        int scale = difficulty == Hell ? (online ? lv->LHPH : lv->HPH) : difficulty == Nightmare ? lv->HPN : lv->HP;
        return static_cast<double>(static_cast<int64_t>(base) * scale / 100) * hpBonus(quality, difficulty) * (players + 1) / 2.0;
    }

    double Library::hpMax(int monster, int difficulty, int mlvl, int quality, int players) const {
        const auto& m = stats[monster];
        const auto* lv = levelRow(mlvl - levelBonus(quality));
        if (!lv) {
            return 0;
        }
        int base = difficulty == Hell ? m.MaxHPH : difficulty == Nightmare ? m.MaxHPN : m.maxHP;
        int scale = difficulty == Hell ? (online ? lv->LHPH : lv->HPH) : difficulty == Nightmare ? lv->HPN : lv->HP;
        return static_cast<double>(static_cast<int64_t>(base) * scale / 100) * hpBonus(quality, difficulty) * (players + 1) / 2.0;
    }

    double Library::hp(int monster, int difficulty, int mlvl, int quality, int players) const {
        return std::max(1.0, (hpMin(monster, difficulty, mlvl, quality, players) + hpMax(monster, difficulty, mlvl, quality, players)) / 2.0);
    }

    int Library::resist(int monster, int difficulty, int element) const {
        const auto& m = stats[monster];
        switch (element) {
            case 0: return difficulty == Hell ? m.ResFiH : difficulty == Nightmare ? m.ResFiN : m.ResFi;
            case 1: return difficulty == Hell ? m.ResLiH : difficulty == Nightmare ? m.ResLiN : m.ResLi;
            case 2: return difficulty == Hell ? m.ResCoH : difficulty == Nightmare ? m.ResCoN : m.ResCo;
            default: return 0;
        }
    }

    double Library::experience(int monster, int difficulty, int mlvl, int quality, int players) const {
        const auto& m = stats[monster];
        const auto* lv = levelRow(mlvl - levelBonus(quality));
        if (!lv) {
            return 0;
        }
        int base = difficulty == Hell ? m.ExpH : difficulty == Nightmare ? m.ExpN : m.Exp;
        int scale = difficulty == Hell ? lv->LXPH : difficulty == Nightmare ? lv->LXPN : lv->LXP;
        double q = quality >= 0 && quality < QualityCount ? kExpMultiplier[quality] : 1.0;
        return static_cast<double>(static_cast<int64_t>(base) * scale / 100) * q * (players + 1) / 2.0;
    }

    double Library::expShare(int clvl, int mlvl) const {
        int diff = mlvl - clvl;
        int share256 = 256;
        if (diff < -5) {
            // Monster well below you, at any character level.
            static const int below[] = { 207, 159, 110, 61 }; // -6 .. -9
            share256 = diff <= -10 ? 13 : below[-diff - 6];
        }
        else if (diff > 5 && clvl < 25) {
            static const int above[] = { 225, 174, 92, 38 }; // +6 .. +9
            share256 = diff >= 10 ? 5 : above[diff - 6];
        }

        double share = share256 / 256.0;
        if (diff > 0 && clvl >= 25) {
            share = static_cast<double>(clvl) / mlvl;
        }

        int ratio = clvl >= 0 && clvl < static_cast<int>(expRatio.size()) ? expRatio[clvl] : 1024;
        return share * ratio / 1024.0;
    }

    int64_t Library::expToNext(int clvl) const {
        if (clvl < 1 || clvl >= maxLevel || clvl >= static_cast<int>(expTable.size())) {
            return 0;
        }
        return expTable[clvl] - expTable[clvl - 1];
    }

    void Library::loadPopulation(const std::string& popFile) {
        MiniJson::Value root = MiniJson::parseFile(popFile);
        const MiniJson::Value* lvls = root.get("levels");
        if (!lvls || !lvls->isArray()) {
            throw std::runtime_error("No levels in " + popFile);
        }

        std::unordered_map<std::string, int> index;
        for (size_t i = 0; i < stats.size(); i++) {
            index[stats[i].Id] = static_cast<int>(i);
        }
        auto monsterIndex = [&](const std::string& id) {
            auto it = index.find(id);
            return it == index.end() ? -1 : it->second;
        };

        // members: { monster id: { quality: { mlvl: count per game } } }
        auto addMembers = [&](Pack& pack, const MiniJson::Value* members) {
            if (!members || !members->isObject()) {
                return;
            }
            for (const auto& [mid, byQuality] : members->obj) {
                int mon = monsterIndex(mid);
                for (const auto& [q, byLevel] : byQuality.obj) {
                    for (const auto& [ml, n] : byLevel.obj) {
                        if (mon < 0 || pack.packs <= 0) {
                            continue;
                        }
                        Member m;
                        m.monster = mon;
                        m.quality = std::max(0, parseQuality(q));
                        m.mlvl = std::stoi(ml);
                        m.count = n.num / pack.packs;
                        pack.members.push_back(m);
                        pack.size += m.count;
                    }
                }
            }
        };

        for (const auto& lvl : lvls->arr) {
            const MiniJson::Value* diffs = lvl.get("difficulties");
            if (!diffs || !diffs->isObject() || diffs->obj.empty()) {
                continue;
            }
            for (const auto& [dname, d] : diffs->obj) {
                Area area;
                area.id = static_cast<int>(lvl.number("id"));
                area.name = lvl.string("name");
                area.act = static_cast<int>(lvl.number("act"));
                area.difficulty = parseDifficulty(dname);
                area.areaLevel = static_cast<int>(d.number("areaLevel"));
                area.monsters = d.number("total");
                if (const MiniJson::Value* surface = d.get("area")) {
                    area.walkable = surface->number("walkableSubtiles");
                }
                if (area.difficulty < 0) {
                    continue;
                }

                if (const MiniJson::Value* packs = d.get("packs")) {
                    for (const auto& [mid, p] : packs->obj) {
                        int leader = monsterIndex(mid);
                        const MiniJson::Value* types = p.get("types");
                        if (leader < 0 || !types) {
                            continue;
                        }
                        for (const auto& [q, byLevel] : types->obj) {
                            for (const auto& [ml, bucket] : byLevel.obj) {
                                Pack pack;
                                pack.name = p.string("name");
                                pack.packs = bucket.number("packs");
                                pack.members.push_back({ leader, std::max(0, parseQuality(q)), std::stoi(ml), 1.0 });
                                addMembers(pack, bucket.get("members"));
                                if (pack.packs > 0) {
                                    area.packs.push_back(std::move(pack));
                                }
                            }
                        }
                    }
                }

                if (const MiniJson::Value* supers = d.get("superuniques")) {
                    for (const auto& [name, su] : supers->obj) {
                        int leader = monsterIndex(su.string("monster"));
                        const MiniJson::Value* byLevel = su.get("mlvl");
                        if (leader < 0 || !byLevel) {
                            continue;
                        }
                        for (const auto& [ml, bucket] : byLevel->obj) {
                            Pack pack;
                            pack.name = name;
                            pack.packs = bucket.number("packs");
                            pack.members.push_back({ leader, SuperUnique, std::stoi(ml), 1.0 });
                            addMembers(pack, bucket.get("members"));
                            if (pack.packs > 0) {
                                area.packs.push_back(std::move(pack));
                            }
                        }
                    }
                }

                for (const auto& p : area.packs) {
                    area.packCount += p.packs;
                }
                areaList.push_back(std::move(area));
            }
        }
    }

}
