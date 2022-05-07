<script setup>
import { reactive, computed } from "vue";

import "../../../objext.js";
import monlvl from "../../../json/monlvl.json";
import levels from "../../../json/levels.json";
import monstats from "../../../json/monstats.json";
import monpopulationest from "../../../json/monpopulationest.json";
import moncountest from "../../../json/moncountest.json";
import superuniques from "../../../json/superuniques.json";

levels[47]['*StringName'] = 'Act 2 ' + levels[47]['*StringName'];
levels[48]['*StringName'] = 'Act 2 ' + levels[48]['*StringName'];
levels[49]['*StringName'] = 'Act 2 ' + levels[49]['*StringName'];
levels[92]['*StringName'] = 'Act 3 ' + levels[92]['*StringName'];
levels[93]['*StringName'] = 'Act 3 ' + levels[93]['*StringName'];

// 57e2f6
const expCurve = [13, 16, 110, 159, 207, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 225, 174, 92, 38, 5];
const expPenalty = [1024, 976, 928, 880, 832, 784, 736, 688, 640, 592, 544, 496, 448, 400, 352, 304, 256, 192, 144, 108, 81, 61, 46, 35, 26, 20, 15, 11, 8, 6, 5];

const data = reactive({
  level: 1,
  mindmg: 1,
  maxdmg: 1,
  damageType: '',
  areaRestrict: 'combat',
  areaSizeNormalize: 1,
  minGrade: 60,
  clearMode: 'all',
});

function clamp (min, value, max) {
  if (value < min) {
    return min;
  }

  if (value > max) {
    return max;
  }

  return value;
}

function expModifier (mlvl) {
  let diff = data.level < 25 ? clamp(-10, mlvl - data.level, 10) : clamp(-10, mlvl - data.level, 0);
  let diffmod = expCurve[diff + 10];
  let lvlmod = expPenalty[clamp(69, data.level, 99) - 69];

  return lvlmod * diffmod / 1024 / 255;
}

function monEffort (monId, mlvl, diff, type, superId) {
  let exp = expModifier(mlvl) * (monlvl[mlvl][s('L-XP', diff)] || 0),
    hp = (monlvl[mlvl][s('L-HP', diff)] || 0) * (
      (monstats[monId][['minHP', 'MinHP(N)', 'MinHP(H)'][diff]] || 0) +
      (monstats[monId][['maxHP', 'MaxHP(N)', 'MaxHP(H)'][diff]] || 0)
    ) / 200,
    dmg = 1;

  let minion = type === -1;

  if (minion) {
    type = 0;
    exp *= 5;
  }
  else {
    exp *= [1, 3, 5, 5, 5][type];
  }

  hp *= minion ? [2, 1.75, 1.5][diff] : [
    1,
    [3, 2.5, 2][diff],
    [4, 3, 2][diff],
    [4, 3, 2][diff],
    1,
  ][type];

  if (data.damageType) {
    let res = monstats[monId][s('Res' + data.damageType, diff)] || 0;

    dmg = (data.mindmg + data.maxdmg) / 2;

    if (superId) {
      let mods = {};

      for (let c = 1; c < 5; c++) {
        if (superuniques[superId]['Mod' + c]) {
          mods[superuniques[superId]['Mod' + c]] = superuniques[superId]['Mod' + c];
        }
      }

      switch (data.damageType) {
        case 'Dm':
          if (mods[28]) {
            res += 50;
          }

          break;
        case 'Fi':
          if (mods[9]) {
            res += diff === 2 ? 100 : 75;
          }

          if (mods[8]) {
            res += 40;
          }

          break;
        case 'Li':
          if (mods[17]) {
            res += diff === 2 ? 100 : 75;
          }

          if (mods[8]) {
            res += 40;
          }

          break;
        case 'Co':
          if (mods[18]) {
            res += diff === 2 ? 100 : 75;
          }

          if (mods[8]) {
            res += 40;
          }

          break;
        case 'Po':
          if (mods[9]) {
            res += diff === 2 ? 100 : 75;
          }

          if (mods[8]) {
            res += 40;
          }

          break;
      }
    }
    
    hp /= clamp(0, 1 - res / 100, 2);
  }

  exp *= (monstats[monId][s('Exp')] || 0) / 100;

  let hitstokill = isFinite(hp) ? Math.max(1, Math.ceil(hp / dmg)) : Infinity;

  return exp / hitstokill;
}

function s(key, diff) {
  return '' + key + ['', '(N)', '(H)'][diff || 0];
}

function t(key, diff) {
  return '' + key + [' (norm)', ' (nm)', ' (hell)'][diff || 0];
}

const grades = [
  [97, 'A+'],
  [93, 'A'],
  [90, 'A-'],
  [87, 'B+'],
  [83, 'B'],
  [80, 'B-'],
  [77, 'C+'],
  [73, 'C'],
  [70, 'C-'],
  [67, 'D+'],
  [63, 'D'],
  [60, 'D-'],
  [0, 'F'],
];

function grade (score) {
  for (let i = 0; i < grades.length; i++) {
    if (score >= grades[i][0]) {
      return grades[i][1];
    }
  }

  return 'F';
}

const results = computed(() => {
  let ret = {};

  [0, 1, 2].forEach(diff => {
    let makelvlkey = lvlId => t(levels[lvlId]['*StringName'] + ' [ID ' + lvlId + ']', diff);

    monpopulationest.forEach((leveldata, lvlId) => {
      if (data.level < 20 && (data.areaRestrict !== 'any' && diff > 0 || diff >= 0 && lvlId >= 128)) {
        return;
      }

      if (data.level < 40 && (data.areaRestrict !== 'any' && diff > 1 || diff >= 1 && lvlId >= 128)) {
        return;
      }

      if (data.level < 60 && (data.areaRestrict !== 'any' && diff > 2 || diff >= 2 && lvlId >= 128)) {
        return;
      }

      if ([32, 133, 134, 135, 136].includes(lvlId | 0)) {
        return;
      }

      if (!moncountest[lvlId]) {
        return;
      }

      let totalest = (moncountest[lvlId][diff] || 0)**data.areaSizeNormalize;

      if (totalest <= 0) {
        return;
      }

      if (['all', 'norm'].includes(data.clearMode)) {
        leveldata.normal.forEach((monData, monId) => {
          let mlvl = monData[s('mlvl', diff)] || 0,
            packCount = monData[s('packCount', diff)] || 0,
            lvlkey = makelvlkey(lvlId),
            group = ((monstats[monId]['MinGrp'] || 0) + (monstats[monId]['MaxGrp'] || 0)) / 2,
            party = ((monstats[monId]['PartyMin'] || 0) + (monstats[monId]['PartyMax'] || 0)) / 2,
            minions = [
              monstats[monId]['minion1'] || null,
              monstats[monId]['minion2'] || null,
            ].filter(Boolean);

          if (data.areaRestrict === 'combat' && mlvl > data.level + 5) {
            return;
          }

          if (mlvl > 0 && packCount > 0) {
            ret[lvlkey] = ret[lvlkey] || 0;
            ret[lvlkey] += monEffort(monId, mlvl, diff) * packCount * group / totalest;

            if (minions.length && party > 0) {
              minions.forEach(minionId => {
                ret[lvlkey] += monEffort(minionId, mlvl, diff) * packCount * party / minions.length / totalest;
              });
            }
          }
        });
      }

      leveldata.champion.forEach((monData, monId) => {
        let mlvl = (monData[s('mlvl', diff)] || 0) + 2,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = makelvlkey(lvlId),
          group = 3,
          party = ((monstats[monId]['PartyMin'] || 0) + (monstats[monId]['PartyMax'] || 0)) / 2,
          minions = [
            monstats[monId]['minion1'] || null,
            monstats[monId]['minion2'] || null,
          ].filter(Boolean);

        if (data.areaRestrict === 'combat' && mlvl > data.level + 5) {
          return;
        }

        if (mlvl > 0 && packCount > 0) {
          ret[lvlkey] = ret[lvlkey] || 0;

          if (['all', 'champs'].includes(data.clearMode)) {
            ret[lvlkey] += monEffort(monId, mlvl, diff, 1) * packCount * group / totalest;
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              ret[lvlkey] += monEffort(minionId, mlvl, diff, -1) * packCount * party / minions.length / totalest;
            });
          }
        }
      });

      leveldata.unique.forEach((monData, monId) => {
        let mlvl = (monData[s('mlvl', diff)] || 0) + 3,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = makelvlkey(lvlId),
          group = 1,
          party = ((monstats[monId]['PartyMin'] || 0) + (monstats[monId]['PartyMax'] || 0)) / 2,
          minions = [
            monstats[monId]['minion1'] || null,
            monstats[monId]['minion2'] || null,
          ].filter(Boolean);
        
        if (data.areaRestrict === 'combat' && mlvl > data.level + 5) {
          return;
        }

        if (party) {
          party += diff;
        }

        if (mlvl > 0 && packCount > 0) {
          ret[lvlkey] = ret[lvlkey] || 0;

          if (['all', 'champs'].includes(data.clearMode)) {
            ret[lvlkey] += monEffort(monId, mlvl, diff, 2) * packCount * group / totalest;
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              ret[lvlkey] += monEffort(minionId, mlvl, diff, -1) * packCount * party / minions.length / totalest;
            });
          }
        }
      });

      leveldata.superunique.forEach((monData, superId) => {
        let mlvl = (monData[s('mlvl', diff)] || 0) + 3,
          monId = superuniques[superId].Class,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = makelvlkey(lvlId),
          lvlkeybaal = makelvlkey(132),
          group = 1,
          party = ((superuniques[superId]['MinGrp'] || 0) + (superuniques[superId]['MaxGrp'] || 0)) / 2,
          minions = [
            monstats[monId]['minion1'] || null,
            monstats[monId]['minion2'] || null,
          ].filter(Boolean);

        if (data.areaRestrict === 'combat' && mlvl > data.level + 5) {
          return;
        }

        if (party) {
          party += diff;
        }

        if (mlvl > 0 && packCount > 0) {
          ret[lvlkey] = ret[lvlkey] || 0;

          if (['all', 'champs'].includes(data.clearMode)) {
            let effort = monEffort(monId, mlvl, diff, 3, superId) * packCount * group / totalest;
            ret[lvlkey] += effort;

            if (lvlId == 131) {
              ret[lvlkeybaal] += effort;
            }
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              let meffort = monEffort(minionId, mlvl, diff, -1) * packCount * party / minions.length / totalest;
              ret[lvlkey] += meffort;

              if (lvlId == 131) {
                ret[lvlkeybaal] += meffort;
              }
            });
          }
        }
      });

      leveldata.boss.forEach((monData, monId) => {
        let mlvl = monData[s('mlvl', diff)] || 0,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = t(levels[lvlId]['*StringName'] + ' [ID ' + lvlId + ']', diff);

        if (data.areaRestrict === 'combat' && mlvl > data.level + 5) {
          return;
        }

        if (mlvl > 0 && packCount > 0) {
          ret[lvlkey] = ret[lvlkey] || 0;

          if (['all'].includes(data.clearMode)) {
            ret[lvlkey] += monEffort(monId, mlvl, diff, 4) * packCount / totalest;
          }
        }
      });
    });

    let newret = ret;

    ({
      22: [21],
      23: [21, 22],
      24: [21, 22, 23],
      25: [21, 22, 23, 24],
      36: [35],
      37: [35, 36],
      73: [72],
      89: [88],
      91: [88, 89],
      93: [92],
      94: [80],
      95: [80],
      96: [81],
      97: [81],
      98: [82],
      99: [82],
      102: [101],
      132: [131],
    }).forEach((sourcelvlIds, lvlId) => {
      let n = ret[makelvlkey(lvlId)] * moncountest[lvlId][diff], d = moncountest[lvlId][diff];

      sourcelvlIds.forEach(sourcelvlId => {
        n += ret[makelvlkey(sourcelvlId)] * moncountest[sourcelvlId][diff] / 2;
        d += moncountest[sourcelvlId][diff] / 2;
      });

      newret[makelvlkey(lvlId)] = n / d;
    });    

    ret = newret;
  });

  let max = 0;

  ret = ret.map(v => {
    v = v || 0;
    max = Math.max(v, max);
    return v;
  });

  ret = ret.map(v => v * 100 / max).filter(v => v >= data.minGrade).toArray().sort((a, b) => b[1] - a[1]);
  ret[0][1] = 100;

  return ret.filter(Boolean);
});

</script>

<template>
  <div>
    <div class="row">
      <div class="col-auto" style="width:5.5rem">
        <label class="form-label">Level</label>
        <input
          class="form-control"
          type="number"
          min="1"
          max="98"
          step="1"
          v-model.number="data.level"
        />
      </div>
      <div class="col-auto">
        <label class="form-label">Element</label>
        <select class="form-select" v-model="data.damageType">
          <option value="">Unknown</option>
          <option value="Dm">Physical</option>
          <option value="Ma">Magic</option>
          <option value="Fi">Fire</option>
          <option value="Li">Lightning</option>
          <option value="Co">Cold</option>
          <option value="Po">Poison</option>
        </select>
      </div>
      <div class="col-auto">
        <label class="form-label">Area Restrictions</label>
        <select class="form-select" v-model="data.areaRestrict">
          <option value="any">Any Area</option>
          <option value="no grush">Quest Gated (No Glitch Rush)</option>
          <option value="combat">Reasonable Combat (+5 over level)</option>
        </select>
      </div>
      <div class="col-auto">
        <label class="form-label">Clear Mode</label>
        <select class="form-select" v-model="data.clearMode">
          <option value="all">All</option>
          <option value="champs">Champions / Uniques / Minions</option>
          <option value="norm">Normal Mobs Only</option>
        </select>
      </div>
      <div class="col-auto">
        <label class="form-label">Minimum Grade</label>
        <select class="form-select" v-model="data.minGrade">
          <option v-for="grade in grades" :key="grade[0]" :value="grade[0]">{{ grade[1] }}</option>
        </select>
      </div>
      <div class="col-auto" style="width:15rem">
        <label class="form-label">Area Size Normalization: {{ data.areaSizeNormalize.toFixed(2) }}</label>
        <input
          class="form-range"
          type="range"
          min="0"
          max="2"
          :step="1/6"
          v-model.number="data.areaSizeNormalize"
        />
      </div>
      <div v-if="data.damageType" class="col-auto" style="width:8rem">
        <label class="form-label">Min Damage</label>
        <input
          class="form-control"
          type="number"
          min="1"
          step="1"
          v-model.number="data.mindmg"
        />
      </div>
      <div v-if="data.damageType" class="col-auto" style="width:8rem">
        <label class="form-label">Max Damage</label>
        <input
          class="form-control"
          type="number"
          min="1"
          step="1"
          v-model.number="data.maxdmg"
        />
      </div>
    </div>
    <table class="table">
      <thead>
        <tr><th>Area</th><th>Rating</th><th>Grade</th></tr>
      </thead>
      <tbody>
        <tr v-for="(level, index) in results" :key="index">
          <td>{{ level[0] }}</td>
          <td>{{ Math.floor(level[1]) }}%</td>
          <td>{{ grade(level[1]) }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<style>

</style>
