<script setup>
import { reactive, computed } from "vue";

import "../../../objext.js";
import levels from "../../../json/levels.json";
import items from "../../../json/items.json";
import itemtypes from "../../../json/itemtypes.json";
import itemratio from "../../../json/itemratio.json";
import treasureclassex from "../../../json/treasureclassex.json";
import tcprecalc from "../../../json/tcprecalc.json";

levels[47]['*StringName'] = 'Act 2 ' + levels[47]['*StringName'];
levels[48]['*StringName'] = 'Act 2 ' + levels[48]['*StringName'];
levels[49]['*StringName'] = 'Act 2 ' + levels[49]['*StringName'];
levels[92]['*StringName'] = 'Act 3 ' + levels[92]['*StringName'];
levels[93]['*StringName'] = 'Act 3 ' + levels[93]['*StringName'];

function idiv (a, b) {
  return (a / b) | 0;
}

function sleep(timeout) {
  return new Promise(resolve => {
    setTimeout(resolve, timeout || 0);
  });
}

function dropChance (base, divisor, min, diminishFactor) {
  base = base || 0;
  divisor = divisor || 1;
  min = min || 0;

  return (mf, ilvl, qlvl, factor) => {
    let difference = ilvl - qlvl;
    let chance = (base - idiv(difference, divisor)) * 128;

    if (mf) {
      let newmf = newmf > 10 ? diminishFactor ? idiv(newmf * diminishFactor, newmf + diminishFactor) : (newmf | 0) : mf;

      chance = idiv(chance * 100, 100 + newmf);
    }

    chance = Math.max(min, chance);
    chance = (chance - idiv(chance * factor, 1024));
    return Math.min(1, 128 / chance);
  };
}

itemratio.forEach(data => {
  data.func = {
    unique: dropChance(data.Unique, data.UniqueDivisor, data.UniqueMin, 250),
    set: dropChance(data.Set, data.SetDivisor, data.SetMin, 500),
    rare: dropChance(data.Rare, data.RareDivisor, data.RareMin, 600),
    magic: dropChance(data.Magic, data.MagicDivisor, data.MagicMin),
    hq: dropChance(data.HiQuality, data.HiQualityDivisor),
    normal: dropChance(data.Normal, data.NormalDivisor),
  };
});

const data = reactive({
  tcname: 'Griswold (H)',
  mlvl: 84,
  mf: 0,
  players: 1,
  output: '',
  downloadName: '',
  doingIt: false,
  rowSelect: -1,
});

function iterateDrops (func = () => {}, tcName, mult = 1, drops = {}, tcpath = []) {
  tcName = tcName.trim();

  if (tcprecalc[tcName]) {
    mult *= tcprecalc[tcName].droprate[data.players];

    tcprecalc[tcName].counts.forEach((ratio, key) => {
      iterateDrops(func, key, mult * ratio, drops, [...tcpath, tcName]);
    });
  }
  else {
    func(tcName, mult, drops, tcpath);
  }

  return drops;
}

function doEntry (name, chance, drops, tcPath) {
  for (let c = 0; c < 659; c++) {
    [2, 3, 4, 5, 6, 7].forEach(quality => {
      let key = [c, quality].join(' ');
      drops[key] = drops[key] || 0;
    });
  }

  let itc = name.slice(0, 5) === '"gld,' ? 'gld' : name;

  if (!items[itc]) {
    throw new Error('Item not found: ' + name);
  }

  let item = items[itc],
    type = itemtypes[item.type],
    classid = item.classid,
    isuber = item.normcode && item.code !== item.normcode,
    isclass = type.class,
    ratioFuncs = Object.values(itemratio).filter(data => data.Version && !isuber === !data.Uber && !isclass === !data['Class Specific'])[0].func,
    mods = tcPath.reduce(({ unique, set, rare, magic, hq, normal }, v) => {
      if (treasureclassex[v]) {
        unique = Math.max(unique, treasureclassex[v]['Unique'] || 0);
        set = Math.max(set, treasureclassex[v]['Set'] || 0);
        rare = Math.max(rare, treasureclassex[v]['Rare'] || 0);
        magic = Math.max(magic, treasureclassex[v]['Magic'] || 0);
      }

      return { unique, set, rare, magic, hq, normal };
    }, {
      unique: 0,
      set: 0,
      rare: 0,
      magic: 0,
      hq: 0,
      normal: 0,
    });

  if (!type['Normal']) {
    let rarity = 'unique',
      qualityNumber = 7,
      calcQuality = ratioFuncs[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal']) {
    let rarity = 'set',
      qualityNumber = 5,
      calcQuality = ratioFuncs[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal'] && type['Rare']) {
    let rarity = 'rare',
      qualityNumber = 6,
      calcQuality = ratioFuncs[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal']) {
    let rarity = 'magic',
      qualityNumber = 4,
      calcQuality = ratioFuncs[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal'] && !type['Magic']) {
    let rarity = 'hq',
      qualityNumber = 3,
      calcQuality = ratioFuncs[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Magic']) {
    let rarity = 'normal',
      qualityNumber = 2,
      calcQuality = ratioFuncs[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }
}

async function doit () {
  data.players = Math.max(1, Math.min(8, data.players | 0));
  data.mlvl = Math.max(1, Math.min(110, data.mlvl));
  data.rowSelect = -1;

  if (!data.doingIt) {
    data.doingIt = true;
    await sleep();
    data.output = tcprecalc[data.tcname.trim()] ? Object.values(iterateDrops(doEntry, data.tcname).map((ratio, key) => ratio ? key + ' ' + ratio : null)).filter(Boolean).join('\n') : '';
    data.downloadName = `${data.tcname.trim()} [mlvl-${data.mlvl}] [p-${data.players}] [mf-${data.mf}]`;
    await sleep();
    data.doingIt = false;
  }
}

function lookupClassId(classid) {
  for (let item in items) {
    if (items[item].classid == classid) {
      return item;
    }
  }

  return '';
}

function downloadURI(uri, name) {
  var link = document.createElement('a');
  link.download = name;
  link.href = uri;
  document.body.appendChild(link);
  link.click();
  document.body.removeChild(link);
}

function download () {
  if (data.output.trim().length) {
    downloadURI('data:text/html,' + data.output, `${data.downloadName}.txt`);
  }
}

</script>

<template>
  <div>
    <div class="row align-items-end mb-3">
      <div class="col">
        <label class="form-label">TC Name</label>
        <select class="form-select" type="text" v-model="data.tcname">
          <option v-for="(tc, classid) in Object.values(treasureclassex).sort((a, b) => a.lineNumber - b.lineNumber)" :key="classid" :value="tc['Treasure Class']">{{ tc['Treasure Class'] }}</option>
        </select>
      </div>
      <div class="col">
        <label class="form-label">mlvl</label>
        <input class="form-control" type="number" min="1" max="110" v-model.number="data.mlvl">
      </div>
      <div class="col">
        <label class="form-label">players</label>
        <input class="form-control" type="number" min="1" max="8" v-model.number="data.players">
      </div>
      <div class="col">
        <label class="form-label">mf</label>
        <input class="form-control" type="number" min="0" max="1167" v-model.number="data.mf">
      </div>
      <div class="col-auto">
        <button type="button" class="btn btn-primary" @click="doit" :disabled="data.doingIt">Do it!</button>
      </div>
      <div class="col-auto">
        <button type="button" class="btn btn-primary" @click="download" :disabled="!data.output.trim().length || data.doingIt">Download</button>
      </div>
    </div>
    <div v-if="data.downloadName.length">Filename: {{ data.downloadName }}.txt</div>
    <table class="table table-hover">
      <thead>
        <tr><th style="width:7%">classid</th><th style="width:63%">quality</th><th style="width:20%">chance</th><th style="width: 10%">ratio</th></tr>
      </thead>
      <tbody>
        <tr v-for="(line, index) in data.output.split('\n').filter(l => l.length)" :key="index" :class="{
          'table-info': data.rowSelect === index,
        }"><template v-for="(cell, cellIndex) in line.split(' ')" :key="cellIndex" @click="data.rowSelect = index">
          <td>{{ cell }}
            <template v-if="cellIndex === 0">({{ lookupClassId(cell) }})</template>
            <template v-if="cellIndex === 1 && cell == 2">(Normal)</template>
            <template v-if="cellIndex === 1 && cell == 3">(Superior)</template>
            <template v-if="cellIndex === 1 && cell == 4">(Magic)</template>
            <template v-if="cellIndex === 1 && cell == 5">(Set)</template>
            <template v-if="cellIndex === 1 && cell == 6">(Rare)</template>
            <template v-if="cellIndex === 1 && cell == 7">(Unique)</template>
          </td>
          <td v-if="cellIndex === 2">~{{ Math.max(Math.round(Number(cell)), 1) }}:{{ Math.max(Math.round(1 / Number(cell)), 1) }}</td>
        </template></tr>
      </tbody>
    </table>
  </div>
</template>

<style>

</style>
