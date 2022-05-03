<script setup>
import { reactive, computed } from "vue";

import objext from "../../../objext.js";
import experience from "../../../json/experience.json";
import monlvl from "../../../json/monlvl.json";
import levels from "../../../json/levels.json";
import monstats from "../../../json/monstats.json";
import monpopulationest from "../../../json/monpopulationest.json";
import superuniques from "../../../json/superuniques.json";

// 57e2f6
const expCurve = [13, 16, 110, 159, 207, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 225, 174, 92, 38, 5];
const expPenalty = [1024, 976, 928, 880, 832, 784, 736, 688, 640, 592, 544, 496, 448, 400, 352, 304, 256, 192, 144, 108, 81, 61, 46, 35, 26, 20, 15, 11, 8, 6, 5];

const data = reactive({
  level: 1,
  perKill: 0,
  damageType: '',
  areaRestrict: 'combat',
  minGrade: 90,
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

function monEffort (monId, mlvl, diff, superId) {
  let ret = expModifier(mlvl) * (monlvl[mlvl][s('L-XP', diff)] || 0) / (data.perKill ? 1 : (monlvl[mlvl][s('L-HP', diff)] || 0));

  if (monId && monstats[monId]) {
    if (data.damageType) {
      let res = monstats[monId][s('Res' + data.damageType, diff)] || 0;

      if (superId) {
        let mods = {}, c = 1;

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
      
      let resmod = clamp(-1, 1 - res / 100, 1);

      ret *= resmod;
    }

    if (monstats[monId][s('Exp')] !== undefined) {
      ret *= monstats[monId][s('Exp')] / 100;
    }
  }
  
  return ret;
}

function s(key, diff) {
  return '' + key + ['', '(N)', '(H)'][diff || 0];
}

function t(key, diff) {
  return '' + key + [' (N)', ' (NM)', ' (H)'][diff || 0];
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

      if (lvlId > 132) {
        return;
      }

      leveldata.normal.forEach((monData, monId) => {
        let mlvl = monData[s('mlvl', diff)] || 0,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = t(levels[lvlId]['*StringName'] + ' [ID ' + lvlId + ']', diff),
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

          if (data.clearMode !== 'champs') {
            ret[lvlkey] += monEffort(monId, mlvl, diff) * packCount * group;
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              if (data.clearMode !== 'champs') {
                ret[lvlkey] += monEffort(minionId, mlvl, diff) * packCount * party / minions.length;
              }
            });
          }

        }
      });

      leveldata.champion.forEach((monData, monId) => {
        let mlvl = (monData[s('mlvl', diff)] || 0) + 2,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = t(levels[lvlId]['*StringName'] + ' [ID ' + lvlId + ']', diff),
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

          if (data.clearMode !== 'norm') {
            ret[lvlkey] += monEffort(monId, mlvl, diff) * 3 * packCount * group;
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              ret[lvlkey] += monEffort(minionId, mlvl, diff) * 5 * packCount * party / minions.length;
            });
          }
        }
      });

      leveldata.unique.forEach((monData, monId) => {
        let mlvl = (monData[s('mlvl', diff)] || 0) + 3,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = t(levels[lvlId]['*StringName'] + ' [ID ' + lvlId + ']', diff),
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

          if (data.clearMode !== 'norm') {
            ret[lvlkey] += monEffort(monId, mlvl, diff) * 5 * packCount * group;
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              ret[lvlkey] += monEffort(minionId, mlvl, diff) * 5 * packCount * party / minions.length;
            });
          }
        }
      });

      leveldata.superunique.forEach((monData, superId) => {
        let mlvl = (monData[s('mlvl', diff)] || 0) + 3,
          monId = superuniques[superId].Class,
          packCount = monData[s('packCount', diff)] || 0,
          lvlkey = t(levels[lvlId]['*StringName'] + ' [ID ' + lvlId + ']', diff),
          lvlkeybaal = t(levels[132]['*StringName'] + ' [ID 132]', diff),
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

          if (data.clearMode !== 'norm') {
            ret[lvlkey] += monEffort(monId, mlvl, diff, superId) * 5 * packCount * group;

            if (lvlId == 131) {
              ret[lvlkeybaal] += monEffort(monId, mlvl, diff) * 5 * packCount * group;
            }
          }

          if (minions.length && party > 0) {
            minions.forEach(minionId => {
              ret[lvlkey] += monEffort(minionId, mlvl, diff) * 5 * packCount * party / minions.length;

              if (lvlId == 131) {
                ret[lvlkeybaal] += monEffort(minionId, mlvl, diff) * 5 * packCount * party / minions.length;
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

          if (data.clearMode !== 'norm') {
            ret[lvlkey] += monEffort(monId, mlvl, diff) * 5 * packCount;
          }
        }
      });
    });
  });

  let max = 0;

  ret = ret.map(v => {
    v = v || 0;
    max = Math.max(v, max);
    return v;
  });

  ret = ret.map(v => v * 100 / max).filter(v => v >= data.minGrade).toArray().sort((a, b) => b[1] - a[1]);
  ret[0][1] = 100;

  return ret;
});

</script>

<template>
  <div class="card">
    <h1 class="card-header bg-primary text-light text-center">
      Best Leveling Areas
    </h1>
    <div class="card-body">
      <div class="row">
        <div class="col-auto">
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
          <label class="form-label">Calculation</label>
          <select class="form-select" v-model="data.perKill">
            <option :value="0">EXP per damage</option>
            <option :value="1">EXP per kill</option>
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
            <option value="champs">Champions or Better</option>
            <option value="norm">Normal Mobs Only</option>
          </select>
        </div>
        <div class="col-auto">
          <label class="form-label">Minimum Grade</label>
          <select class="form-select" v-model="data.minGrade">
            <option v-for="grade in grades" :key="grade[0]" :value="grade[0]">{{ grade[1] }}</option>
          </select>
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
    <div class="card-footer text-center">
      <em>Powered by <a href="https://vuejs.org">Vue.js</a> and <a href="https://getbootstrap.com">Bootstrap 5</a></em>
    </div>
  </div>
</template>

<style>
@import "https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css";
</style>
