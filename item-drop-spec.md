# Diablo II (1.14d): monster item drops

This document describes, step by step, how Diablo II 1.14d decides which items a monster drops when it dies and what those items are. It starts at the killing blow and ends when the last item is on the ground. Given the inputs in section 1, following these steps reproduces the same items with the same qualities, attributes and positions, and consumes random numbers in the same order.

Table references are written `File.txt: Column`. Monsters are identified by their MonStats row id and items by their item codes.

---

## Contents

0. [Notation](#0-notation)
1. [Inputs](#1-inputs)
2. [Random numbers](#2-random-numbers)
3. [Overview](#3-overview)
4. [Step 1: does the monster drop at all?](#4-step-1-does-the-monster-drop-at-all)
5. [Step 2: choosing the treasure class](#5-step-2-choosing-the-treasure-class)
6. [Step 3: the levels involved](#6-step-3-the-levels-involved)
7. [Step 4: treasure class upgrade](#7-step-4-treasure-class-upgrade)
8. [Step 5: resolving the treasure class](#8-step-5-resolving-the-treasure-class)
9. [Step 6: item quality and Magic Find](#9-step-6-item-quality-and-magic-find)
10. [Step 7: creating the item and its base attributes](#10-step-7-creating-the-item-and-its-base-attributes)
11. [Step 8: applying the quality](#11-step-8-applying-the-quality)
12. [Step 9: ethereal, sockets, automatic affix](#12-step-9-ethereal-sockets-automatic-affix)
13. [Step 10: gold adjustments and the item cap](#13-step-10-gold-adjustments-and-the-item-cap)
14. [Step 11: where items land](#14-step-11-where-items-land)
15. [Step 12: scripted drops after the treasure class](#15-step-12-scripted-drops-after-the-treasure-class)
16. [End state](#16-end-state)
- [Appendix A: building the treasure-class table from data](#appendix-a-building-the-treasure-class-table-from-data)
- [Appendix B: behaviours that differ from common assumptions](#appendix-b-behaviours-that-differ-from-common-assumptions)
- [Appendix C: order of random-number consumption](#appendix-c-order-of-random-number-consumption)
- [Appendix D: points not fully confirmed](#appendix-d-points-not-fully-confirmed)

---

## 0. Notation

**Arithmetic.** Unless a formula is marked *real-valued*, all arithmetic is 32-bit signed integer arithmetic:
- `a / b` truncates toward zero (so −7 / 2 = −3).
- `a mod b` is applied to non-negative values only.
- `min`, `max` and `clamp(x, lo, hi)` have their usual meanings.

**Random draws.** `rand(S, n)` is a uniform draw in [0, n−1] from random stream `S` (section 2). `raw(S)` is the raw 32-bit output of one step of `S`.

**Qualities**, in increasing order: Low (inferior), Normal, Superior, Magic, Set, Rare, Unique. Crafted and Tempered also exist but cannot come from drops.

**Levels:**

| Symbol | Meaning |
|---|---|
| mlvl | the monster's level |
| ilvl | item level |
| qlvl | the item's base quality level, `Items.txt: level` |
| alvl | affix level (section 11.6) |

**Item types** are written as `ItemTypes.txt: Code` values, for example `weap`, `armo`, `tors`, `gold`. "Is of type X" includes types that inherit from X through `ItemTypes.txt: Equiv1/Equiv2`.

**Expansion item:** an item whose `Items.txt: version` is ≥ 100. **Expansion-format item:** an item created in an expansion game. **Classic-format item:** an item created in a classic game.

**Positions** are measured in subtiles; a map tile is 5 × 5 subtiles. **Time** is measured in game frames; there are 25 frames per second.

---

## 1. Inputs

The result depends only on the values below, taken at the moment the monster **begins its death transition**. Section 4.1 lists the effects that can run between the killing blow and that moment; they belong to the skill system and are outside this process.

### 1.1 The game

| Input | Notes |
|---|---|
| Expansion or classic | |
| Difficulty `d` | 0 = Normal, 1 = Nightmare, 2 = Hell |
| Realm or non-realm | Single player, open Battle.net and TCP/IP games are non-realm. Ladder or non-ladder. |
| `/players` setting `P_set` | 1–8. Only honoured in non-realm games. |
| Living players `P_alive` | Player corpses do not count. |
| Uniques already generated this game | The game keeps a record of which unique items it has generated. It starts empty, and picking up or destroying an item does not clear it. |
| Game random stream `G` | Its state when the death transition begins, after any on-kill, on-death and level-up effects of the killing blow (section 4.1) |
| Current game time | Only used for ground-despawn timers |
| Quest history of the game creator | The first player to join. Only used for scripted drops (section 15). |
| Quest random stream `Q` | Its current state. Only used for scripted drops (section 15). |
| Scripted-drop progress | Which one-time scripted drops have already happened or been set up in this game: Council flails and cube, Gidbinn, the Golden Bird carrier, which Uber Tristram bosses have died (section 15) |
| Every player's quest records, inventory, area and party | Scripted drop counts depend on all players, not only the killer (section 15) |
| Monsters in loaded Chaos Sanctuary rooms, and the seal state | Only when the third seal boss dies with all seals open (section 15.3) |
| Monsters near certain dying bosses | Their scheduled deaths draw from the boss's stream (section 15.1) |

### 1.2 The dying monster

| Input | Notes |
|---|---|
| MonStats row id | |
| Classification | Regular, champion, unique, superunique (with its `SuperUniques.txt` row), or minion of a unique or superunique |
| Monster level mlvl | Section 6.2 derives it if you don't have it |
| Player count when it spawned, `P_spawn` | Section 8.4 |
| The monster's random stream `M` | Its state when the death transition begins (section 2.4) |
| "Never drops treasure" mark | Section 4.2 |
| Position and the collision map around it | |
| Its monster modifiers (`MonUMod.txt` rows applied to it) | Some modifiers act at death, before the drop (section 2.4) |

### 1.3 The killer

| Input | Notes |
|---|---|
| Who landed the killing blow | A player; a monster with an owner (mercenary, summon, minion); a converted monster; or nobody. Missiles count as their owner. Poison and open-wounds deaths count as whoever applied them, or nobody if that unit is gone. |
| Magic Find | Of the killer and of its owner (section 9.2). This is `ItemStatCost.txt` stat `item_magicbonus`. |
| Gold Find | Same rule as Magic Find. This is stat `item_goldbonus`. |
| Party | Living party members of the credited player who are in the same area (`Levels.txt` row) as that player |
| Quest state | The credited player's quest state for the monster's `MonStats.txt: TCQuestId` |

### 1.4 Data

The following tables are needed:
- `MonStats.txt`, `MonUMod.txt`, `SuperUniques.txt`, `Levels.txt`
- `TreasureClassEx.txt`
- `Weapons.txt`, `Armor.txt`, `Misc.txt` (together "Items")
- `ItemTypes.txt`, `ItemRatio.txt`
- `UniqueItems.txt`, `SetItems.txt`
- `MagicPrefix.txt`, `MagicSuffix.txt`, `AutoMagic.txt`, `RarePrefix.txt`, `RareSuffix.txt`
- `QualityItems.txt`, `LowQualityItems.txt`
- `Properties.txt`, `ItemStatCost.txt`, `Skills.txt`, `Books.txt`
- `MonStats2.txt` (corpse selection for Find Item), `States.txt` (the conversion test), `Missiles.txt` (whether death-effect missiles can be created, which decides whether they step `G`)

Exact positions on uneven terrain also need the line-of-sight direction field file `data\global\expfield.d2` (section 14).

**Row order matters** in several tables: ItemTypes (it numbers the automatic treasure classes), TreasureClassEx (upgrades walk forward through rows), and every table that is searched by weighted pick.

---

## 2. Random numbers

### 2.1 Generator

A random stream is a pair of 32-bit unsigned words `(x, c)`. One step is:

```
t = x · 1791398085 + c          (64-bit unsigned)
x = t mod 2³²
c = t / 2³²
output x
```

A stream seeded with value `s` starts at `(s, 666)`.

### 2.2 Uniform draw

```
rand(S, n):  if n ≤ 0 (as a signed value): return 0 without stepping S
             otherwise: step S once and return (new x) mod n
```

For n = 1 the stream still steps and the result is 0. A draw "in [a, b]" means `a + rand(S, b − a + 1)`.

### 2.3 Streams used in a drop

| Stream | Belongs to | Seeded from | Used for |
|---|---|---|---|
| `M` | the dying monster | one step of `G` when the monster was created | every treasure-class pick, every quality roll, and the forced-ethereal and forced-socket rolls |
| `G` | the game | game creation | two steps per created item, which seed `B` and `A`. Also one step for every other unit the game creates, including missiles created during the death itself (section 2.4) |
| `B` | each new item ("base stream") | first `G` step: `B = (g₁, 666)` | base attributes: gold amount, stack size, durability, defense, inventory graphic, low-quality durability |
| `A` | each new item ("attribute stream") | second `G` step: `A = (g₂, 666)`. `g₂` is also kept as the item's **modifier seed** `m₀` | quality application, every unique/set/rare/magic/superior/low choice, affix values, staff mods, ethereal chance, socket chance |
| `Q` | quest control | one `G` step at game start | only the Andariel gems and the Baal gold (section 15) |

Item creation never touches `M`, and treasure-class resolution never touches `B` or `A`.

### 2.4 The monster's stream at death

`M` is seeded at spawn, but the monster's AI and skills draw from it throughout its life. To reproduce a real kill exactly you need `M`'s state when its death transition begins (section 4.1).

Once the death transition has begun, two kinds of draws happen before the drop:

- **Spectral Hit.** A monster that has the *Spectral Hit* modifier (`MonUMod.txt` row 27) and is classed as unique or champion takes one step of `M`.
- **Poison-cloud death** (`MonUMod.txt` row 23; in vanilla this is Lilith, MonStats 707). The monster releases 8 poison-cloud missiles: 2 in each of 4 directions. Creating each missile takes one step of `G`, because every new unit is seeded from `G`. If a missile cannot be created, it takes no step. These steps come before the first item's two `G` steps.

Earlier, between the killing blow and the start of the death transition, other effects can draw too (section 4.1). For example, a killer's "chance to cast … when you kill an enemy" effect draws from the killer's stream, and every missile it creates steps `G`. These belong to the skill system. This process therefore starts from `M` and `G` as they stand when the death transition begins.

No other draws inside the death transition before the drop are known (Appendix D).

---

## 3. Overview

1. **Death.** The killing blow lands. The hit's on-kill and on-death effects run, experience is awarded (which can trigger level-up effects), and the monster starts dying (section 4.1).
2. **Eligibility** (section 4). Some monsters never drop, and a monster standing on a wall or door cell drops nothing.
3. **Treasure class choice** (section 5) from the monster's classification, the difficulty, and its quest-drop rule.
4. **Levels** (section 6). The monster level becomes the item level.
5. **Upgrade** (section 7) to a higher treasure class in the same group, by monster level.
6. **Resolution** (section 8). Picks, NoDrop scaled by player count, weighted entry choice and nested classes produce up to **6** items.
7. For each item:
   - quality roll with Magic Find (section 9);
   - placement (section 14);
   - creation and base attributes (section 10);
   - quality application with fallbacks (section 11);
   - ethereal, sockets and automatic affix (section 12);
   - gold adjustments (section 13).
8. **Death effects** of the monster happen next. These include explosions, boss death missiles, deaths of nearby monsters scheduled with random delays, and, for the three Uber Tristram bosses, the Hellfire Torch drop (section 15).
9. **Quest scripts** react to the kill. They may drop fixed quest items, and the third Chaos Sanctuary seal boss kills the rest of the Sanctuary's monsters, each of which drops (section 15).

---

## 4. Step 1: does the monster drop at all?

### 4.1 Timing

The treasure-class drop happens in the same game frame as the killing blow. For a death from a hit (melee, missile, spell damage), the order is:
1. **Kill effects.** The victim's death event and the killer's kill event run. Examples are item effects such as "chance to cast … when you kill an enemy". These can draw from the caster's stream and create missiles, which steps `G`.
2. **Experience** is awarded. A resulting level-up can trigger its own effects.
3. **Death transition begins.** The monster switches to its death animation. Monster-modifier effects that run on entering death happen here: the Spectral Hit draw and Lilith's poison clouds (section 2.4).
4. **The treasure-class drop** happens (sections 5–14).
5. **Death effects** run: monster-modifier death effects, explosions, boss death effects, and the Uber Tristram loot (section 15.1).
6. **Quest scripts** react (section 15).

For a death from poison or open wounds, steps 2–6 happen first, and the death and kill events of step 1 run afterwards.

This process starts at step 3. The states of `M` and `G` are taken as they stand there.

A monster that is already dying or dead cannot die again. A monster with `MonStats.txt: killable = 0` never dies, so it never drops.

### 4.2 Monsters that never drop treasure

These monsters carry a permanent "never drops treasure" mark:

- every player summon: skeletons and mages, golems, druid summons, Valkyrie, shadows, hydras, and bone walls and bone prisons created by skills;
- mercenaries;
- corpses raised by Revive, by "reanimate as" item effects, and by monster resurrection. For example, a Fallen raised by a Shaman never drops again;
- minions spawned during play by monster skills: monster summon skills, Baal's tentacles, Baal's clone, evil-hole spawns;
- traps;
- the illusory Tristram inhabitants, the Dark Wanderer, and Trapped Souls;
- every monster with `MonStats.txt: Align = 1` (allied monsters);
- Bone Prison (MonStats 340–343) and the Compelling Orb (MonStats 366).

Nests and sarcophagi are **not** marked from the start. They mark themselves once they have finished spawning; killed before that, they drop normally (if their treasure class is not empty).

The mark is removed only when a monster resurrects *itself*. Such a monster can drop again each time it dies.

Bone Wall (MonStats 344) must always carry the mark; the game treats a Bone Wall reaching this step without it as an error.

### 4.3 The death cell

The drop is cancelled if the subtile under the monster's position is a **wall/unwalkable** cell or a **door** cell. It is also cancelled if the position has no collision data. Corpses themselves do not block. In practice, a flying monster killed over a cliff or void drops nothing.

### 4.4 Find Item (Barbarian)

Find Item replays a corpse's treasure-class drop. The differences from a kill drop are:

- **Target:** a selectable corpse (`MonStats2.txt: corpseSel`) that has not been searched yet. Searching marks the corpse, even if the attempt fails.
- **Success roll:** uses the Barbarian's own random stream: `rand(barbarian, 100) < ` the skill's success chance. A second `rand(barbarian, 100)` is drawn and its result is ignored.
- **Gates skipped:** the "never drops treasure" mark and the death-cell test (sections 4.2 and 4.3) do not apply.
- **The Barbarian is the killer** for Magic Find, Gold Find and the quest-drop rule.
- **NoDrop is ignored entirely** (section 8.5).
- **Random stream:** the corpse's own stream `M` is used for the picks, as in a kill.

Everything else is identical to a kill drop.

---

## 5. Step 2: choosing the treasure class

No random numbers are used in this step.

### 5.1 By classification

Let `d` be the difficulty. MonStats has four treasure-class columns per difficulty: `TreasureClass1..4` (Normal), `TreasureClass1(N)..4(N)` (Nightmare) and `TreasureClass1(H)..4(H)` (Hell). Below, `TCk[d]` means column k for difficulty d.

| The monster is | Treasure class |
|---|---|
| a superunique | `SuperUniques.txt: TC / TC(N) / TC(H)` for its row (if that row is missing, `TC3[d]`) |
| otherwise, a champion | `TC2[d]` |
| otherwise, a unique | `TC3[d]` |
| otherwise (regular monsters **and minions of uniques and superuniques**) | `TC1[d]` |

Champions are checked before uniques. Act bosses are ordinary monsters for this purpose, so they use `TC1[d]`, or `TC4[d]` through the quest rule below.

### 5.2 Quest drop rule

The quest rule replaces the choice above with `TC4[d]` when all of these hold:

1. `MonStats.txt: TCQuestId` ≠ 0, `TC4[d]` is not empty, and there is a killer.
2. The **credited player** exists. It is determined as follows:
   - If the killer is a player, it is the killer.
   - Otherwise start from the killer's owner, if it has one (a mercenary's or summon's player, a minion's boss).
   - If the killer is under Conversion (it has a state marked `States.txt: exp` and carries a conversion record), the converting player **replaces** that owner.
   - The result is the credited player if it is a player; otherwise there is none.
3. In that player's quest record for this difficulty, quest `TCQuestId` is:
   - not completed in a previous game;
   - not awaiting its reward;
   - not at step `MonStats.txt: TCQuestCP`.

The quest rule is checked before quest scripts update the player's quest state (section 15). So the first time a character kills Andariel, the quest is still open and `TC4` ("Andarielq") applies.

The credited player is used only for this test. Magic Find, Gold Find and party size always use the actual killer (sections 8 and 9).

---

## 6. Step 3: the levels involved

### 6.1 Item level

```
ilvl = max(mlvl, 1)
```

There is no upper limit. A level-110 Uber monster gives ilvl 110. The same value is used as the "quality level" in section 9 and as the item's level.

### 6.2 How mlvl is set at spawn

Base monster level:

| Game | Difficulty | Base mlvl |
|---|---|---|
| Classic | Normal | `MonStats.txt: Level` |
| Classic | Nightmare / Hell (non-allied monsters) | `Level + 25·d` |
| Expansion | Normal | `Level` |
| Expansion | Nightmare / Hell; monster is neither `boss` nor `NoRatio` | `Levels.txt: MonLvl2Ex` / `MonLvl3Ex` of the area **where it spawned** |
| Expansion | Nightmare / Hell; `boss` or `NoRatio` monster | `Level(N)` / `Level(H)` |

Mercenaries always use the Normal columns.

Bonuses from monster modifiers (`MonUMod.txt`):

| Monster | Net change |
|---|---|
| Unique, superunique | +3 |
| Minion of a unique or superunique | +3 |
| Champion (plain, ghostly, fanatic, possessed) | +2 (a +3 level bonus, then −1) |
| Berserk champion | **+3**: the berserk modifier skips the −1 |
| Champion pack members | +2 |
| Ordinary monsters and act bosses | +0 |

One later change can apply before death: a monster converted by Conversion or Mind Blast has its level lowered to the caster's level, if it was higher, for the duration of the conversion. If it dies while converted, it drops at the lowered level.

---

## 7. Step 4: treasure class upgrade

### 7.1 When it applies

The upgrade applies only when **all** of these hold:
- the game is expansion;
- the difficulty is Nightmare or Hell;
- `MonStats.txt: boss = 0` and `NoRatio = 0`.

Otherwise the treasure class from section 5 is used as is.

### 7.2 Rule

Let `TC` be the chosen treasure class and `L = mlvl`.

```
if TC.group = 0: no upgrade
while the next row of TreasureClassEx has the same group and that row's level ≤ L:
    TC = that next row
```

Notes:
- The upgrade only moves forward, through consecutive rows of the same `group`. A row whose `level` equals mlvl qualifies.
- The original row's own level is never compared, so a treasure class is never downgraded.
- Only the monster's own treasure class is upgraded. Treasure classes reached through nesting (section 8) are never upgraded.
- The automatically generated item-type classes (`weap3`, `armo60`, …) have no group, so they never upgrade.
- An empty treasure class reference means nothing drops.

---

## 8. Step 5: resolving the treasure class

### 8.1 What a treasure class holds

A treasure class (TC) is one row of `TreasureClassEx.txt`, or one of the automatically generated item-type classes (Appendix A).

| Field | Column |
|---|---|
| **Picks** | `Picks`. 0 means 1. A negative value selects sequential mode (section 8.5). |
| **NoDrop weight** `N` | `NoDrop` |
| Quality modifiers | `Unique`, `Set`, `Rare`, `Magic` (section 9) |
| Up to 10 entries | `Item1..Item10` with weights `Prob1..Prob10`, read in order. **The first empty `Item` cell ends the list**: later cells are never read, even if they are filled. A filled cell whose Prob is < 1 is skipped without ending the list. |

Each entry is one of:
- an **item code** (≤ 4 characters, matching `Items.txt: code`);
- another **TC name**, which nests;
- a **unique item name** (`UniqueItems.txt: index`), which drops that exact unique;
- a **set item name** (`SetItems.txt: index`), which drops that exact set item.

An entry may carry options after commas, for example `"gld,mul=1280"`:

| Option | Effect |
|---|---|
| `mul=` (also `ma=`, `mg=`) | gold multiplier, in 256ths |
| `cu=`, `cs=`, `cr=`, `cm=` | unique, set, rare and magic quality modifiers for this entry |
| `ce=`, `cg=` | chance in 1024 to force ethereal, and to force the socket roll |

The six quality values and the gold multiplier are stored as **unsigned 16-bit** numbers: the low 16 bits of what was written, read back as 0–65535. So `ce=-1` becomes 65535, which always passes, and `mul=65536` becomes 0, meaning no multiplier.

Some entries are **expansion-only**. An entry is expansion-only if it is:
- an item with `Items.txt: version ≥ 100`;
- a nested TC that has no classic weight;
- any unique or set item entry.

### 8.2 The weight line

For the current game type, lay a TC's entries end to end on a line, in column order, each occupying a length equal to its weight. In a **classic** game, expansion-only entries have length 0 and are never selected. The total length is `T`.

Entry `i` occupies `[sᵢ, sᵢ + wᵢ)`. A position `r` selects the entry whose interval contains it.

### 8.3 Procedure

The monster's TC is resolved **depth-first**. Each nested TC is fully resolved, with all its picks, before the parent continues with its next pick. Each active TC carries:

- its **remaining picks**, which start at `max(|Picks|, 1)`;
- six **modifiers**: magic, rare, set, unique, force-ethereal chance, force-socket chance.

The modifiers start from the monster's TC columns. The last two start at 0, because no TreasureClassEx column sets them.

```
resolve(TC, modifiers):
  while TC.remainingPicks > 0 and T(TC) > 0:
      choose a position r                                   (§8.5; may result in "nothing")
      TC.remainingPicks −= 1
      if nothing was chosen: continue
      E = the entry at position r
      if E is a nested TC:
          childModifiers[k] = max(modifiers[k], child TC's own column k)   for each of the six
          resolve(child TC, childModifiers)                 (no upgrade, §7)
      else:
          handle item entry E                               (§8.7; may stop everything)
```

- **Limits:** at most **6 items** per kill (section 8.8). Nesting is at most 64 levels deep. A nested TC chosen on its parent's last pick reuses the parent's level, so only nesting that still has picks pending counts toward 64.
- **Empty TCs:** a TC whose total weight `T` is 0 resolves to nothing, and any picks it had left are lost.

### 8.4 NoDrop scaling by player count

When the TC has `Picks > 0` and `N ≠ 0`, the NoDrop weight is adjusted before **each** pick. A negative `N` (non-standard data) also goes through the adjustment. This uses no random numbers.

**Credited player.** The killer if it is a player; otherwise the killer's owner if that owner is a player; otherwise none.

**Party size `p`:**
- no credited player: 1;
- otherwise: the number of living members of the credited player's party who are in the **same area** as that player, the player included, clamped to [1, 8];
- a player who is not in a party counts as 1.

**Players in game `P`:**

```
P = P_alive                      (realm games)
P = max(P_alive, P_set)          (non-realm games)
```

**Effective player count `n`:**

```
n = p + (P − p) / 2
n = min(n, max(P_spawn, 1))
```

`P_spawn` is the player count recorded on the monster when it spawned: `max(P, 1)` at that moment for hostile monsters, and 1 for allied ones. Because `P_spawn` is only an upper cap, raising `/players` after a monster has spawned cannot raise its `n` above `P_spawn`. Lowering `/players` takes effect immediately. For example, a monster that spawned under `/players 8` and is killed solo after `/players 1` uses `n = 1`.

**Adjusted NoDrop `N′`.** If `n ≤ 1`, `N′ = N`. Otherwise compute the following in IEEE double precision (*real-valued*):

```
ρ  = N / (N + T)
π  = ρ · ρ · … · ρ        (n factors, multiplied left to right)
q  = 1 − π
N′ = 0                                   if q = 0
N′ = truncate( ((1 − q) · T) / q )       otherwise
```

Algebraically `N′ = ⌊T · ρⁿ / (1 − ρⁿ)⌋`. To get bit-identical results, use the exact sequence above: compute `1 − q` rather than reusing `π`, multiply by `T`, divide by `q`, then truncate.

This is the only floating-point calculation in treasure-class resolution, quality, item creation, affixes and placement; all of those are integer arithmetic. Experience sharing at the kill, which happens before the drop, also uses floating point, but it does not affect drops.

**Rounding model:**
- `N`, `N + T` and `T` enter exactly, as integers.
- Each division, multiplication and subtraction above is an ordinary IEEE double-precision operation (round to nearest, ties to even).
- The final quotient is truncated toward zero.

**Exact maths is not a substitute.** The double-precision result differs from the mathematically exact floor in about 1 of 20,000 random sampled cases, so implement the floating-point sequence rather than exact rational arithmetic.

Single player with `/players X`: `n = 1 + (X−1)/2`, so 1–2 → 1, 3–4 → 2, 5–6 → 3, 7–8 → 4.

**Example.** `N = 100`, `T = 60`, `n = 4`:
- `ρ = 0.625`
- `π = 0.152587890625`
- `q = 0.847412109375`
- `N′ = truncate(10.8038…) = 10`

### 8.5 Choosing a position

| TC kind | Position | NoDrop | Random numbers |
|---|---|---|---|
| `Picks > 0`, normal kill | `r = rand(M, T + N′)`. If `r < N′`: nothing. Otherwise use position `r − N′`. | yes | 1 draw per pick (none if `T + N′ ≤ 0`) |
| `Picks > 0`, Find Item | `r = rand(M, T)` | ignored | 1 draw per pick |
| `Picks < 0` (sequential) | The k-th pick (k = 0, 1, 2, …) uses position `r = k`. If `k ≥ T`, this TC stops immediately. | ignored | none |

In sequential mode an entry of weight `w` is chosen `w` times in a row. For example, Picks −5 with entries A (weight 2) and B (weight 3) gives A, A, B, B, B. With A:1 and B:1 it gives A, B, then stops early.

### 8.6 How quality modifiers combine

- **Nested TC:** each of the six values becomes the larger of the current value and the nested TC's own column.
- **Entry options in classic games only:** when an item entry carries `cu=`, `cs=`, `cr=`, `cm=`, `ce=` or `cg=`, the current TC's values are raised to the entry's values, if larger, as the entry is handled. The raise **persists** for that TC's remaining picks.
- **Entry options in expansion games:** these per-entry quality options are ignored entirely.
- Values never decrease within a TC.

### 8.7 Handling an item entry

The steps are applied in this order:

1. **Classic game and expansion item:** nothing. The pick is spent.
2. Classic game only: apply the entry's quality options (section 8.6).
3. **Quality:**
   - a unique-name entry is Unique, as that exact unique;
   - a set-name entry is Set, as that exact set item;
   - otherwise roll the quality (section 9).
4. **Forced ethereal:** if the force-ethereal value `e > 0`, take one raw step of `M`. If `raw(M) mod 1024 < e`, the item is forced ethereal.
5. **Forced socket roll:** the same with the force-socket value. On success, the item's socket roll in section 12.2 always passes.

   In expansion games both values are always 0, so neither step 4 nor step 5 draws.
6. **Classic games only, throwing weapons** (item type with `ItemTypes.txt: Throwable = 1`): the first **10** such results in a kill are discarded and **the pick is given back**. After that, the item is replaced by `lsd` (Long Sword) with the quality already rolled.
7. **Create the item** (sections 10–12). If no ground space can be found (section 14), nothing is created; the pick is spent and nothing is counted.
8. **Gold multiplier and count** (section 13). When the count reaches 6, resolution stops entirely.
9. **Gold Find** (section 13).

### 8.8 Edge cases

- **Item cap.** Every created item counts toward the cap of 6, including gold piles and items from nested TCs. NoDrop results, skipped entries and failed placements do not count. When the cap is reached, all remaining picks are abandoned without drawing.
- **Cyclic TCs.** A TC that contains itself, directly or through others, can do any of three things:
  - finish normally, once a pick leaves the cycle;
  - exceed the 64-level nesting limit, which is an error;
  - loop forever. This happens when the cycle is always re-entered on the last pick: the nested TC then reuses its parent's level, so depth never grows.

  For example, an expansion TC with Picks 1, NoDrop 0 and only itself as an entry never ends. With entries `gld:1` and `self:1`, it ends as soon as gold is picked.
- **Empty automatic TC.** A nested automatic TC with no items (an empty level band) behaves like extra NoDrop weight in expansion games.

---

## 9. Step 6: item quality and Magic Find

The quality roll is skipped when the TC entry names a specific unique or set item. Otherwise it uses the monster's stream `M`.

### 9.1 Which ItemRatio row

Two properties of the item select the row:
- **Class-specific:** the item's own type has a `ItemTypes.txt: Class`, for example Amazon bows, claws or orbs.
- **Uber:** the item is a weapon or armor whose `code` equals its own `ubercode` or `ultracode` (it is an exceptional or elite base), and it is neither a quest item nor a throwing potion (`tpot`).

The rule:
- Among the `ItemRatio.txt` rows whose `Class Specific` and `Uber` columns match these two properties and whose `Version` ≤ 100, use the one with the highest `Version`. If several tie, use the **last** such row.
- **Version 100 is used even in classic games.**

### 9.2 Magic Find

```
MF = (killer's Magic Find) + (killer's owner's Magic Find, if the killer is a monster with an owner)
```

- Only players and monsters can contribute. If there is no killer, or the killer is an object, MF = 0.
- A player kill uses that player's MF.
- A mercenary or summon kill uses the pet's MF **plus** its owner's MF.
- A converted monster's kill uses only its own MF, because its converter is not its owner.
- Nothing else contributes: not party members, area, difficulty or player count.

**Effective MF.** Diminishing returns use a factor `f` of 250 for unique, 500 for set and 600 for rare:

```
E(f) = 100 + MF·f / (MF + f)        if MF > 10
E(f) = 100 + MF                     if MF ≤ 10
E_magic = 100 + MF                  (magic has no diminishing returns)
```

### 9.3 The roll

Let:
- `Δ = ilvl − qlvl`, where qlvl = `Items.txt: level` (signed);
- `mod_X` be the current TC modifier for tier X (section 8.6);
- `ty` be the item's own `ItemTypes.txt` row (no inheritance).

Checks made first, with no random numbers:
1. If `ty.Normal = 1`: **Normal**.
2. If `Items.txt: unique = 1` (unique-only base): **Unique**.
3. If `ty.Magic = 1` and the item is a quest item: **Unique**.
4. If `MF ≤ −100`: skip directly to the Superior step below.

Then for each tier X in order:

| Tier | Ratio columns | Factor | Condition |
|---|---|---|---|
| Unique | `Unique`, `UniqueDivisor`, `UniqueMin` | E(250) | |
| Set | `Set`, `SetDivisor`, `SetMin` | E(500) | |
| Rare | `Rare`, `RareDivisor`, `RareMin` | E(600) | only if `ty.Rare = 1` |
| — | — | — | if `ty.Magic = 1`, stop: **Magic** |
| Magic | `Magic`, `MagicDivisor`, `MagicMin` | E_magic | |

```
base   = Ratio − Δ / Divisor
chance = (12800 · base) / E                      (with MF = 0 this equals 128 · base)
chance = max(chance, Min)
chance = chance − (chance · mod_X) / 1024
if chance < 1: success (no draw)
else: success if rand(M, chance) < 128
```

The first success decides the quality. If none succeeds:

```
Superior: c = 128 · (HiQuality − Δ / HiQualityDivisor)
          if c ≤ 0: Superior (no draw);   else Superior if rand(M, c) < 128
Normal:   c = 128 · (Normal − Δ / NormalDivisor)
          if c < 1: Normal (no draw);     else Normal if rand(M, c) < 128, otherwise Low
```

Notes:
- **Every item that is not Normal-only gets the unique and set rolls**, even if no unique or set exists for that base. Whether one exists is only settled in section 11, and a miss leads to fallbacks there.
- **Always-magic types** (`ty.Magic = 1`: rings, amulets, charms, jewels) return Magic after the rare roll.
- With `MF ≤ −100`, always-magic types can come back Superior, Normal or Low. Section 11.1 turns those back into Magic.
- **TC modifiers:** a modifier of 1024 or more makes that tier certain.
- **Example 1.** Unique modifier 983 on a chance of 6400 gives `6400 − 6143 = 257`, so P = 128/257 ≈ 49.8%.
- **Example 2.** A row with Unique 400/1/6400, ilvl 85, qlvl 50, MF 300, no modifier:
  - `Δ = 35`, `base = 365`
  - `E = 100 + 75000/550 = 236`
  - `chance = 4,672,000 / 236 = 19796`
  - P(unique) = 128/19796 ≈ 0.647%. Without MF, P = 128/46720 ≈ 0.274%.

---

## 10. Step 7: creating the item and its base attributes

### 10.1 Creation

1. **Find a ground position** near the monster (section 14). If none is found, no item is created.
2. In a classic game, an expansion item cannot be created, and nothing results.
3. **Item level:** `ilvl = max(mlvl, 1)`.
4. **Seed the item's streams** by stepping `G` twice:
   - `B = (g₁, 666)`;
   - `A = (g₂, 666)`, and keep `m₀ = g₂` as the item's modifier seed.

   Nothing else draws from `G` between these two steps.
5. The item starts **identified**. Magic, rare, set and unique processing later makes it unidentified.
6. **Drop options** carried into the later steps:
   - *force ethereal* and *force socket roll*, from section 8.7;
   - *Cow King allowed*, set when the dying monster is a Hell Bovine (MonStats 391).
7. Roll the **base attributes** from stream `B` (section 10.2).
8. Apply the **quality** (section 11), then ethereal, sockets and automatic affix (section 12), all from stream `A`.
9. If the item has a replenish-durability or replenish-quantity attribute, schedule its first regeneration tick. This uses no random numbers.

### 10.2 Base attributes (stream B)

Exactly one case applies, chosen by the item's own `Items.txt: type`. "Is of type" follows inheritance. A `rand` whose range is ≤ 0 does not draw.

**Gold** (type `gold`):
```
amount = ilvl + rand(B, 5·ilvl)               range [ilvl, 6·ilvl − 1]
amount = max(amount, 1)
```

**Arrows and bolts** (`ItemTypes.txt: Quiver = 1`):
```
maxStack = min(maxstack + extra-stack bonus, 511)
quantity = minstack + rand(B, maxStack − minstack)      range [minstack, maxStack − 1]
quantity = max(quantity, 1)
```

**Armor** (is of type `armo`):
```
block chance = Items.txt: block;   speed penalty = −Items.txt: speed
D = Items.txt: durability
durability    = min(D/2 + rand(B, D/2), 255)            range [D/2, 2·(D/2) − 1]
maxdurability = min(D, 255)
defense       = minac + rand(B, maxac − minac + 1)      range [minac, maxac]
```

**Weapons** (is of type `weap`):
```
if stackable (throwing weapons):
    quantity = max(minstack + rand(B, maxStack − minstack), 1)
durability, maxdurability as for armor
base damage = the Items.txt damage columns (one-hand, two-hand, missile), no randomness
attack speed = −Items.txt: speed
```

**Everything else**, if stackable (keys, tomes, …):
```
upper    = spawnstack  if spawnstack ≥ minstack and spawnstack ≠ 0
           otherwise max(minstack, maxStack)
quantity = max(minstack + rand(B, upper − minstack), 1)
```

**All items:** if `ItemTypes.txt: VarInvGfx = v > 0`, the inventory graphic is `rand(B, v)`.

Consequences:
- **Plain drops are never at full durability**, because durability is at most `2·(D/2) − 1`. Ethereal items are the exception (section 12.1).
- **Stacks never roll their maximum size.**

---

## 11. Step 8: applying the quality

Everything in this section and in section 12 uses stream `A`, unless it says otherwise.

### 11.1 Adjusting the requested quality

Start from the quality from section 9, or the forced unique/set from section 8.7. If a scripted drop requested **no** quality (the Cow King's potions, section 15), first roll the **item-local quality** below. Then apply these rules in order:

1. If `ItemTypes.txt: Magic = 1` (always-magic type):
   - a quest item becomes **Unique**;
   - otherwise anything below Magic becomes **Magic**.
2. If `ItemTypes.txt: Rare = 0` and the quality is Rare: **Magic**.
3. If `Items.txt: unique = 1`: **Unique**.
4. If `ItemTypes.txt: Normal = 1`: **Normal**.

**Item-local quality** (only when no quality was requested). It uses stream `A` and does **not** use Magic Find, the Min columns, or TC modifiers:

```
if Items.txt: quest ≠ 0: Normal (no draws)
row = the ItemRatio row of section 9.1 (Version 100)
a   = 1 if the item is of type misc, otherwise max(1, ilvl − qlvl)
for tier in Unique, Rare, Set, Magic, Superior, Normal:          (note: Rare before Set)
    c = Ratio − a / Divisor          using Unique/UniqueDivisor, Rare/RareDivisor, Set/SetDivisor,
                                     Magic/MagicDivisor, HiQuality/HiQualityDivisor, Normal/NormalDivisor
    if c ≤ 0: that tier (no draw)
    if rand(A, c) = 0: that tier
if no tier was chosen: Low
```

If such an item later falls back (section 11.2), the first fallback repeats this roll once and discards the result before switching quality. Every later fallback skips it.

### 11.2 Fallback chains

Each quality has a generator that can fail. On failure, the next quality in its chain is tried:

| Requested | Chain |
|---|---|
| Low | Low → Normal |
| Normal | Normal (always succeeds) |
| Superior | Superior → Normal |
| Magic | Magic → Superior → Normal |
| Set | Set → **[durability ×2]** → Magic → Superior → Normal |
| Rare | Rare → Magic → Superior → Normal |
| Unique | Unique → **[durability ×3]** → Rare → Magic → Superior → Normal |

- **Durability multipliers.** When a set or unique fails, both current and maximum durability are multiplied by 2 or 3, capped at 255. This applies only to items that have durability. It happens once, and the multiplied durability is kept through any further fallbacks. This is the familiar "failed unique becomes a triple-durability rare".
- **Reseeding.** Just before each generator runs, note the current `x` of stream `A` (call it `a`). If that generator fails, all its affixes are discarded, and the stream and the modifier seed are reset before the next generator runs:
  ```
  A  = (a, 666)
  m₀ = a
  ```
  The next generator starts from that state. Its own starting point is then the new `x` of `A`, and that becomes `a` for any further fallback.

### 11.3 Unique

Candidates are the rows of `UniqueItems.txt`, in file order, that meet all of these:
- `code` equals the item's code;
- `enabled = 1`;
- `lvl ≤ ilvl`;
- it is not an expansion row (`version ≥ 100`) on a classic-format item;
- it is not a ladder-only row in a non-ladder realm game.

Each candidate weighs `max(rarity, 1)`.

```
if no candidates:
    succeed with no unique row if Items.txt: unique = 1 (unique-only bases such as quest items)
    otherwise fail
if the TC entry named a specific unique and that row is a candidate:  choose it (no draw)
otherwise: r = rand(A, total weight); choose the candidate whose cumulative weight interval contains r
if the chosen unique has already been generated in this game (and the base is not a quest item):
    FAIL                       ← even if other candidates were still available
record the unique as generated (unless UniqueItems.txt: nolimit = 1)
mark unidentified; apply prop1..prop12 (section 11.9)
```

### 11.4 Set

Candidates are the rows of `SetItems.txt`, in file order, that meet all of these:
- `item` equals the item's code;
- `lvl ≤ ilvl`;
- it is not an expansion row on a classic-format item;
- if it belongs to set 29 (Cow King's Leathers), the *Cow King allowed* option is set.

Each candidate weighs `rarity`, or 1 if `rarity` is 0.

```
if the TC entry named a specific set item and it is a candidate:
    choose it (no draw)
else:
    if total weight = 0: fail
    r = rand(A, total); choose the candidate containing r
mark unidentified; apply prop1..prop9, then the partial-set bonuses aprop1a, aprop1b, …, aprop5a, aprop5b (section 11.9)
```

Set items have no once-per-game rule.

### 11.5 Rare

```
if ItemTypes.txt: Rare = 0: fail
prefixName = uniform choice among eligible RarePrefix.txt rows        rand(A, count)
suffixName = uniform choice among eligible RareSuffix.txt rows        rand(A, count)
if either list is empty: fail
affixCount = jewel:      3 + rand(A, 2)                               3 or 4
             otherwise:  [3,4,4,5,5,5,6,6][raw(A) mod 8]              P(3,4,5,6) = 1/8, 2/8, 3/8, 2/8
for each of affixCount slots:
    if prefixes and suffixes are both still possible:  side = suffix if raw(A) is odd, else prefix
    else: side = whichever is still possible (no draw); if neither, stop
    pick an affix for that side (section 11.6, rare rules)
    if nothing is eligible: that side is closed, and the slot is NOT used up
    a side closes after 3 affixes
if no affixes at all: fail
mark unidentified
apply the affixes in the order prefix1, suffix1, prefix2, suffix2, prefix3, suffix3
staff mods (section 11.8)
```

A rare-name row is eligible when all of these hold:
- the item has none of its `etype` types;
- the item has at least one of its `itype` types;
- it is not an expansion row on a classic-format item;
- a classic-format item is not stackable or throwable.

### 11.6 Choosing a magic affix

This procedure is used by magic, rare and automatic affixes. Its inputs are the **pool** (MagicPrefix, MagicSuffix or AutoMagic) and whether the affix **must** be chosen.

**1. Coin.** Step `A` once. If the result is even and the affix is optional, there is no affix. The coin is drawn even when the affix is mandatory.

**2. Affix level.** Let `q = qlvl`, `i = max(ilvl, qlvl)` and `m = Items.txt: magic lvl`.

```
alvl = i + m                    if m > 0
alvl = i − q/2                  if m = 0 and i < 99 − q/2
alvl = 2·i − 99                 otherwise
alvl = clamp(alvl, 1, 99)
```

**3. Eligible rows.** A row of the pool is eligible if all of these hold:
- `spawnable = 1`. This is not required for automatic affixes.
- It is not an expansion row (`version ≥ 100`) on a classic-format item.
- `level ≤ alvl`, and (`maxlevel = 0` or `alvl ≤ maxlevel`).
- If the item is rare, the row has `rare = 1`.
- The item has none of its `etype` types and at least one of its `itype` types.
- A classic-format item is not stackable or throwable.
- If the item can never have sockets, the row's first modifier is not a socket modifier.
- `frequency > 0`.
- Class: if `classspecific` is set and the item's type has a class, the two classes match.
- `group` differs from the group of every prefix **and** suffix already on the item.
- For automatic affixes, `group` equals `Items.txt: auto prefix`.

**4. Weight.** Each eligible row weighs `frequency`, or `frequency × level` if the base has a `magic lvl`. Sum these to `W`.

**5. Choice.**
```
if there are no eligible rows: no affix, and NO choice draw (the coin has already been drawn)
r = rand(A, W + 1)                      range [0, W]: note the +1
walk the eligible rows in table order, subtracting each weight from r;
choose the first row that takes r below 0;
if no row does (only possible when r = W), choose the last eligible row
```
The `+1` means the last eligible row gets one extra point of weight.

**6. Apply.** For magic items, the chosen affix's values (section 11.9) are rolled immediately, before anything else is drawn. Rare and automatic affixes are applied later, as described in their own sections.

### 11.7 Magic

```
prefix = choose a magic prefix (optional)
suffix = choose a magic suffix: mandatory if no prefix was obtained, optional otherwise
if neither: fail
mark unidentified; staff mods (section 11.8)
```

With both pools non-empty, the outcomes are:

| Result | Probability |
|---|---|
| prefix only | 1/4 |
| prefix and suffix | 1/4 |
| suffix only | 1/2 |

### 11.8 Superior, Low, Normal, and staff mods

**Superior.** Let `R` be the number of `QualityItems.txt` rows. Throwing weapons and items with `nodurability = 1` may only use the first 4 rows.

```
repeat:
    draw rand(A, R) until it gives a row not yet tried    (every draw counts, including repeats)
    if the row suits the item: apply its mod1 and mod2 (section 11.9), staff mods, and succeed
    otherwise mark the row as tried; if every row has been tried: fail
```

A row suits an item if any of these hold:
- the row's `weapon` flag is set and the item is a weapon other than a staff, bow, crossbow, scepter or wand;
- the row's `armor` flag is set and the item is armor other than a shield, boots, gloves or belt;
- the row's flag for the item's exact type is set (`shield`, `scepter`, `wand`, `staff`, `bow` (also crossbows), `boots`, `gloves`, `belt`).

**Low quality.** This succeeds only for weapons and armor. Any other base makes the draws below (its name draw and any staff mods), then fails and falls back to Normal (section 11.2).
```
name = rand(A, number of LowQualityItems.txt rows)         Crude / Cracked / Damaged / Low Quality
if the item has durability:
    D′ = max(Items.txt: durability · 33 / 100, 1)
    durability = max(D′/2 + rand(B, D′/2), 1)          ← base stream B
    maxdurability = D′
weapons: each damage value × 75/100 (truncated), then floored:
         one- and two-hand minimum damage at least 1, maximum damage at least 2;
         thrown minimum damage at least 2, thrown maximum damage at least 1 (the thrown floors are reversed)
armor:   defense = max(defense · 75/100, 1)
staff mods
```

**Normal.** Never fails.
- A charm that ends up Normal (only possible through fallbacks) still receives a magic prefix and/or suffix, using the same procedure as section 11.7 but without staff mods.
- Scrolls and books record which `Books.txt` row they are.
- Then staff mods.

**Staff mods** apply to every quality except set and unique, and only when `ItemTypes.txt: StaffMods` names a class. Let `L = ilvl`.

```
r = raw(A) mod 100
count = 3 if r ≥ 91;  2 if r ≥ 71;  1 if r ≥ 31;  else none
        (P(0, 1, 2, 3) = 31%, 40%, 20%, 9%)
tier = 5 if L ≥ 37 and the item is expansion-format;  4 if L ≥ 25;  3 if L ≥ 19;  2 if L ≥ 12;  else 1
repeat count times:
    r = raw(A) mod 100
    t = tier+1 if r ≥ 81;  tier if r ≥ 31;  tier−1 if r ≥ 11;  else tier−2;   t = max(t, 1)
    if the item is Low quality: t = min(t, 4)
    up to 6 tries: skill = the class's (5·(t−1) + raw(A) mod 5)-th skill in Skills.txt order
                   accept if the skill fits the item (Skills.txt: itypea1) and was not already chosen
                   (if all 6 tries are rejected, the last one is used anyway)
    if the item is Low quality and expansion-format: level = 1 (no draw)
    else: r = raw(A) mod 100;  level = 3 if r ≥ 90;  2 if r ≥ 60;  else 1
    the item's bonus to that skill is SET to level (a repeat of an already chosen skill,
    possible only after exhausted retries, replaces the earlier bonus instead of adding to it)
```

### 11.9 Turning modifiers into attributes

Every affix, superior row, unique row or set row lists modifiers as `(code, param, min, max)`, where `code` is a `Properties.txt` row. Each property row lists up to seven functions (`func1..func7`), each with a stat, a set flag and a value. They run in order and stop at the first empty function.

**Source kind.** Each modifier is applied with a source kind: magic, rare or automatic affix; superior row; unique row; or set row.

**Rolled value.** A rolled value is `lo + rand(A, hi − lo + 1)`, where `lo = min(min, max)` and `hi = max(min, max)`. When `min = max` the value is `min` and **no draw is made**.

**Reused value.** The first function of a property returns a *result* (see "Results" below). Later functions of the same property that "reuse" take that result; **if it is 0 they roll their own value instead**, which draws.

**Storing.** A value `v` is first scaled to the stat's storage units: `v · 2^k`, where `k = ItemStatCost.txt: ValShift` (a 32-bit shift; only the low 5 bits of `k` count). It is then **added** to the item's existing stat, or **replaces** it if that function's set flag is on. A value of 0 stores nothing. For example, 10 with ValShift 8 stores 2560.

**Maximum poison damage** (`ItemStatCost.txt` row 58) also maintains the item's poison-source count (`poison_count`): adding increases the count by 1, and replacing sets it to 1 if it was 0.

| `Properties.txt: func` | Value stored | Random draws |
|---|---|---|
| 1 | rolled value. Only for a **superior** source, raise the base first (below) | 1 if min ≠ max |
| 2 | rolled value, always raising the base first | 1 if min ≠ max |
| 3 | reused value (rolled if 0). Raise the base first only for a **superior** source | 0 or 1 |
| 4 | reused value (rolled if 0), always raising the base first | 0 or 1 |
| 5 | reused value (rolled if 0) added to minimum damage (one-hand, two-hand, thrown, as the item has them). Each result is at least 1 | 0 or 1 |
| 6 | the same for maximum damage; each result is at least 0 | 0 or 1 |
| 7 | enhanced damage %, as a reused value (rolled if 0). If `base max damage · value / 100 ≤ 0`, add +1 maximum damage instead | 0 or 1 |
| 8 | reused value (rolled if 0) | 0 or 1 |
| 9 | +skill: reused value (rolled if 0) to skill `param` | 0 or 1 |
| 10 | +skill tab: reused value (rolled if 0) to tab `param mod 3` of class `param / 3` | 0 or 1 |
| 11 | chance to cast skill `param` (formula below) | **0** |
| 12 | +`param` levels to a randomly chosen skill: the skill id is the rolled value | 1 if min ≠ max |
| 13 | rolled value. Raise the base first only for a **superior** source. Then set durability to its maximum | 1 if min ≠ max |
| 14 | sockets: reused value, rolled if ≤ 0, or `param` if that is still ≤ 0; clamped to [1, min(6, inventory width × height, socket limit for ilvl)] | 0 or 1 |
| 15 | minimum damage = `min`. When the stat is minimum damage this works like function 5, so `min = 0` rolls a value instead | 0, or 1 if `min = 0` and min ≠ max |
| 16 | maximum damage = `max`. When the stat is maximum damage this works like function 6, so `max = 0` rolls a value instead | 0, or 1 if `max = 0` and min ≠ max |
| 17 | per-level value: `param`, or a rolled value if `param` = 0 | 0 or 1 |
| 18 | by-time value (formula below) | **0** |
| 19 | charges of skill `param` (formula below) | **exactly 1** |
| 20 | indestructible | 0 |
| 21 | rolled value to the class skills of class `Properties.txt: val` | 1 if min ≠ max |
| 22 | rolled value to skill `param` (auras, other skills) | 1 if min ≠ max |
| 23 | ethereal: if not already ethereal and it has durability, make it ethereal with ×1.5 base attributes (durability unchanged) | 0 |
| 24 | reused value (rolled if 0) to sub-stat `param` | 0 or 1 |
| 36 | random class skill: the skill is a rolled value; the amount is `Properties.txt: val` | 1 if min ≠ max |

**Results** (what a later "reuse" sees), where they differ from the stored value:
- function 15 returns its `min` field, and function 16 its `max` field, even when a 0 field was rolled;
- function 18 returns `clamp(max + 256, 0, 1023)`. For example, `(2, 10, 20)` stores 1,131,562 but returns 276;
- function 19 returns the maximum charges `C`;
- every other function returns the value it stored (before scaling).

**Raising the base value.**
- For defense or enhanced defense on armor that has a `maxac`, the base defense becomes `max(current + 1, maxac + 1)`.
- For damage on weapons, the base damage is reset to the Items.txt values.

Only functions 2 and 4 do this for every source. Functions 1, 3 and 13 do it only for **superior** sources. So `maxac + 1` comes from enhanced-defense properties (`ac%`, function 2) and from superior rows, **not** from flat defense on a unique or set item.

**Skill level for functions 11 and 19.** Let `R` = `Skills.txt: reqlevel` of the skill and `Lmax` = that skill's maximum level.

```
if max > 0:  level = max
if max = 0:  level = clamp( (ilvl − R) / 4 + 1, 1, Lmax )
if max < 0:  s = max(1, 99 − R)
             s = max(1, −(s / max))
             level = (ilvl − R) / s;  if level ≤ 0: level = 1
```

All divisions truncate toward zero. Only the `max = 0` case is clamped to `Lmax`.

**Function 11 (chance to cast).**
- chance = `min`, or 5 if `min < 1`;
- stored as `chance`, keyed by skill `param` at the level above;
- no random draw.

**Function 19 (charges).**
```
C = min
if C = 0:  C = 5
if C < 0:  C = −C + (−C · level) / 8
C = clamp(C, 1, 255)
current = rand(A, C − C/8) + 1 + C/8              (one draw)
stored value = (current mod 256) + 256 · C, keyed by skill param at the level above
```

For example, `min = −10`, `max = 4` gives level 4 and `C = 10 + 40/8 = 15`.

**Function 18 (by time of day).** No draw:
```
stored value = clamp(param, 0, 3) + 4 · ( clamp(min + 256, 0, 1023) + 1024 · clamp(max + 256, 0, 1023) )
```
For example, `(param 2, min 10, max 20)` stores 1,131,562.

**Partial-set bonuses (`aprop1a..aprop5b`).** All ten are rolled when the set item is created, in the order 1a, 1b, 2a, 2b, …, 5a, 5b.
- If `SetItems.txt: add func` is 0, they become ordinary attributes.
- Otherwise each pair `k` (`aprop{k}a`, `aprop{k}b`, k = 1…5) goes into its own **dormant group k**. These are tied, in order, to `States.txt` rows 165–169. The game switches a group on only while the wearer has enough pieces of the set equipped, as `add func` dictates.

### 11.10 Final attribute order

For an expansion item, the visible result is built in this order:
1. base attributes;
2. quality (with fallbacks);
3. ethereal;
4. sockets;
5. automatic affix;
6. quest difficulty (section 12.4).

Ethereal therefore multiplies a defense that may already have been raised to `maxac + 1`.

---

## 12. Step 9: ethereal, sockets, automatic affix

These three steps run after the quality is final, in this order. The item's final quality after all fallbacks determines which of them apply.

### 12.1 Ethereal (expansion-format items only)

An item is eligible when all of these hold:
- it is a weapon or armor (`weap` or `armo`);
- it has durability, meaning `Items.txt: nodurability = 0`, durability > 0, and it is not indestructible;
- its quality is **not Low and not Set**;
- it is not a quest item;
- the drop is not marked "never ethereal".

```
r = rand(A, 100)                       (drawn for every eligible item, even when ethereal is forced)
ethereal if r < 5, or the drop was forced ethereal (section 8.7)
```

An ethereal item is modified as follows:
- weapons: every base damage value (one-hand, two-hand, thrown) becomes `base · 3 / 2`;
- armor: base defense becomes `base · 3 / 2`;
- `maxdurability = base maxdurability / 2 + 1`, and `durability = maxdurability`. Ethereal items always drop at full durability.

Uniques can be ethereal. This random or forced step never applies to set, low-quality, indestructible or quest items.

An item can also become ethereal earlier, through an `ethereal` property (function 23). That changes base attributes but not durability. If the item is still eligible here, the draw is still made: a failure leaves it as it is, and a success applies the ×1.5 change again and sets durability as above. So "ethereal items always drop at full durability" holds only for items made ethereal by this step.

### 12.2 Sockets

Only **Normal** and **Superior** items can gain sockets this way. The item must also have an inventory size and must not be stackable.

```
limit = ItemTypes.txt: MaxSock1    if ilvl ≤ 25
        ItemTypes.txt: MaxSock25   if 26 ≤ ilvl ≤ 40
        ItemTypes.txt: MaxSock40   if ilvl ≥ 41
limit = min(limit, Items.txt: gemsockets)
if limit = 0: no sockets
limit = min(limit, 3 / 4 / 6 for Normal / Nightmare / Hell)
classic-format body armor (type tors): no sockets
r = rand(A, 100)
if the drop was forced to pass the socket roll (section 8.7): r = 0
if r ≥ 33: no sockets                                  (33% chance)
sockets = (m₀ mod limit) + 1                           (NOT a new draw: uses the item's modifier seed)
sockets = clamp(sockets, 1, min(6, inventory width × height, limit))
```

`m₀` is the second game-stream value from section 10.1, unless a quality fallback reset it (section 11.2). Magic, rare, set and unique items only get sockets from a socket property (`Properties.txt` function 14).

### 12.3 Automatic affix (expansion-format items only)

This step applies when the item's final quality is neither Set nor Unique and `Items.txt: auto prefix` ≠ 0. Typical examples are class-specific items and circlets.

Choose a mandatory affix from `AutoMagic.txt` (section 11.6), restricted to rows whose `group` equals `auto prefix`. The coin is still drawn. Apply the chosen affix's modifiers (section 11.9).

### 12.4 Quest items that remember their difficulty

Last of all, for every format: if the base has both `Items.txt: quest ≠ 0` and `questdiffcheck ≠ 0`, the item stores the current difficulty (0, 1 or 2) as its `questitemdifficulty` attribute and is **marked identified**. This uses no random numbers.

---

## 13. Step 10: gold adjustments and the item cap

After each item is created:

1. **Gold multiplier.** If the item is gold and its TC entry carries `mul=k` (also written `ma=` or `mg=`) with a stored `k` other than 0 (section 8.1):
   ```
   gold = (gold · k) / 256        rounded down
   ```
   For example, `gld,mul=1280` is ×5. A stored `k` of 0 means no multiplier, not ×0.
2. **Count.** Increase the drop count. If it is now **6**, stop the whole treasure-class resolution immediately. Gold Find (step 3) is *not* applied to this sixth item.
3. **Gold Find.** If the item is gold:
   ```
   GF   = (killer's Gold Find) + (killer's owner's Gold Find, if any)
   gold = gold · (100 + GF) / 100
   ```
   Any negative result becomes 0.

The full formula for a gold pile dropped by a monster is:

```
gold = ( ( (ilvl + rand(B, 5·ilvl)) · k / 256 ) · (100 + GF) ) / 100
```

- The `· k / 256` term is omitted when the entry has no multiplier.
- The `(100 + GF) / 100` term is omitted when this pile is the sixth item.

---

## 14. Step 11: where items land

Each item's position is chosen just before the item is created. Items are placed one at a time. Each placed item occupies its cell, so later items spread out around earlier ones. Placement uses no random numbers.

### 14.1 Free cells

A cell is **free** when it has no wall or unwalkable flag, no item, no object, no door, no pet, and no other reserved-unit flag.

A cell is **reachable** from the monster when the walking line from the cell back to the monster's cell crosses no wall or door cell.

The line is traced with the game's **direction field**, `data\global\expfield.d2`. The file layout is:
- 2 bytes, skipped;
- the height `H`, a little-endian 32-bit integer at byte 2;
- the width `W`, a little-endian 32-bit integer at byte 6;
- the grid of `W·H` direction codes from byte 10, row by row.

Rows are addressed with a stride of 256. Let `hw = W / 2` and `hh = H / 2`.

For a cell `(x, y)` and the monster's cell `(ox, oy)`, the code is:
```
code(x, y) = grid[ (y − oy + hh) · 256 + (x − ox) + hw ]
```

Codes 0–7 are one-subtile steps toward the monster; code 8 is the monster's own cell ("arrived"), with step (0, 0):

| code | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|---|
| step (dx, dy) | (0,−1) | (1,−1) | (1,0) | (1,1) | (0,1) | (−1,1) | (−1,0) | (−1,−1) | (0,0) |

```
reachable(x, y):
    if (x, y) is a wall or door cell: not reachable          (this first test applies even if (x, y) is the monster's cell)
    loop:
        (x, y) = (x, y) + step(code(x, y))
        if code(x, y) = 8: reachable                          (a cell reached by stepping is never tested once it is the monster's cell)
        if (x, y) is a wall or door cell: not reachable
```

### 14.2 Search

```
origin = the monster's position
start  = origin + (2, 3)       if that point lies in the monster's room or one of its adjacent rooms
       = origin                otherwise
if start is free and reachable: use it
for ring radius ρ = 1, 2, …, 49:              (square rings around start)
    scan the ring in this exact order:
        for y = start.y − ρ to start.y + ρ:                    (pass 1: the two side columns)
            for x in (start.x − ρ, start.x + ρ): try (x, y)
        for x = start.x − ρ + 1 to start.x + ρ − 1:            (pass 2: top and bottom rows, no corners)
            for y in (start.y − ρ, start.y + ρ): try (x, y)
    among the free, reachable cells of this ring, choose the one with the smallest |dx| + |dy| from start;
        on a tie, keep the first one found in the scan order above
        (example: if only start+(−1,+1) and start+(+1,−1) are usable in ring 1, the choice is start+(+1,−1))
    if any cell was found in this ring: use it and stop
if nothing was found within radius 49: place the item at start anyway (even if occupied)
if start itself is not inside any known room: no item is created
```

### 14.3 The item on the ground

The item lies at the chosen subtile and blocks it for later placements. It has no owner: Diablo II has no loot ownership.

Items dropped by monsters have **no expiry while their area stays loaded** (section 16). Clients see the item, with all final values, on their next update. The falling animation is purely visual.

---

## 15. Step 12: scripted drops after the treasure class

Some deaths also create fixed items outside the treasure-class system. These use **fixed item codes**, not treasure classes. They ignore the "never drops treasure" mark and the death-cell test, and they use the placement rule of section 14 from the monster's position.

Each item, **except Baal's gold** (described below the table):
- has item level `max(mlvl, 1)`;
- uses two `G` steps and its own `B` and `A` streams, exactly as in sections 10–12;
- makes no draws from `M`.

### 15.1 When they happen

1. **Death effects** come first (section 15.4 describes those that matter for drops). The **Uber Tristram** loot is one of them.
2. **Quest scripts** come next, unless the monster was a revived corpse. A quest script runs only if that quest is still active in the game. Most quests become inactive for the whole game when the **game creator** had already completed the quest (or completed it in a previous game). The Council, the Cow King, Mephisto and Baal always run their death scripts, but some still check the same "creator already finished" condition internally.

The **credited player** for these scripts is:
- the killer, if a player;
- the killer's owner, if a player;
- in single player, if there is no killer, the single player.

### 15.2 The drops

| Monster | Condition | Items | Count |
|---|---|---|---|
| **The Cow King** (`SuperUniques.txt` Cow King) | If there is a credited player: that player has not yet killed the Cow King, and has completed the game's final quest (classic: *Terror's End*; expansion: *Eve of Destruction*). With no credited player: always. | `vps` (stamina potion). No quality is requested, so the item-local quality roll of section 11.1 is made on each potion's stream `A`; the result is then normalised to Normal | 8 |
| **Andariel** (MonStats 156) | Quest active, and the credited player has not completed *Sisters to the Slaughter* and has no reward pending | Two chipped gems/skulls, each chosen as `[gcv, gcr, gcb, gcy, gcg, gcw, skc][raw(Q) mod 7]`, then one standard gem/skull chosen as `[gsv, gsr, gsb, gsy, gsg, gsw, sku][raw(Q) mod 7]`. Each `raw(Q)` is taken just before its item. | 3 |
| **Radament** (MonStats 229) | Quest active | `ass` (Book of Skill) | the number of players in the game who are owed the book and are not carrying one |
| **Gidbinn guardian** (the unique fetish, MonStats 407, spawned at the Gidbinn altar) | Quest active, guardian spawned by the altar, and the victim is champion, unique, superunique or a boss | `g33` (The Gidbinn) | 1, once |
| **Golden Bird carrier** (the first eligible random unique spawned in Act III while the quest wants a figurine) | Quest active, and, if there is a credited player, that player has not completed *The Golden Bird*. With no credited player the drop is still attempted. | `j34` (Jade Figurine) | 1, once |
| **Council member** (`SuperUniques.txt` Ismail Vilehand, Geleb Flamefinger, Toorc Icefist) | First qualifying kill: Khalim's Flails. A later council kill: Horadric Cubes. | `qf1` (unique), then `box` | Flails: the number of Act III players who have not completed *Khalim's Will* and hold neither flail. Cubes: the number of Act III players without a cube. |
| **Mephisto** (MonStats 242) | — | `mss` (Soulstone) | the number of players newly credited with *The Guardian* by this kill (the killer, players in Durance of Hate level 3, and party members in Act III) |
| **Hephasto** (MonStats 409) | Quest active | `hfh` (Hellforge Hammer) | 1 per death |
| **Baal** (MonStats 544) | Quest active, and the credited player had not completed *Eve of Destruction* **before** this kill | gold piles. Each pile is `lo + rand(Q, 1500)`, with `lo = 1500 + 6000·d`: Normal 1500–2999, Nightmare 7500–8999, Hell 13500–14999. Gold Find does not apply. | the number of players in the Worldstone Chamber credited by this kill |
| **Uber Mephisto, Uber Diablo, Uber Baal** (MonStats 704, 705, 709) | When the third of the three has died in this game | `cm2` (Hellfire Torch); its charged skills are then refilled to their maximum (no draw). Then `std` (Standard of Heroes) | 1 torch + 1 standard per client in the game |

Notes:
- Quest-only items whose base is marked `Items.txt: unique = 1` (`ass`, `j34`, `mss`) come out as Unique without a UniqueItems row.
- Gems, potions and `box` come out Normal because their item types are Normal-only.
- Andariel, Mephisto and Radament record the quest credit **before** dropping. Baal checks the killer's completion **before** crediting, then credits, then drops gold.
- **Baal's gold** does not follow the shared rules above:
  - Each pile is created as a gold item at **item level 1**. Its base-gold draw `rand(B, 5)` still happens, but the result is then replaced by the pile amount.
  - The pile is placed by the search of section 14.2 **without the fallback**: if no free, reachable cell is found within radius 49, that pile is lost. Each of Baal's piles is placed independently.
  - Baal's piles get normal ground lifetimes (section 16) and no Gold Find.
- The Uber Tristram record of which Ubers have died is never reset within a game.
- No other kill-triggered fixed-item creation exists. Hearts, brains and other "body part" drops (`MonItemPercent.txt`) are loaded but never used.

### 15.3 The Chaos Sanctuary seal clear

When the **third seal boss dies after all five seals have been opened**, its quest script immediately kills the rest of the Sanctuary's monsters, inside the same kill. (The same clear can also be triggered by opening the last seal after the three bosses are dead.)
- **Which monsters:** every monster in a loaded Chaos Sanctuary room that is alive, hostile, and not Diablo (MonStats 243).
- **Order:** Act IV's rooms in their active-list order, then each room's units in list order.
- **How each dies:** through its own death transition, with **no killer**, so there is no experience, no quest scripts, no killer Magic Find or Gold Find, and a party size of 1.
- **Drops:** each one drops through sections 4–15 with its own stream `M`, sharing `G`, the game's unique record, and ground occupancy with everything else.
- **Timing:** all of this finishes before the seal boss's own kill finishes.

### 15.4 Death effects that matter for drops

These run in the death-effects phase: after the treasure-class drop, before quest scripts.
- **Nearby hostiles killed after a delay.** When Andariel, Blood Raven (undead only), Radament or Izual dies, eligible hostile monsters around it are scheduled to die after a random delay:
  - the delay is drawn from the **boss's** stream `M` as `rand(M, maxDelay − minDelay)`, one draw per affected monster in the order found, even when the range is a single frame;
  - MonStats 333 is never affected;
  - those monsters die, and drop, in later frames, as separate deaths with no killer.
- **Death missiles.** Radament and Mephisto each create one death missile. Creating it steps `G` once, unless `Missiles.txt` prevents the missile from being created. This happens **before** their Books of Skill or Soulstones.
- **Other missiles and objects.** Quest scripts can also create missiles or objects; examples are the Countess, the Ancients, and Baal's portal after his gold. Each created unit steps `G`.

---

## 16. End state

Once the killing blow has been fully processed:

- every item created in steps 5–12 lies on the ground at its chosen position;
- at most 6 of them came from this monster's treasure class (scripted items and the drops of monsters killed by a seal clear come on top);
- uniques that dropped are recorded in the game's unique record;
- streams `M`, `G` and, if used, `Q` have advanced by the draws listed in Appendix C, plus those made by effects outside this process (skills, missiles and objects created by death effects);
- the area's kill counter has increased, and the corpse is marked so that it is never respawned.

**Ground lifetime.** An item gets a removal time when it is dropped by a player, or when its area is unloaded:

| Item | Lifetime |
|---|---|
| Quest items | never removed |
| Magic | 30000 frames (20 min) |
| Set, rare, unique | 45000 frames (30 min) |
| Gold | 45000 frames if the pile is more than 10000 gold; otherwise 15000 frames (10 min) |
| Gems, runes and jewels (type `sock`) | 30000 frames |
| Everything else | 15000 frames |

- Items are removed in a sweep that runs every 1500 frames (60 s).
- **Monster drops are given no removal time while their area stays loaded.** They receive one, from the time of unloading, if the area unloads. When the area reloads, at least 15000 more frames are allowed.

---

## Appendix A: building the treasure-class table from data

### A.1 Order and names

Treasure-class names are matched without regard to case, up to 31 characters. The table is built in this order:

1. An empty class at position 0. Empty TC references point here and drop nothing.
2. **Automatic item-type classes:**
   - For each `ItemTypes.txt` row with `TreasureClass = 1`, in row order, 32 classes named `<code>3`, `<code>6`, …, `<code>96` (for example `weap3`, `armo87`).
   - These have Picks 1, NoDrop 0, no quality modifiers, and no group.
3. **TreasureClassEx rows**, in file order, stopping at the first row with an empty name.
   - `group` and `level` are stored as 16-bit numbers. `group` is first cut to its low 16 bits; if the result is nonzero, it is offset by the number of item types that generated automatic classes, then cut to 16 bits again. `level` is cut to 16 bits and compared as a signed value (so 40000 becomes −25536). The offset only keeps groups distinct; relative order within a group is what matters.

An entry can only refer to a class that appears **earlier** in this order, or to its own row. A forward reference is not treated as a class name; it falls through to the unique and set lookups instead. A row that refers to itself makes a cyclic TC (section 8.8).

### A.2 Automatic class contents

For automatic class `<code>L`, every item with all of the following is included:
- `Items.txt: spawnable = 1` and not a quest item;
- the item is of type `<code>` (via inheritance). Throwing potions (`tpot`) are excluded from every type's classes except `tpot` itself;
- `L − 3 < Items.txt: level ≤ L`. Each item therefore lands in exactly one band: `L = 3·⌈qlvl/3⌉`.

Items are added in **combined item-table order: all Weapons.txt rows, then Armor.txt rows, then Misc.txt rows**; this order decides which item each weighted position selects.

Each item's weight is the `ItemTypes.txt: Rarity` of the item's **own** type, minimum 1. It is not `Items.txt: rarity`. Expansion items (`version ≥ 100`) are expansion-only entries.

### A.3 Item cell grammar

An `ItemN` cell has the form `token[,key=value[,key=value…]]`, optionally in quotes. The token is resolved in this order:
1. an item code (≤ 4 characters, case-sensitive);
2. an earlier treasure-class name;
3. a `UniqueItems.txt: index` name. The unique row at position 0 cannot be referenced this way;
4. a `SetItems.txt: index` name.

If nothing matches, there is no entry.

Options must match exactly. Spaces are significant, so `"gld, mul=1280"` has the key `" mul"`, which is unknown, and no multiplier applies. An unknown key ends option parsing, but the entry is kept. A `mul=` on a unique or set entry overwrites which unique or set it names.

---

## Appendix B: behaviours that differ from common assumptions

1. **Per-entry quality options** (`cu=`, `cs=`, `cr=`, `cm=`, `ce=`, `cg=`) work only in **classic** games. The TC's own Unique/Set/Rare/Magic columns work in both.
2. Quality rolls always use the **Version 100** ItemRatio rows, even in classic games.
3. Magic Find of **10 or less** gets no diminishing returns.
4. Magic Find of **−100 or less** skips the unique, set, rare and magic rolls entirely.
5. **6 items per treasure-class drop** at most, gold included. Scripted drops and seal-clear deaths add to this. If the sixth item is gold, it gets **no Gold Find**.
6. **NoDrop player count** is party members in the *same area* plus half (rounded down) of everyone else, capped by the player count when the monster spawned.
7. A unique that has already dropped this game makes the **whole unique roll fail** if it is the one picked, even when another unique for that base was available. The result is a triple-durability rare.
8. The magic affix pick has a **+1 weight on the last eligible affix**. Bases with `magic lvl` weight affixes by `frequency × level`.
9. **Berserk champions** are +3 levels, not +2.
10. **Plain drops are never at full durability, and stacks never roll their maximum.**
11. The random/forced **ethereal** step never applies to Low, Set, quest or indestructible items. Items it makes ethereal drop at full durability. The `ethereal` property is the exception (section 12.1).
12. **Socket count** reuses the item's modifier seed rather than drawing anew. The cap is 3/4/6 by difficulty. Classic-format body armor never gets sockets.
13. In **classic** games, throwing weapons are rerolled up to 10 times per kill, then replaced by a Long Sword.
14. **Monster drops never expire while their area stays loaded.**
15. **Low-quality class items** cap staff-mod tiers at 4, and in expansion always give +1.
16. **Cow King's Leathers** drop only from Hell Bovines (MonStats 391).
17. **Find Item** ignores NoDrop, the "never drops treasure" mark, and the death-cell test.
18. A monster that dies **standing on a wall or door cell** drops nothing from its treasure class. Scripted quest items still drop.
19. Most **scripted quest drops** are disabled for the whole game if the game's *creator* already completed the quest.
20. **The NoDrop adjustment is floating point, not integer math.** It runs in double precision. The exact operation order matters, because it differs from the exact rational answer in rare cases (section 8.4).

---

## Appendix C: order of random-number consumption

**For one kill in an expansion game:**

```
[before this process starts: on-kill / on-death / level-up effects of the killing blow (section 4.1)]
M: Spectral Hit adjustment (1 step), if the monster has that modifier and is unique or champion
G: 1 step per poison-cloud missile created, if the monster has the poison-cloud death modifier (up to 8)
for each pick, depth-first:
    M: position          rand(M, T + N′)                (positive Picks only)
    [NoDrop or nested class → next pick]
    M: quality           up to 6 draws (unique, set, rare, magic, superior, normal/low), stopping at the first
                         success; a tier whose chance is < 1 succeeds without drawing
    M: forced ethereal   1 step, only if the force-ethereal value > 0
    M: forced socket     1 step, only if the force-socket value > 0
    [classic throwing-weapon reroll → next pick, pick given back]
    — item —
    G: 2 steps → B, A, m₀
    B: base attributes (gold | stack | durability, defense | stack, durability | stack), then inventory graphic
    A: quality application:
         magic:    prefix coin, [prefix choice, prefix values], suffix coin, [suffix choice, suffix values], staff mods
         rare:     prefix name, suffix name, affix count, then per slot [side coin] + affix coin + affix choice,
                   then all affix values in the order p1, s1, p2, s2, p3, s3, then staff mods
         unique:   choice (unless named), then prop1..prop12 values
         set:      choice (unless named), then prop values, then partial-set values
         superior: row draws until a fitting row, then up to 2 values, then staff mods
         low:      name; durability on B; staff mods
         normal:   staff mods (Normal charms: magic affix procedure first)
         each fallback: reset A to (a, 666), then the next generator's draws
    A: ethereal roll (if eligible)
    A: socket roll (if eligible); the count uses m₀, no draw
    A: automatic affix: coin, choice, values (if eligible)
M: (after the drop) death-effect randomness: corpse explosions, and one rand(M, range) per nearby monster
   scheduled to die by Andariel, Blood Raven, Radament or Izual (section 15.4)
G: (after the drop) 1 step per death missile created: Radament, Mephisto (before their scripted items)
then scripted drops: per item, G×2 and its own B/A draws; Q once per Andariel gem and once per Baal gold pile
```

**Staff-mod draws:** 1 (count), then per skill: 1 (tier) + 1–6 (skill choice) + 1 (level, unless an expansion low-quality item).

**Value draws** follow the per-function rules in section 11.9, not a flat "one per modifier":
- a rolled value draws once only if `min ≠ max`;
- a reused value draws only when the value being reused is 0;
- functions 11, 18, 20 and 23 never draw; functions 15 and 16 draw only when their fixed field is 0 (section 11.9);
- an affix pick with no eligible rows makes no choice draw (its coin is still drawn);
- function 19 (charges) always draws exactly once, for the current charges.

---

## Appendix D: points not fully confirmed

1. **Other draws before the drop.** Inside the death transition, the only known draws are Spectral Hit's step of `M` and the poison-cloud missiles' steps of `G`. Missile set-up was not exhaustively checked for further draws. Effects that run before the death transition (section 4.1) are skill-system behaviour and are outside this process.
2. **Death-effect details.** The radius and delay range for each boss's scheduled deaths, and the full list of death effects that create units, are summarised rather than specified (section 15.4).
3. **Data values.** The vanilla 1.14d `.txt` values (ItemRatio numbers, which item types generate automatic classes, chest TC names) are not reproduced here. This process is data-driven; supply the real tables.
4. **Ladder-only uniques.** Behaviour depends on whether your UniqueItems.txt has any ladder-only rows.
5. **Converted monsters and the quest drop rule.** It was not checked which vanilla `States.txt` rows carry the `exp` mark that the conversion test relies on.
6. **Modifier seed and sockets.** It is assumed that only fallbacks change the modifier seed, and that no generator changes it otherwise. If one did, socket counts would differ.
7. **No live replay.** The process has not been replayed against a running game with known seeds.
