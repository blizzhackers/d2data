# sorcbuild: sorceress leveling optimizer

`sorcbuild` finds the sorceress skill allocation with the most experience per second at a given character level, and the areas that build should farm. `--epm` ranks by experience per mana instead. It reads the ROTW tables in `txt/` and the area populations in `pop/d2r-rotw_population.json`.

```
./sorcbuild 24                                   # best build per main skill and top 5 areas, as JSON
./sorcbuild 60 --skills 2 --cold-skills 1 --quest-skills 12
./sorcbuild 40 --skill "Blizzard" --top 10       # only consider Blizzard as the main skill
./sorcbuild skill "Meteor" 20 "Fire Bolt=20" "Fire Ball=20" "Fire Mastery=10"
./sorcbuild monster hellbovine --diff hell --mlvl 81 --clvl 75
```

`php sorc-levels.php > sorc-levels.md` runs `sorcbuild` for every level from 2 to 98 and formats the JSON as a markdown table. It has one `level()` line per level, so each level's bonus skills, quest points, required skills and previous build (`--prev`) can be tuned there.

## Output

`sorcbuild <level>` prints one JSON object:

- `objective`: `expPerSecond`, or `expPerMana` with `--epm`; `rush`: whether every area was open; `trees`: the trees points could go in.
- `progression`: `enforced`, `maxSeconds`, the `difficulty` being worked through, and the `areas` a build must be able to clear.
- `level`, `points` (hard points to spend), `questSkills`, `bonus` (`all`, `fire`, `lightning`, `cold`), `players`, `fcr`.
- `required` and `previous`: the `--require` skills and the `--prev` build (`skill`, `points`).
- `warnings`: for example, a required skill that isn't available yet.
- `expToNext`: experience from this level to the next; 0 at the cap.
- `builds`: the best build for each main skill, best first; empty when nothing is available. Each has:
  - `skill` (two names joined by ` + ` for a hybrid), `hybrid`, `expPerSecond`, `expPerMana`, `secondsToNext`, `manaToNext`, `unspent`, `teleport` (whether the build has Teleport for travel), and `progressionSeconds` (time to clear the progression areas);
  - `allocation`: hard `points` and effective `level` per skill, main skill first;
  - `added`: points beyond `--prev`;
  - `damage` (and `secondaryDamage` for a hybrid's second skill): `skill`, `element`, `min`/`max` per hit (per second if `perSecond`), Meteor's `burnMin`/`burnMax`/`burnSeconds`, `count` (bolts, chain hits or shots), `radiusYards`, `mana` (per second if `manaPerSecond`), `synergy`/`burnSynergy`/`mastery` in %, cold `pierce`, `castFrames`, `cooldownFrames`, `secondsPerCast`;
  - `areas`: the top `--top` areas, each with `id`, `name`, `act`, `difficulty`, `areaLevel`, `expPerMana`, `expPerSecond`, `expPerClear`, `combatSeconds`, `travelSeconds` (including `approachSeconds` from the waypoint), `manaPerClear`, and `killable` (the share of the area's experience the build can take).

Bad arguments print an error to stderr and exit with status 1. `sorcbuild skill` and `sorcbuild monster` still print text.

Build it with `./build.sh`, or on its own:

```
g++ sorcbuild.cpp sorcskills.cpp monsters.cpp txtrotw.cpp -o sorcbuild -std=c++17 -O3 -pthread
```

## Options

| Option | Meaning |
|-|-|
| `--skills N`, `--fire-skills N`, `--lightning-skills N`, `--cold-skills N` | Bonus skill levels. They apply only to skills with a hard point and raise damage and mana cost, but not synergies, which read hard points. |
| `--quest-skills N` | Extra hard points on top of one per level after level 1. |
| `--players N` | Players setting. Monster life and experience scale by (N + 1) / 2. |
| `--online` | Multiplayer game: Hell monsters use monlvl.txt `L-HP`. Single player, the default, uses `HP`; the two only differ in Hell. |
| `--fcr N` | Faster cast rate, 37 by default: 10 frames per cast, 15 for Lightning and Chain Lightning. |
| `--top N` | Number of areas to list. |
| `--skill "Name"` | Only optimize for this main skill. |
| `--prev "<build>"` | The previous level's build, pasted from the `Points:` line or the table's Build column (`Fire Ball 6, Fire Bolt 11 (13); 2 unspent`), or as `Fire Ball=6,Fire Bolt=11`. No skill may drop below these hard points, so the result is a real next step instead of a respec. The output adds an `Added:` line with the new points. |
| `--fire`, `--lightning`, `--cold` | Only spend points in these trees; combine them freely, and none means all three. With `--fire` alone it won't pick Nova, say. Skills from `--prev` and `--require` stay in the build even outside these trees, but get no extra points. Teleport (with Telekinesis) can still be added for travel whatever the trees. |
| `--require "A,B"` | Every build must put a point in these skills and their prerequisites, e.g. `Telekinesis,Teleport`. Skills not yet available at the level are ignored with a warning. |
| `--hybrid`, `--progression` | The same mode under two names. Builds, including hybrids of two main skills cast together, are chosen by how fast they clear what progression needs in the difficulty being leveled through, and every area is then judged against the chosen build (both below). `--hybrid-step N` sets how finely points are split between the two skills (default 1). |
| `--rush` | Consider every area at every level, as if rushed. Without it, areas follow the Ancients gates (below). |
| `--epm` | Rank by experience per mana, the original objective, instead of per second. Travel doesn't count, and Teleport isn't added for travel. |
| `--teleport-range D` | Subtiles covered per Teleport (default 25, about as far as you can click). |
| `--allow-thunderstorm` | Allow Thunder Storm as the main skill (see Limits). |
| `--data DIR` | Repository root holding `txt/` and `pop/`, by default the executable's directory. |

The model options are described under Assumptions.

## What is optimized

For level L there are L − 1 + quest hard points. A skill can hold at most min(20, L − reqlevel + 1) hard points, and needs one point in each prerequisite. For each main skill, the optimizer searches:

- the main skill's level, which sets both damage and mana cost;
- its element's mastery level;
- which synergy skills to unlock, including any prerequisites they need;
- a knapsack DP over the unlocked synergy skills that finds the most synergy % for each number of spare points. When a skill has two damage parts with different synergies (Meteor's impact and its burning ground), the DP keeps the Pareto front.

Allocations are pruned to those not beaten on every damage multiplier and on cold pierce. Each survivor is scored against every reachable area, and a build's value is its best area's experience per second (or per mana with `--epm`).

**Reachable areas.** The Ancients let you into the Worldstone Keep at level 20 in Normal, 40 in Nightmare and 60 in Hell, and beating Baal opens the next difficulty. So, unless `--rush` is given:

- Nightmare needs level 20 and Hell needs level 40.
- The Worldstone Keep levels, the Throne of Destruction, the Worldstone Chamber and the Cow Level (which needs Baal dead) need 20 in Normal, 40 in Nightmare and 60 in Hell.
- The Pandemonium areas only count in Hell, where the event exists.

Other gates, such as quests and waypoints, aren't modeled; the top-N area list is there for those.

**Progression (`--hybrid` / `--progression`).** The difficulty a character levels in is Normal below 20, Nightmare from 20 to 39 and Hell from 40. Acts 1 and 2 need no particular kills, and the Ancients are random, so they're ignored. A build must be able to kill:

- the High Council in that difficulty's Travincal (Act 3);
- everything in that difficulty's Chaos Sanctuary (Act 4), since the seal bosses can't be sniped;
- everything in that difficulty's Throne of Destruction plus Baal's five waves (Act 5), once its Ancients are passed at 20/40/60. At exactly 20 and 40 the previous difficulty's Throne counts too, since that's when it gets cleared.

In this mode builds are chosen by how fast they clear those areas together: one run through them, combat and travel included, approach from the waypoint too. A build must be able to kill everything there, with a main skill each monster isn't immune to. Once the build is chosen, every area is judged against it, and its leveling numbers (`expPerSecond`, `secondsToNext`, the top areas) come from that. So the answer is the build that gets you through the difficulty fastest, plus the best place to level with it. `progressionSeconds` is its clear time. In Normal nothing there is immune. Nightmare's Chaos has fire-immune Doom Knights, and its Throne and Hell's Chaos and Throne have immunes of every element, so those need two elements.

**Hybrids** (same mode) pair two main skills that are worth casting together:

- **Different elements:** each covers the other's immunes.
- **One timed, one not:** a timed skill can't be cast back to back. It has a cooldown (Frozen Orb, Blizzard, Meteor, Fire Wall) or lasts (Hydra, Thunder Storm), and the other skill fills its downtime.
- **Thunder Storm with anything:** once cast it needs no casting, so it pairs with timed and untimed skills alike, even though it isn't a main skill on its own. It strikes every `perdelay` frames for `auralencalc` frames, one enemy within 17 subtiles per strike, cycling through them, so its damage spreads over the pack.

The pair's elements must also cover what progression needs.

Each pack is fought whichever way is fastest, or cheapest with `--epm`:

- one skill at its own rate with the other cast in its downtime, in either order; or
- one skill alone, then the other on what the first couldn't kill.

Every monster takes damage from each skill it isn't immune to, and the fight is solved with the same fluid model as for one skill, per second.

To find the allocation, the single-skill optimizer first finds each skill's best allocation for every point budget (every `--hybrid-step` points), judged on the progression areas. Each pair then tries each budget for one skill with the largest budget for the other that still fits, counting shared points (prerequisites, Teleport, `--require`, `--prev`) once. The best five pairs are scored again with the combined allocation, so cross synergies like Fire Ball and Meteor count. A hybrid is only listed if it clears faster than both of its skills on their own.

Teleport only speeds up travel, so for experience per second each main skill is optimized twice, with and without a point in Teleport (and Telekinesis), and the better build is kept.

## Time

An area's time is combat plus travel, with mana assumed unlimited (potions):

- **Combat:** for each pack, (casts − 1) × the cast interval + the time the last cast takes to land. The interval is cast frames at the FCR or the cooldown, whichever is longer. Landing time is the cast itself for most spells. For Frozen Orb it's the orb's 30-frame flight, for Fire Wall and Blizzard the time monsters spend in them (`--dwell`), and for Meteor the 60-frame fall plus the burn. Inferno counts its channel time plus a 15-frame start per pack.
- **Travel:** first the trip from the nearest waypoint to the area, then the route around its packs. The trip is the quickest chain of levels from a waypoint, using `levels.txt` dungeon links (`Vis0`–`Vis7`) plus the outdoor borders and portals the game builds itself (Cow Level and Pandemonium from town, Tristram, Arcane Sanctuary, Duriel, Nihlathak, the red portals). It counts half the waypoint's level and each level crossed in full, a level being about √(walkable subtiles) across. Areas with their own waypoint cost nothing. Each Cow Level run also fetches Wirt's Leg: to Tristram from the Stony Field waypoint, across Tristram to the corpse, then across town to cube it. Towns are always walked. It's a typical estimate, not a maze path. The packs are spread over the area's walkable subtiles from the population sim, and the route through them is the expected shortest tour through that many random points, 0.7124 × √(packs × walkable subtiles). On foot it's walked at the base run speed, `RunVelocity` / 16 = 0.5625 subtiles a frame (14 a second) with no faster run/walk. With Teleport it's covered in `--teleport-range` hops of one cast each (25 subtiles per 0.4 s at 37% FCR, through walls).

## Skill damage (sorcskills.cpp)

Damage follows the tables: `EMin`/`EMax` plus the per-level brackets (levels 2–8, 9–16, 17–22, 23–28, 29+), shifted by `HitShift`. That is multiplied by (100 + synergy %), with synergies from `EDmgSymPerCalc` evaluated on hard points, and then by (100 + mastery %). Mana cost is (`mana` + `lvlmana` × (lvl − 1)) × 2^`manashift` / 256, never less than `minmana`. Calc strings are evaluated by `d2calc.h`.

The mechanics below were checked against the 1.14d game code, which D2R shares apart from synergies.

- **Inferno:** every start command charges the per-cast cost once. While channeling, the sequence repeats every 2 frames, so a second holds 12.5 charges and 12.5 flames: (23 + slvl) × 25/128 mana per second (4.7/s at level 1, 8.4/s at level 20). The opening 15-frame sequence is charged but makes no flame, so each pack costs one extra charge. `startmana` is only required, never spent. Each flame passes through and hits each monster in its line once, for the per-frame damage; the D2R tooltip's ×12 is 12.5 truncated. Inferno is billed per flame, so a monster that dies in 3 flames costs 3 charges, not a second.
- **Fire Wall:** the maker places one single-cell segment per subtile. Fire Wall is fire type, so each segment is direct damage that hits once per frame, and everything stacks: several segments under one monster, and overlapping walls. In 1.14d only burn-type damage shares a single burning state per monster, so it doesn't stack. The tooltip's ×3 is three segments under one monster. A 3×3 monster (monstats2 `SizeX` 3) always touches 3; a plus-shaped one (`SizeX` 1–2, three quarters of all monsters) touches 5/3 on average while crossing.
- **Meteor's burning ground:** 18 `meteorfire` patches in a fixed pattern about ±4 subtiles across, each lasting Meteor's `ln34` frames (1.2 s at level 1, 12.6 s at level 20). They're fire type too, so a monster burns once per frame for each patch its footprint touches, and casts stack. The tooltip counts 3 patches.
- **Blizzard:** one shard every `calc2` frames (6.25/s), on a whole-subtile offset in a 12 × 12 square (`calc1`). A shard hits the monsters its plus shape touches: 13 of 144 offsets for a plus-shaped monster, 21 for a 3×3 one.
- **Frozen Orb:** the orb flies (Vel × 0.75/16 =) 0.47 subtiles a frame for 30 frames, firing one bolt a frame with the direction stepping 106.875°, then a 16-bolt nova (64 / `sHitPar1`) where it expires. Bolts fly 21 subtiles and die on their first hit.
- **Hydra:** three heads per cast, each firing at the Hydra skill's level and damage.
- **Masteries** multiply after synergies: base × (100 + synergy)/100 × (100 + mastery)/100. Fire Mastery covers Fire Wall, Meteor's burning ground (`ApplyMastery`) and Hydra. Cold Mastery lowers enemy cold resistance, never below −100, and does nothing to monsters at 100 or more.
- **Collision:** monsters with monstats2 `SizeX` 2 have a plus-shaped footprint and `SizeX` 3 a 3×3 box (`SizeX` 1, 0.1% of monsters, is a single cell; it's treated as a plus). Missiles test a single cell (`Size` 0–1), a plus (2) or a 3×3 box (3), and hit when the shapes share a subtile. Moving missiles test only the subtiles they enter, never their spawn subtile. Stationary ones (Fire Wall, Meteor's fires, Blizzard shards) re-test their own subtile every frame and hit one unit per frame. A Blizzard shard can't hit the same monster twice in a row, so it hits a lone monster once.

The killers modeled are Fire Bolt, Ice Bolt, Ice Blast, Charged Bolt, Fire Ball, Glacial Spike, Lightning, Inferno, Nova, Frost Nova, Chain Lightning, Frozen Orb, Blizzard, Fire Wall, Blaze, Meteor and Hydra. Blaze is never picked as the main skill, since it only burns where you walk. It still takes its one prerequisite point for Fire Wall, and `--skill Blaze` evaluates it on request. The armors, Energy Shield, Teleport, Telekinesis, Enchant (a weapon skill), Static Field and Warmth only count as synergies and prerequisites.

## Packs and geometry

Each pack in the population sim is scored separately: its average size, and each member's quality, level, HP, resistances and experience. Members of a pack sit in a disk of `--pack-area` subtiles² each. Every cast deals `aimed` damage to the monster you aim at and `other` to each other member, based on spell geometry:

| Geometry | aimed / other per cast |
|-|-|
| Fire Bolt, Ice Bolt, Ice Blast | full hit / 0 |
| Fire Ball, Glacial Spike (radius from the data) | full hit / hit × share of the pack disk inside the radius |
| Lightning, Inferno (line) | full / hit × share of the pack inside the strip the missile must pass through to touch a footprint |
| Nova, Frost Nova | everyone, full hit (the pack is assumed to be around you) |
| Charged Bolt | bolts × `--cb-hit` (0.91) spread evenly over the pack |
| Chain Lightning | 1 + jumps / size on the aimed monster, jumps / size on each other; no jumps without a second target |
| Frozen Orb | expected bolt hits, traced on the subtile grid: the orb flies from `--cast-distance` (6 subtiles) through the aimed monster's subtile, and each bolt's direction is uniform over the game's 64. A bolt hits if a subtile it *enters* is in the footprint; its spawn subtile is never tested |
| Blizzard | shards × chance a shard touches the monster, over `--dwell` of the 4 s |
| Fire Wall | tooltip damage per second × `--dwell` (2 s), capped at the duration, on every monster in the wall |
| Blaze | the same with `--trail` (1 s) |
| Meteor | impact: full hit / hit × share inside the radius; then the burn × `--dwell`, capped at the fire's life, on monsters touching any patch |
| Hydra | 3 heads × life / `--hydra-interval` (35 frames) shots × `--uptime` (0.75), single target |
| Thunder Storm | duration / `perdelay` strikes × `--uptime`, spread evenly over the pack |

Geometry is worked out for both footprints. 3×3 monsters take more from footprint-dependent spells, and the solver scales what they need accordingly.

Casts per pack: after T casts, each member has taken `other` × T. A member still short of its HP needs (HP − other × T) / (aimed − other) casts aimed at it, and at least one. T is the total of those, and every pack costs at least one cast. T is solved exactly; the demand is piecewise linear in T. Inferno is channeled, so its "cast" is one second of channeling, its mana is a per-second rate, and the smallest amount it can spend is one flame, plus the opening charge per pack. HP is effective HP: HP / (1 − resistance) plus the expected overkill on the last hit, E[X²] / 2E[X]. Immune monsters are skipped, and their experience is lost; the `killable` column shows the share of experience kept.

## Monsters and experience (monsters.cpp)

- Monster levels come from the population sim, with champion (+2) and unique, superunique and minion (+3) bonuses included. In NM and Hell the base is the area level.
- HP: (minHP + maxHP) / 2 for the difficulty × monlvl.txt `HP` / 100 (`L-HP` with `--online`) at the level *before* the quality bonus, then the monumod.txt bonus: champions +200/150/100%, uniques and superuniques +300/200/100%, minions +100/75/50% in Normal/NM/Hell.
- Experience: monstats.txt `Exp` × monlvl.txt `XP` / 100 at the level before the bonus, times 3 for champions and 5 for uniques, superuniques and minions. Act bosses get ×1.
- Level penalty, on the monster's actual level: within ±5 levels you get 100%. For monsters 6–10+ levels below you: 81/62/43/24/5%. Below level 25, for monsters 6–10+ levels above you: 88/68/36/15/2%. From level 25 on, any higher monster gives clvl / mlvl. After that, experience.txt `ExpRatio` / 1024 applies.

## Assumptions to verify

These are about how fights play out rather than game code, so they're set by hand and exposed as options:

- How long monsters stand in ground effects (`--dwell`, `--trail`). This drives Fire Wall, Meteor's fire and Blizzard.
- Where Frozen Orb flies (`--cast-distance`). The orb is assumed to pass straight through the monster you aim at; a moving target or a near miss loses the bolts fired from inside its footprint, which are most of them.
- Charged Bolt's hit rate (`--cb-hit`, 0.91 point-blank).
- Hydra's shot interval (`--hydra-interval`). In code it is the attack animation (animdata, not read) + `aidel` (15) + 6.7 frames of average idle; 35 assumes a 13-frame attack.
- Pack spread (`--pack-area`, 9 subtiles² = one 3×3 spawn cell per monster).
- Random champion types (Berserker, Possessed) aren't in the population sim, so all champions are treated alike.

## Limits

- One main skill per build, or two with `--hybrid` / `--progression`; the other points only serve them. A hybrid's allocation is the union of each skill's best allocation for its share of the points, not a joint optimum. Packs a build can't damage are skipped. Progression clear time uses the same model as everything else, so it's as good as the geometry and dwell assumptions.
- Experience per second leaves out making games and town visits, which cost the same for any build. It also ignores survival, so within the gates it will send a character to the hardest difficulty it can enter. Small areas packed with uniques benefit most from that.
- Running ignores stamina. A sorceress drains 3.9 stamina a second running and drops to walking (9.4 subtiles a second) when it's gone.
- Experience per mana (`--epm`) ignores time entirely.
- Packs are scored independently: an AoE cast never hits two packs at once, and nothing hits a passing monster from a different pack.
- A Fire Wall segment or Meteor fire hits only one unit per frame, and a Blizzard shard covering two monsters alternates between them. Pack members are assumed far enough apart (`--pack-area`) not to share a segment or shard.
- Random champion and unique modifiers (enchantments, magic resistant) aren't modeled.
- Thunder Storm is off by default. One cast lasts minutes for 19 mana, so it wins experience per mana outright while killing far too slowly to level with.
- Only the ROTW data is supported, since the population sim is ROTW.
- Each level is optimized on its own, as if respecced, unless `--prev` gives the build it has to grow from.
