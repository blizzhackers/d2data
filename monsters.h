/**
 * Monster hit points, resistances and experience by difficulty, monster
 * level and quality, plus the per-area pack populations from the population
 * sim (pop/d2r-rotw_population.json).
 *
 * Hit points: (minHP + maxHP) / 2 from monstats.txt for the difficulty, times
 * monlvl.txt L-HP for the monster level / 100, times the quality bonus from
 * monumod.txt constants, times (players + 1) / 2.
 * Experience: monstats.txt Exp for the difficulty times monlvl.txt L-XP / 100,
 * times the quality multiplier (champion x3; unique, superunique and minion
 * x5), times (players + 1) / 2.
 * In Nightmare and Hell, monster levels come from the area; the population
 * sim already records each monster's level, champion and unique bonuses
 * included.
 */

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "txtrotw.h"

namespace Mon {

    enum Quality { Normal, Champion, Unique, Minion, SuperUnique, Boss, PrimeEvil, QualityCount };
    enum Difficulty { NormalDifficulty = 0, Nightmare = 1, Hell = 2 };

    const char* qualityName(int q);
    // Monster level a quality adds: champion +2, unique, superunique and minion +3.
    int levelBonus(int quality);
    const char* difficultyName(int d);
    int parseQuality(const std::string& s);       // -1 if unknown.
    int parseDifficulty(const std::string& s);    // -1 if unknown.

    struct Member {
        int monster = -1;   // Row in monstats.txt.
        int quality = Normal;
        int mlvl = 1;
        double count = 1;   // Per pack.
    };

    struct Pack {
        std::string name;   // Leader's name.
        double packs = 0;   // Packs per game.
        double size = 1;    // Monsters per pack.
        std::vector<Member> members; // Leader first, with count 1.
    };

    struct Area {
        int id = 0;
        std::string name;
        int act = 0;
        int difficulty = 0;
        int areaLevel = 0;
        double monsters = 0; // Per game.
        double walkable = 0; // Walkable subtiles.
        double packCount = 0; // Packs per game, superuniques included.
        std::vector<Pack> packs;
    };

    class Library {
    public:
        Library(const std::string& txtDir, const std::string& popFile);

        // Multiplayer games read monlvl.txt L-HP; single player reads HP.
        // Only Hell differs.
        void setOnline(bool on) { online = on; }

        int find(const std::string& id) const; // monstats Id; -1 if absent.
        const std::string& id(int monster) const { return stats[monster].Id; }
        int count() const { return static_cast<int>(stats.size()); }

        // Normal-difficulty monster level from monstats; NM/Hell use the area level.
        int baseLevel(int monster, int difficulty) const;

        // mlvl is the monster's actual level, quality bonus included. Hit
        // points and experience are computed at the level before the bonus,
        // then multiplied; the experience penalty uses the actual level.
        double hpMin(int monster, int difficulty, int mlvl, int quality, int players) const;
        double hpMax(int monster, int difficulty, int mlvl, int quality, int players) const;
        double hp(int monster, int difficulty, int mlvl, int quality, int players) const;
        // 0 fire, 1 lightning, 2 cold (matches Sorc::Element).
        int resist(int monster, int difficulty, int element) const;
        double experience(int monster, int difficulty, int mlvl, int quality, int players) const;
        bool killable(int monster) const { return stats[monster].killable != 0; }
        // Collision size from monstats2 SizeX: 1-2 is a plus-shaped
        // footprint, 3 a 3x3 box.
        int sizeX(int monster) const { return sizes[monster]; }

        // Share of a monster's experience a character of level clvl receives
        // from a monster of level mlvl: the level-difference penalty times the
        // high-level ExpRatio / 1024.
        double expShare(int clvl, int mlvl) const;
        // Experience needed to go from clvl to clvl + 1; 0 at the cap.
        int64_t expToNext(int clvl) const;

        const std::vector<Area>& areas() const { return areaList; }

        // Typical seconds from the nearest waypoint to the entrance of level
        // `id`: half the waypoint's level, then each level crossed on the way,
        // each about sqrt(walkable subtiles) across. Towns are walked;
        // elsewhere Teleport is used when `teleportSpeed` > 0 and the level
        // allows it. Speeds are in subtiles per second. 0 if the level has
        // its own waypoint.
        double approachSeconds(int id, double runSpeed, double teleportSpeed) const;

    private:
        std::vector<D2::ROTW::t_monstats> stats;
        std::vector<D2::ROTW::t_monlvl> levels;
        std::vector<int> constants;           // monumod.txt constants.
        std::vector<int> sizes;               // monstats2 SizeX per monstats row.
        std::vector<int64_t> expTable;        // Index = level, value = exp to reach level + 1.
        std::vector<int> expRatio;            // Index = level.
        int maxLevel = 99;                    // experience.txt MaxLvl.
        bool online = false;
        std::vector<Area> areaList;

        struct LevelNode {
            double across = 0;      // Subtiles.
            bool waypoint = false;
            bool town = false;
            bool teleport = true;   // levels.txt Teleport allows it.
            std::vector<int> links; // Levels you can walk or portal into.
        };
        std::vector<LevelNode> graph;  // Indexed by level id.
        void loadLevelGraph(const std::string& txtDir);

        const D2::ROTW::t_monlvl* levelRow(int mlvl) const;
        double hpBonus(int quality, int difficulty) const;
        void loadPopulation(const std::string& popFile);
    };

}
