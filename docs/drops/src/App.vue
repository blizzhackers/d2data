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

function int (num) {
  return Math.trunc(num);
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
    let chance = (base - int(difference / divisor)) * 128;

    if (mf !== 0) {
      let newmf = newmf > 10 ? diminishFactor ? int((newmf * diminishFactor) / (newmf + diminishFactor)) : (newmf | 0) : mf;

      chance = int((chance * 100) / (100 + newmf));
    }

    chance = Math.max(min, chance);
    chance = (chance - int(chance * factor / 1024));

    return chance <= 128 ? 1 : 128 / chance;
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
  mlvl: 87,
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
    isuber = item.code === item.ultracode || item.code === item.ubercode,
    isclass = type.Class,
    ratio = Object.values(itemratio).filter(data => data.Version && !isuber === !data.Uber && !isclass === !data['Class Specific']).sort((a, b) => b.Version - a.Version)[0],
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
      calcQuality = ratio.func[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal']) {
    let rarity = 'set',
      qualityNumber = 5,
      calcQuality = ratio.func[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal'] && type['Rare']) {
    let rarity = 'rare',
      qualityNumber = 6,
      calcQuality = ratio.func[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal']) {
    let rarity = 'magic',
      qualityNumber = 4,
      calcQuality = ratio.func[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Normal'] && !type['Magic']) {
    let rarity = 'hq',
      qualityNumber = 3,
      calcQuality = ratio.func[rarity],
      qchance = chance * calcQuality(data.mf, data.mlvl, item.level || 0, mods[rarity]),
      key = [classid, qualityNumber].join(' ');

    chance -= qchance;

    drops[key] = drops[key] || 0;
    drops[key] += qchance;
  }

  if (!type['Magic']) {
    let rarity = 'normal',
      qualityNumber = 2,
      calcQuality = ratio.func[rarity],
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
          <option v-for="(tc, classid) in Object.values(treasureclassex).sort((a, b) => a.lineNumber - b.lineNumber)" :key="classid" :value="tc['Treasure Class']">[{{ classid + 161 }}] {{ tc['Treasure Class'] }}</option>
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
    <div v-if="treasureclassex[data.tcname].level">TC Level: {{ treasureclassex[data.tcname].level }}</div>
    <div v-if="data.downloadName.length">Filename: {{ data.downloadName }}.txt</div>
    <table class="table table-hover">
      <thead>
        <tr><th style="width:7%">classid</th><th style="width:63%">quality</th><th style="width:20%">chance</th><th style="width: 10%">ratio</th></tr>
      </thead>
      <tbody>
        <tr v-for="(line, index) in data.output.split('\n').filter(l => l.length).map(line => line.split(' '))" :key="index" :class="{
          'table-info': data.rowSelect === index,
        }">
          <td>{{ line[0] }} ({{ lookupClassId(line[0] | 0) }})</td>
          <td>{{ line[1] }}
            <template v-if="line[1] == 1">(Low Quality)</template>
            <template v-if="line[1] == 2">(Normal)</template>
            <template v-if="line[1] == 3">(Superior)</template>
            <template v-if="line[1] == 4">(Magic)</template>
            <template v-if="line[1] == 5">(Set)</template>
            <template v-if="line[1] == 6">(Rare)</template>
            <template v-if="line[1] == 7">(Unique)</template>
          </td>
          <td>{{ line[2] }}</td>
          <td>~{{ Math.max(Math.round(Number(line[2])), 1) }}:{{ Math.max(Math.round(1 / Number(line[2])), 1) }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<style>

</style>
