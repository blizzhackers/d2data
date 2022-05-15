<script setup>
import { reactive, computed } from "vue";

import "../../../objext.js";
import levels from "../../../json/levels.json";
import items from "../../../json/items.json";
import treasureclassex from "../../../json/treasureclassex.json";
import atomic from "../../../json/atomic.json";
import tcprecalc from "../../../json/tcprecalc.json";

levels[47]['*StringName'] = 'Act 2 ' + levels[47]['*StringName'];
levels[48]['*StringName'] = 'Act 2 ' + levels[48]['*StringName'];
levels[49]['*StringName'] = 'Act 2 ' + levels[49]['*StringName'];
levels[92]['*StringName'] = 'Act 3 ' + levels[92]['*StringName'];
levels[93]['*StringName'] = 'Act 3 ' + levels[93]['*StringName'];

const data = reactive({
  drops: {},
});

for (let c = 0; c < 659; c++) {
  data.drops[c] = 0;
}

const calcCache = {};

function forEachPick (tcName, func) {
  for (let c = 1; c < 10; c++) {
    if (treasureclassex[tcName]['Item' + c] && treasureclassex[tcName]['Prob' + c]) {
      func(treasureclassex[tcName]['Prob' + c], treasureclassex[tcName]['Item' + c]);
    }
  }
}

function calcDrops (tcName, players = 1, mult = 1, drops = {}, doCache = true) {
  if (doCache) {
    let cacheKey = [tcName, players, mult].join('|');

    if (calcCache[cacheKey]) {
      return calcCache[cacheKey];
    }
    else {
      calcCache[cacheKey] = drops;
    }
  }

  if (tcprecalc[tcName]) {
    mult *= tcprecalc[tcName].droprate[players];

    tcprecalc[tcName].counts.forEach((ratio, key) => {
      calcDrops(key, players, mult * ratio, drops, false);
    });
  }
  else {
    drops[tcName] = drops[tcName] || 0;
    drops[tcName] += mult;
  }

  return drops;
}

function calcDropsHard (tcName, players = 1, mult = 1, drops = {}) {
  if (treasureclassex[tcName]) {
    let total = treasureclassex[tcName]['noDrop'] || 0;

    if (!treasureclassex[tcName]['Picks'] || treasureclassex[tcName]['Picks'] < 1) {
      throw new Error('Nope');
    }

    mult *= (1 + treasureclassex[tcName]['Picks']) / 2;

    forEachPick(tcName, prob => {
      total += prob;
    });

    forEachPick(tcName, (prob, item) => {
      calcDropsHard(item, players, mult * prob / total, drops);
    });
  } else if (atomic[tcName]) {
    atomic[tcName].forEach((chance, itc) => {
      calcDropsHard(itc, players, mult * chance, drops);
    });
  } else {
    drops[tcName] = drops[tcName] || 0;
    drops[tcName] += mult;
  }

  return drops;
}

calcDrops('Act 2 (H) Unique B', 1).forEach((ratio, key) => {
  if (items[key]) {
    data.drops[items[key].classid] = ratio;
  }
});

</script>

<template>
  <div>
    <pre>{{ JSON.stringify(data.drops, null, ' ') }}</pre>
  </div>
</template>

<style>

</style>
