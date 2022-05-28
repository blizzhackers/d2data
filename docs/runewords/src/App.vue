<script setup>
import { reactive, computed } from "vue";

import "../../../objext.js";
import runes from "../../../json/runes.json";
import itemtypes from "../../../json/itemtypes.json";
import items from "../../../json/items.json";
import properties from "../../../json/properties.json";
import strings from"../../../json/localestrings-eng.json";

itemtypes.pala.ItemType = 'Paladin Shield';
itemtypes.h2h.ItemType = 'Claw A';
itemtypes.h2h2.ItemType = 'Claw B';
itemtypes.sppl.ItemType = 'Spear or Polearm';
itemtypes.blde.ItemType = 'Sword or Dagger';
itemtypes.rod.ItemType = 'Staff or Rod';

const data = reactive({
  usedRunes: {},
  search: {
    name: '',
    types: '',
    items: '',
    mods: '',
  },
});

function getTypes(types, ret = {}) {
  (Array.isArray(types) ? types : [types]).forEach(type => {
    if (itemtypes[type]) {
      ret[type] = true;

      for (let c = 0; c < 10; c++) {
        getTypes(itemtypes[type]['Equiv' + c], ret);
      }
    }
  });

  return ret;
}

function getSubTypes(types, ret = {}) {
  if (Array.isArray(types) && types.length) {
    let tmp = types.slice();

    for (let type in itemtypes) {
      if (itemtypes[type]) {
        for (let c = 0; c < 10; c++) {
          if (tmp.includes(itemtypes[type]['Equiv' + c])) {
            ret[type] = true;
            getSubTypes([type], ret);
          }
        }
      }
    }
  }

  return ret;
}

function intersect(a, b) {
  return a.some(elem => b.includes(elem));
}

items.forEach(item => {
  item.types = Object.keys(getTypes(item.type));
});

runes.forEach(runeword => {
  runeword.runes = [];
  runeword.types = [];
  runeword.mods = [];

  for (let c = 0; c < 9; c++) {
    if (runeword['Rune' + c]) {
      let runeName = runeword['Rune' + c];
      runeword.runes.push(runeName);
      data.usedRunes[runeword['Rune' + c]] = data.usedRunes[runeword['Rune' + c]] || false;
    }

    if (runeword['itype' + c]) {
      runeword.types.push(runeword['itype' + c]);
    }

    if (runeword['T1Code' + c]) {
      runeword.mods.push({
        property: properties[runeword['T1Code' + c]],
        param: runeword['T1Param' + c],
        min: runeword['T1Min' + c],
        max: runeword['T1Max' + c],
      });
    }
  }

  runeword.validItems = Object.values(items).filter(item => {
    return intersect(runeword.types, item.types) && runeword.runes.length <= item.gemsockets;
  }).sort((a, b) => itemtypes[a.type].lineNumber - itemtypes[b.type].lineNumber || a.level - b.level);

  runeword.subTypes = Object.keys(getSubTypes(runeword.types)).filter(type => !runeword.types.includes(type) && itemtypes[type]['MaxSockets3']);

  runeword.search = {
    name: [
      runeword['*Rune Name'],
    ].join(' '),
    types: [
      ...runeword.types.map(type => itemtypes[type].ItemType),
      ...runeword.subTypes.map(type => itemtypes[type].ItemType),
    ].join(' '),
    items: [
      ...runeword.validItems.map(item => strings[item.code]),
    ].join(' '),
    mods: [
      ...runeword.mods.map(mod => mod.property['*Tooltip']).filter(Boolean),
    ].join(' '),
  };
});

const runewords = computed(() => {
  let ret = Object.values(runes).filter(runeword => runeword['complete']);

  try {
    if (data.usedRunes.reduce((t, v) => t || v, false)) {
      ret = ret.filter(runeword => {
        for (let rune in data.usedRunes) {
          if (data.usedRunes[rune] && !runeword.runes.includes(rune)) {
            return false;
          }
        }

        return true;
      });
    }

    data.search.forEach((text, key) => {
      if (text.length) {
        ret = ret.filter(runeword => new RegExp(text, 'gi').test(runeword.search[key]));
      }
    });
  } catch (e) {
    // Ignore error...
  }

  return ret;
});

</script>

<template>
  <div class="row avquest">
    <div class="col-auto">
      <label class="form-label"><strong>Runes<br>Used</strong></label>
      <div v-for="rune in Object.keys(data.usedRunes).sort().reverse()" :key="rune" class="my-1">
        <button :class="{
          'btn': true,
          'btn-outline-light': data.usedRunes[rune],
          'btn-outline-secondary': !data.usedRunes[rune],
          'fw-bold': true,
        }" style="width:4.25em" @click="() => {
          data.usedRunes[rune] = !data.usedRunes[rune];
        }">{{ strings[rune + 'L'] }}</button>
      </div>
    </div>
    <div class="col">
      <div class="row">
        <div class="col-12 col-lg-6 col-xxl-3 mb-3 mb-xxl-0">
          <input type="search" class="form-control bg-secondary" placeholder="Search a runeword name..." v-model="data.search.name">
        </div>
        <div class="col-12 col-lg-6 col-xxl-3 mb-3 mb-xxl-0">
          <input type="search" class="form-control bg-secondary" placeholder="Search an item type..." v-model="data.search.types">
        </div>
        <div class="col-12 col-lg-6 col-xxl-3 mb-3 mb-lg-0 mb-xxl-0">
          <input type="search" class="form-control bg-secondary" placeholder="Search a base item..." v-model="data.search.items">
        </div>
        <div class="col-12 col-lg-6 col-xxl-3 mb-0 mb-xxl-0">
          <input type="search" class="form-control bg-secondary" placeholder="Search an item modifier..." v-model="data.search.mods">
        </div>
      </div>
      <div class="row">
        <div v-for="runeword in runewords" :key="runeword.Name" class="col-12 col-lg-6 col-xl-4 text-center p-3">
          <div class="unique-title">{{ runeword['*Rune Name'] }}</div>
          <div class="text-info">
            <template v-for="(type, index) in runeword.types"><template v-if="index">, </template>{{ itemtypes[type].ItemType }}</template>
          </div>
          <div class="text-warning">{{ runeword.runes.map(rune => strings[rune + 'L']).join(' ') }}</div>
          <div class="text-primary">
            <div v-for="(mod, index) in runeword.mods" :key="index">{{ mod.property['*Tooltip'] }}</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style>
  @import "https://blizzhackers.github.io/d2data/css/d2font.css";

  .bg-secondary {
    background-color: hsl(208, 7%, 60%) !important;
  }

  .form-control.bg-secondary {
    color: #000;
    font-weight: 700;
  }

  .form-control.bg-secondary::placeholder {
    color: #555;
    font-weight: 700;
  }

  .unique-title {
    color: hsl(51, 24%, 65%);
  }

</style>
