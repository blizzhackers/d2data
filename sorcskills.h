/**
 * Sorceress spell damage library.
 *
 * Reads skills.txt and missiles.txt (ROTW) through the generated loaders and
 * computes per-hit damage, mana cost and cast timing for each sorceress skill
 * from its formulas, then turns that into expected damage per cast against a
 * pack of monsters using a per-spell geometry model.
 *
 * Damage follows the game's pipeline: base E-damage plus per-level brackets
 * (levels 2-8, 9-16, 17-22, 23-28, 29+), shifted by HitShift into 256ths,
 * then multiplied by (100 + synergy%) and by (100 + mastery%). Synergies read
 * hard points only (blvl); everything else reads the effective level (lvl).
 * Damage-over-time spells use the per-second conversion from their
 * skilldesc.txt tooltip formulas, which include overlapping missiles
 * (Fire Wall and Blaze show enms*25*3/256, Inferno enms*12/256).
 */

#pragma once

#include <array>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "txtrotw.h"

namespace Sorc {

    enum Element { Fire = 0, Lightning = 1, Cold = 2, NoElement = 3 };

    const char* elementName(Element e);

    // How a spell spreads its damage over a pack. See packHit().
    enum class Geometry {
        None,        // Not used as a killer (buffs, utility, weapon skills, Static Field).
        Single,      // Direct missile, always hits the aimed target only.
        Splash,      // Direct missile that explodes in a radius.
        Pierce,      // Line that passes through everything in its path.
        Ring,        // Nova around the caster.
        ChargedBolt, // Random bolts.
        Chain,       // Jumps between targets.
        FrozenOrb,   // Spiral of bolts from a moving orb.
        Blizzard,    // Shards falling in an area over time.
        Wall,        // Fire Wall: burning line monsters walk into.
        Trail,       // Blaze: burning trail behind the caster.
        Meteor,      // Impact in a radius plus burning ground.
        Summon,      // Hydra.
        Storm,       // Thunder Storm.
        Channel,     // Inferno: one "cast" is one second of channeling.
    };

    // Tunable assumptions for things the data files don't pin down.
    struct Assumptions {
        int fcr = 37;                      // Faster cast rate, for cast frames.
        double packAreaPerMonster = 9.0;   // Subtiles^2 per pack member: one 3x3 spawn cell each.
        double chargedBoltHit = 0.91;      // Share of bolts that hit something point-blank.
        double castDistance = 6.0;         // Subtiles from the caster to the pack's centre (Frozen Orb).
        double dwell = 2.0;                // Seconds a monster stays in Fire Wall, Blizzard or Meteor fire.
        double trail = 1.0;                // Seconds a monster spends in a Blaze trail.
        double hydraInterval = 35.0;       // Frames between Hydra shots.
        double summonUptime = 0.75;        // Share of a Hydra's or storm's life spent firing at something.
        bool thunderStorm = false;         // Allow Thunder Storm as a killer (degenerate for exp/mana).
        double runSpeed = 0;               // Subtiles per frame running: charstats RunVelocity / 16, set by the caller.
        double teleportRange = 25.0;       // Subtiles per Teleport cast: about as far as the screen lets you click.
    };

    // Expected hit counts by pack geometry that don't depend on skill level
    // (Frozen Orb bolts, Meteor fires): on the aimed monster, and on each
    // other member by pack size (index = size, 1..N).
    struct OverlapTable {
        double aimed = 0;
        std::vector<double> other;
    };

    struct SkillBonuses {
        int all = 0;
        int fire = 0;
        int lightning = 0;
        int cold = 0;
    };

    // Expected damage per cast against a pack, before resistance, for
    // monsters with the common plus-shaped footprint (monstats2 SizeX 1-2).
    struct PackHit {
        double aimed = 0;     // On the monster you aim at.
        double other = 0;     // On each other member of the same pack.
        double overshoot = 0; // Expected damage wasted on the killing hit, E[X^2]/2E[X].
        double boxScale = 1;  // Damage multiplier for 3x3 monsters (SizeX 3).
    };

    struct SkillInfo {
        std::string name;
        int row = -1;                 // Row in skills.txt.
        int reqlevel = 1;
        int tree = 0;                 // 0 fire, 1 lightning, 2 cold (skilldesc SkillPage - 1).
        Element element = NoElement;
        Geometry geometry = Geometry::None;
        std::vector<int> prereqs;     // Sorc skill indices.
        int mastery = -1;             // Sorc index of the mastery that boosts this skill.
        // synergy[c][y] = synergy % per hard point of sorc skill y, for damage
        // component c (0 = the skill itself, 1 = a secondary missile such as
        // Meteor's burning ground).
        std::vector<std::vector<double>> synergy;
        bool killer() const { return geometry != Geometry::None; }
    };

    struct Damage {
        int skill = -1;
        Element element = NoElement;
        int level = 0;             // Effective level.
        double hitMin = 0;         // Per hit, or per second for Wall/Trail/Channel.
        double hitMax = 0;
        double dotMin = 0;         // Meteor's burning ground, per second.
        double dotMax = 0;
        double dotSeconds = 0;     // Duration of a ground effect, seconds.
        double synergyPct[2] = { 0, 0 };
        double masteryPct = 0;     // + % damage from Fire/Lightning Mastery.
        int pierce = 0;            // - % enemy cold resistance from Cold Mastery.
        double mana = 0;           // Per cast; per second for Inferno.
        int castFrames = 0;        // Frames per cast at the assumed FCR.
        int cooldownFrames = 0;
        double secondsPerCast = 0; // Time between casts: cast frames or cooldown, whichever is longer.
        double deliverySeconds = 0; // From a cast until its damage has landed (orb flight, time in a wall, Meteor's fall).
        double delaySeconds = 0;    // Meteor: from the action frame to the impact.
        double minCast = 1;        // Smallest share of a cast you can spend; under 1 for channeling.
        double packMana = 0;       // Extra mana per pack engaged (Inferno's opening charge).
        double packSeconds = 0;    // Extra time per pack engaged.
        int missileSize = 1;       // missiles.txt Size of the missile that does the hitting.
        // Frozen Orb, in subtiles and frames.
        double orbSpeed = 0;
        double orbLife = 0;
        double boltRange = 0;
        int novaBolts = 0;
        double novaRange = 0;
        // Frozen Orb or Meteor geometry, for plus [0] and 3x3 [1] footprints.
        const OverlapTable* overlap[2] = { nullptr, nullptr };
        int count = 0;             // Bolts, chain hits, shards or shots per cast.
        double radius = 0;         // Subtiles; Blizzard's spawn half-width.
    };

    class Library {
    public:
        explicit Library(const std::string& dir);

        int size() const { return static_cast<int>(info.size()); }
        // charstats.txt RunVelocity and WalkVelocity for the Sorceress.
        int runVelocity() const { return run; }
        int walkVelocity() const { return walk; }
        int find(const std::string& name) const; // Case-insensitive; -1 if absent.
        const SkillInfo& skill(int i) const { return info[i]; }
        const std::vector<SkillInfo>& skills() const { return info; }

        // Prereq closure of a skill, including the skill itself.
        std::vector<int> closure(int skill) const;

        // Effective level for a skill with the given hard points.
        int effectiveLevel(int skill, int hard, const SkillBonuses& bonus) const;

        // Damage of `skill` at effective level `lvl`, with the given synergy %
        // per component and the effective level of its mastery (0 = none).
        Damage compute(int skill, int lvl, const double synergyPct[2], int masteryLvl, const Assumptions& a) const;

        // Damage from a full hard-point allocation (indexed by sorc skill).
        Damage compute(int skill, const std::vector<int>& hard, const SkillBonuses& bonus, const Assumptions& a) const;

        // Synergy % per component from hard points.
        void synergyFromHard(int skill, const std::vector<int>& hard, double out[2]) const;

        // Expected damage per cast against a pack of average size k.
        PackHit packHit(const Damage& d, double k, const Assumptions& a) const;

        // Damage from passive mastery at an effective level.
        int masteryValue(int masterySkill, int lvl) const;

    private:
        std::vector<D2::ROTW::t_skills> skillRows;
        std::vector<D2::ROTW::t_missiles> missileRows;
        std::vector<D2::ROTW::t_skilldesc> descRows;
        std::vector<SkillInfo> info;
        std::array<int, 3> masteryByElement = { -1, -1, -1 };
        int run = 0;
        int walk = 0;

        // Geometry that doesn't depend on skill level, cached by its inputs.
        mutable std::mutex cacheLock;
        mutable std::map<std::string, OverlapTable> cache;
        const OverlapTable* orbHits(const Damage& d, const Assumptions& a, int footprint) const;
        const OverlapTable* meteorFires(const Damage& d, const Assumptions& a, int footprint) const;
        PackHit packHitFor(const Damage& d, double k, const Assumptions& a, int footprint) const;

        int missileRow(const std::string& name) const;
        int64_t evalSkill(const std::string& expr, int row, int lvl, int blvl) const;
        int64_t missileRange(int missile, int lvl) const;
    };

}
