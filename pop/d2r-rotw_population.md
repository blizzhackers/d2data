# d2r-rotw_population.json

Hostile monsters per level and difficulty in Diablo II: Resurrected (Reign of the
Warlock), grouped into the packs they spawn in. Every number is a mean per game for
a full clear, rounded to four decimals.

## Structure

```
{
  "generator", "game", "code", "description", "seed",
  "types":  [ quality, ... ],
  "levels": [ level, ... ]                     index = level id, 0 to 136
}

level = {
  "id", "name", "act", "town",
  "difficulties": { "normal": difficulty, "nightmare": difficulty, "hell": difficulty }
}                                              empty for towns and for id 0

difficulty = {
  "runs", "failedRuns", "areaLevel", "rooms", "populatedRooms",
  "area": { "subtiles", "walkableSubtiles", "walkableSubtilesSd",
            "populatedWalkableSubtiles", "spawnCells" },
  "total", "totalStdErr",
  "types":        { quality: monsters },
  "packs":        { monster id: pack },
  "superuniques": { name: superunique }
}

pack        = { "classId", "name", "total", "types": { quality: { mlvl: bucket } } }
superunique = { "superuniqueId", "classId", "monster", "total", "mlvl": { mlvl: bucket } }
bucket      = { "packs": n, "members": { monster id: { quality: { mlvl: n } } } }
```

## Fields

| Field | Meaning |
|-|-|
| `runs` | games the means are taken over |
| `failedRuns` | games lost to a crash in this level |
| `areaLevel` | the area's monster level (`MonLvlEx` in `levels.txt`) |
| `rooms`, `populatedRooms` | rooms in the level, and those that take random spawns |
| `area` | surface in subtiles (a tile is 5 x 5): all, walkable, the walkable figure's game-to-game spread, walkable in rooms that take random spawns, and the 3 x 3 cells random spawns roll on |
| `total` | hostile monsters per game |
| `totalStdErr` | standard error of `total` |
| `types` | `total` split by quality |
| monster id | the `Id` column of `monstats.txt` (`zombie1`); `classId` is its row |
| `superuniqueId` | row in `superuniques.txt`; `monster` is its monster id |
| mlvl | monster level, as a string key (`"68"`) |

Qualities: `normal`, `champion`, `unique` (random unique), `minion` (minion of a
unique or superunique), `superunique`, `boss` (Blood Raven, the Summoner, Izual),
`primevil` (the five act bosses). A monster's party counts as `normal`.

## Reading packs

A pack is everything one spawn created together: a group with its parties, a unique
with its minions, a champion pack, a map preset, a superunique with its escort. It is
keyed by its primary monster, the first one created: its monster id, quality and
monster level.

- `packs` is packs per game.
- `members` is every other monster in those packs, per game. It is a total across all
  the packs, not a count per pack.
- `total` beside `types` or `mlvl` is packs per game, over all of them.
- Superunique packs are listed only under `superuniques`, never under `packs`.
- A level's `total` equals Σ `packs` + Σ `members` over `packs` and `superuniques`
  together, to rounding.

Blood Moor, Normal:

```json
"zombie1": {"classId": 5, "name": "Zombie", "total": 13.9367, "types": {
  "normal": {"1": {"packs": 13.9367, "members": {"zombie1": {"normal": {"1": 6.9927}}}}}}}
```

This reads as 13.94 zombie packs per game, each led by a normal level-1 Zombie, with
6.99 more Zombies across them. That makes 1.5 Zombies per pack, and 20.93 Zombies in
all.
