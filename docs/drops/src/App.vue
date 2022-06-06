<script setup>

import { reactive, computed, watch } from "vue";
import "../../../objext.js";
import _strings from "../../../json/localestrings-eng.json";
import _levels from "../../../json/levels.json";
import _count from "../../../json/moncountest.json";
import _monstats from "../../../json/monstats.json";
import _superuniques from "../../../json/superuniques.json";
import _tc from "../../../json/treasureclassex.json";
import _tcgroups from "../../../json/treasureclassgroupsex.json";
import _tcprecalc from "../../../json/tcprecalc.json";
import _atomic from "../../../json/atomic.json";
import _itemtypes from "../../../json/itemtypes.json";
import _itemratio from "../../../json/itemratio.json";
import _allitems from "../../../json/items.json";
import _uniqueitems from "../../../json/uniqueitems.json";
import _setitems from "../../../json/setitems.json";

function _s (diff) {
  return str => str + ['', '(N)', '(H)'][diff];
}

function int (num) {
  return Math.trunc(num);
}

function sleep (ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

function dtoa (dv) {
      let bytes = [];

      for (let c = 0; c < dv.byteLength; c++) {
          bytes[c] = String.fromCharCode(dv.getUint8(c));
      }

      return btoa(bytes.join(''));
  }

function atod (str64) {
  let bytes = atob(str64), dv = new DataView(new ArrayBuffer(bytes.length));

  for (let c = 0; c < bytes.length; c++) {
    dv.setUint8(c, bytes.charCodeAt(c));
  }

  return dv;
}

let baseurl = 'https://raw.githubusercontent.com/blizzhackers/d2data/master/json/'; // https://api.blizzhackers.dev/json/d2/

const data = reactive({
  items: [],
  areaResults: [],
  packResults: [],
  visible: false,
  calculating: false,
  progress: 0,
  params: {
    mf: 0,
    rolling: 1,
    players: 1,
    group: 1,
    minilvl: 0,
    maxilvl: 110,
  },
  parammap: [
    {key: 'mf', type: 'Uint', size: 2},
    {key: 'rolling', type: 'Uint', size: 1},
    {key: 'players', type: 'Uint', size: 1},
    {key: 'group', type: 'Uint', size: 1},
    {key: 'minilvl', type: 'Uint', size: 1},
    {key: 'maxilvl', type: 'Uint', size: 1},
  ],
  itemSearch: '',
  cowsets: {
    "Cow King's Hide": true,
    "Cow King's Hoofs": true,
    "Cow King's Horns": true,
  },
});

let exp = computed(() => {
		return (data.params.players / 2 + data.params.group / 2) | 0;
});

function updateHash() {
  let items = [];
  data.items.forEach((item, index) => item.use && items.push(index));
  let paramdv = new DataView(new ArrayBuffer(data.parammap.reduce((t, line) => t + line.size, 0) + items.length * 2)), pos = 0;

  data.parammap.forEach(line => {
    paramdv['set' + line.type + (line.size * 8)](pos, data.params[line.key]);
    pos += line.size;
  });

  items.forEach(num => {
    paramdv.setUint16(pos, num);
    pos += 2;
  });

  window.location.hash = dtoa(paramdv);
}

function makeRatio(chance) {
  let ratio = 1/chance;
  return Math.round(ratio).toString();
}

function dropChance (base, divisor, min, diminishFactor) {
  base = base || 0;
  divisor = divisor || 1;
  min = min || 0;

  return (mf, ilvl, qlvl, factor) => {
    let difference = ilvl - qlvl;
    let chance = (base - int(difference / divisor)) * 128;

    if (mf !== 0) {
      let newmf = mf > 10 ? diminishFactor ? int((mf * diminishFactor) / (mf + diminishFactor)) : (mf | 0) : mf;

      chance = int((chance * 100) / (100 + newmf));
    }

    chance = Math.max(min, chance);
    chance = (chance - int(chance * factor / 1024));

    return chance <= 128 ? 1 : 128 / chance;
  };
}

function matches(a, b) {
  if (!a || !a.length) {
    return false;
  }

  a = a.toLowerCase().split(/[^a-zA-Z0-9']+/i).filter(Boolean);
  b = b.toLowerCase().split(/[^a-zA-Z0-9']+/i).filter(Boolean);

  return a.every(av => b.some(bv => bv.indexOf(av) === 0));
}

function capWords(a) {
  if (a && a.length) {
    return a.split(/([^a-zA-Z0-9']+)/i).map(word => word.charAt(0).toUpperCase() + word.slice(1)).join('');
  }

  return a;
}

function getKeywords(type, ret = {}) {
  let itemtype = _itemtypes[type];

  ret[itemtype.ItemType] = true;
  itemtype['Equiv1'] && getKeywords(itemtype['Equiv1'], ret);
  itemtype['Equiv2'] && getKeywords(itemtype['Equiv2'], ret);

  return Object.keys(ret);
}

function clearResults() {
  data.areaResults.splice(0);
  data.packResults.splice(0);
}

let adjustedTcCache = {};

function adjustTc(name, lvl) {
  let cachekey = `${name}|${lvl}`;

  if (adjustedTcCache[cachekey]) {
    return adjustedTcCache[cachekey];
  }

  if (_tc[name].group && _tcgroups[_tc[name].group]) {
    let grp = _tcgroups[_tc[name].group].toArray().map(g => {
      return [Number(g[0]), g[1]];
    }).filter(g => g[0] <= lvl).sort((a, b) => b[0] - a[0]);

    if (grp.length && grp[0] && grp[0][1]) {
      return adjustedTcCache[cachekey] = grp[0][1];
    }
  }

  return adjustedTcCache[cachekey] = name;
}

function setValidHere(set, level) {
  return level.Id === 39 || !data.cowsets[set.index];
}

async function doCalc() {
  let areaResults = [], packResults = [], selectedItems = data.items.filter(item => item.use);

  if (selectedItems.length) {
    if (data.calculating) {
      return;
    }

    data.calculating = true;
    data.progress = 0;
    clearResults();
    await sleep(0);

    let progressInterval = 1 / 3 / Object.values(_levels).length;

    for (let diff = 0; diff < 3; diff++) {
      let s = _s(diff), cache = {};

      for (let level of Object.values(_levels)) {
        let lchance = 0;

        if (diff < 2 && level.Id > 132) {
          data.progress += progressInterval;
          continue;
        }

        level.calc.monsters[diff].forEach(({mon, mlvl, type, superMon, packCount}) => {
          if (mlvl < data.params.minilvl || mlvl > data.params.maxilvl) {
            return;
          }

          let chance = 0, schance = 0;

          let calc = (m, count, mtype, isMinion) => {
            let tcname = (superMon && !isMinion) ? superMon[s('TC')] : m[s('TreasureClass' + (Math.min(3, mtype + 1)))];

            if (tcname) {
              tcname = adjustTc(tcname, mlvl);

              let tc = _tc[tcname];

              let cachekey = `${tcname}|${mtype}|${mlvl}|${Number(level.Id === 39)}`;

              let calcRes = !cachekey || cache[cachekey] === undefined ? calcPicks((pickItem, ...tcpath) => {
                let {uniqueMod, setMod, rareMod, magicMod} = [pickItem, ...tcpath].reduce(({uniqueMod, setMod, rareMod, magicMod}, v) => {
                  if (_tc[v]) {
                    uniqueMod = Math.max(uniqueMod, _tc[v]['Unique'] || 0);
                    setMod = Math.max(setMod, _tc[v]['Set'] || 0);
                    rareMod = Math.max(rareMod, _tc[v]['Rare'] || 0);
                    magicMod = Math.max(magicMod, _tc[v]['Magic'] || 0);
                  }

                  return {uniqueMod, setMod, rareMod, magicMod};
                }, {
                  uniqueMod: 0,
                  setMod: 0,
                  rareMod: 0,
                  magicMod: 0,
                }),
                  ichance = 0;

                selectedItems.forEach(item => {
                  if (item.set && !setValidHere(item.set, level)) {
                    return;
                  }

                  if (pickItem === item.code) {
                    switch (item.quality) {
                      case 'unique':
                        if (mlvl >= (item.unique.lvl || 0)) {
                          let ucount = _uniqueitems.filter(u => u.enabled && u.code === item.code && mlvl >= (u.lvl || 0)).reduce((t, u) => {
                            return t + (u.rarity || 1);
                          }, 0);

                          if (!ucount) {
                            return;
                          }

                          ichance += item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod) * item.unique.rarity / ucount;
                        }
                        break;

                      case 'set':
                        if (mlvl >= (item.set.lvl || 0)) {
                          let scount = _setitems.filter(set => set.item === item.code && mlvl >= (set.lvl || 0) && setValidHere(set, level)).reduce((t, s) => {
                            return t + (s.rarity || 1);
                          }, 0);

                          if (!scount) {
                            return;
                          }

                          ichance += (1 - item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod)) *
                            item.func.set(data.params.mf, mlvl, item.item.level || 0, setMod) * item.set.rarity / scount;
                        }
                        break;

                      case 'rare':
                        ichance += (1 - item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod)) *
                          (1 - item.func.set(data.params.mf, mlvl, item.item.level || 0, setMod)) *
                          item.func.rare(data.params.mf, mlvl, item.item.level || 0, rareMod);
                        break;
                      case 'magic':
                        ichance += (item.type.Rare ? (1 - item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod)) : 1) *
                          (item.type.Rare ? (1 - item.func.set(data.params.mf, mlvl, item.item.level || 0, setMod)) : 1) *
                          (item.type.Rare ? (1 - item.func.rare(data.params.mf, mlvl, item.item.level || 0, rareMod)) : 1) *
                          item.func.magic(data.params.mf, mlvl, item.item.level || 0, magicMod);
                        break;
                      case 'hq':
                        ichance += (item.type.Rare ? (1 - item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod)) : 1) *
                          (item.type.Rare ? (1 - item.func.set(data.params.mf, mlvl, item.item.level || 0, setMod)) : 1) *
                          (item.type.Rare ? (1 - item.func.rare(data.params.mf, mlvl, item.item.level || 0, rareMod)) : 1) *
                          (1 - item.func.magic(data.params.mf, mlvl, item.item.level || 0, magicMod)) *
                          item.func.hq(0, mlvl, item.item.level || 0, 0);
                        break;
                      case 'normal':
                        if (item.type.Normal) {
                          ichance += 1;
                        } else {
                          ichance += (item.type.Rare ? (1 - item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod)) : 1) *
                          (item.type.Rare ? (1 - item.func.set(data.params.mf, mlvl, item.item.level || 0, setMod)) : 1) *
                          (item.type.Rare ? (1 - item.func.rare(data.params.mf, mlvl, item.item.level || 0, rareMod)) : 1) *
                          (1 - item.func.magic(data.params.mf, mlvl, item.item.level || 0, magicMod)) *
                          (1 - item.func.hq(0, mlvl, item.item.level || 0, 0)) *
                          item.func.normal(0, mlvl, item.item.level || 0, 0);
                        }
                        break;
                      default:
                        ichance += (1 - item.func.unique(data.params.mf, mlvl, item.item.level || 0, uniqueMod)) *
                          (1 - item.func.set(data.params.mf, mlvl, item.item.level || 0, setMod)) *
                          (1 - item.func.rare(data.params.mf, mlvl, item.item.level || 0, rareMod)) *
                          (1 - item.func.magic(data.params.mf, mlvl, item.item.level || 0, magicMod)) *
                          (1 - item.func.hq(0, mlvl, item.item.level || 0, 0)) *
                          (1 - item.func.normal(0, mlvl, item.item.level || 0, 0));
                        break;
                    }
                  }
                });

                return ichance;
              }, tcname) : cache[cachekey];

              let pchance = calcRes;

              cache[cachekey] = pchance;

              if (!isMinion) {
                schance = pchance;
              }

              chance += pchance * count;
            }
          };

          let packSize = superMon ? 1 : avg(mon['MinGrp'] || 0, mon['MaxGrp'] || 0);

          calc(mon, packSize, type, false);

          let minionCount = superMon ? avg(superMon['MinGrp'] || 0, superMon['MaxGrp'] || 0) : avg(mon['PartyMin'] || 0, mon['PartyMax'] || 0);

          if (superMon && minionCount) {
            minionCount += diff;
          }

          if (minionCount) {
            let minions = [
              mon['minion1'] && _monstats[mon['minion1']],
              mon['minion2'] && _monstats[mon['minion2']],
            ].filter(Boolean);

            if (superMon && !minions.length) {
              minions[0] = mon;
            }

            minions.forEach(minion => {
              calc(minion, minionCount / minions.length, 0, true);
            });
          }

          if (chance) {
            packResults.push({
              mon,
              mlvl,
              superMon,
              color: ['#000000', '#3366ff', '#b8860b', '#cc33ff', '#FF0000'][type],
              name: (superMon ? _strings[superMon.Name] : _strings[mon.NameStr]) + (packSize + minionCount > 1 ? ' Pack ' : ' ') + ['[N]', '[NM]', '[H]'][diff],
              chance,
              level,
              tooltip: [
                'Type: ' + ['Normal', 'Champion', 'Unique', 'Superunique', 'Boss'][type],
                'mlvl: ' + mlvl,
                'Area: [' + level.Id + '] ' + _strings[level.LevelName],
                'Act: ' + (level.Id >= 109 ? 5 : level.Id >= 103 ? 4 : level.Id >= 75 ? 3 : level.Id >= 40 ? 2 : 1),
                schance !== chance ? 'Individual Chance: 1:' + makeRatio(schance) : null,
              ].filter(Boolean).join('\n'),
            });

            lchance += chance * packCount;
          }
        });

        if (lchance) {
          areaResults.push({
            name: _strings[level.LevelName] + [' [N]', ' [NM]', ' [H]'][diff],
            chance: lchance,
            tooltip: [
              'Id: ' + level.Id,
              'mlvl: ' + level[['MonLvlEx', 'MonLvlEx(N)', 'MonLvlEx(H)'][diff]] || 0,
              'Act: ' + (level.Id >= 109 ? 5 : level.Id >= 103 ? 4 : level.Id >= 75 ? 3 : level.Id >= 40 ? 2 : 1),
            ].filter(Boolean).join('\n'),
          });
        }

        data.progress += progressInterval;
        await sleep(0);
      }
    }

    areaResults = areaResults.sort((a, b) => {
      return b.chance - a.chance;
    });

    packResults = packResults.sort((a, b) => {
      return b.chance - a.chance;
    });

    data.areaResults.push(...areaResults);
    data.packResults.push(...packResults);
    data.calculating = false;
  }
}

function calcPicks(func, tcname, isNested, ...tcpath) {
  if (tcname && _tcprecalc[tcname]) {
    let totalchance = 0;

    _tcprecalc[tcname].counts.forEach((chance, item) => {
      totalchance += _tcprecalc[tcname][isNested ? 'droprate' : 'droprateRoot'][exp.value] * chance * calcPicks(func, item, true, tcname, ...tcpath);
    });

    return totalchance;
  }

  return func(tcname, ...tcpath);
}

function forEachMonster(level, diff, func) {
  let s = _s(diff);

  [0, 1, 2].forEach(type => {
    if (type && !level[s('MonUMin')] && !level[s('MonUMax')]) {
      return;
    }

    let m = num => level[(diff ? 'nmon' : type ? 'umon' : 'mon') + num];

    for (let c = 1; c <= 9; c++) {
      if (m(c)) {
        let mon = _monstats[m(c)];

        if (mon.enabled && mon.killable) {
          let mlvl = monlevel(mon, level, diff) + [0, 2, 3][type];

          func(mon, mlvl, type);
        }
      }
    }
  });
}

function avg(...nums) {
  return nums.reduce((t, v) => t + v, 0) / nums.length || 0;
}

function monlevel(mon, level, diff) {
  if (!diff) {
    return mon['Level'] || 0;
  }

  let s = _s(diff),
    lvl = level[['MonLvl1Ex', 'MonLvl2Ex', 'MonLvl3Ex'][diff]] || 0,
    mlvl = mon[s('Level')] || 0;

  return lvl > mlvl ? lvl : mlvl;
}

_itemratio.forEach(data => {
  data.func = {
    unique: dropChance(data.Unique, data.UniqueDivisor, data.UniqueMin, 250),
    set: dropChance(data.Set, data.SetDivisor, data.SetMin, 500),
    rare: dropChance(data.Rare, data.RareDivisor, data.RareMin, 600),
    magic: dropChance(data.Magic, data.MagicDivisor, data.MagicMin),
    hq: dropChance(data.HiQuality, data.HiQualityDivisor),
    normal: dropChance(data.Normal, data.NormalDivisor),
  };
});

[0, 1, 2].forEach(diff => {
  let s = _s(diff);
  _levels.forEach(level => {
    let l = key => level[key] || 0;

    level.calc = level.calc || {};
    level.calc.monsters = level.calc.monsters || [];
    level.calc.monsters[diff] = level.calc.monsters[diff] || [];

    if (level.Id) {
      let supers = _superuniques.filter(s => s.areaId == level.Id || s.hcIdx === 19 && [66, 67, 68, 69, 70, 71, 72].includes(level.Id | 0)),
        bosses = _monstats.filter(mon => mon.areaId == level.Id),
        acount = (_count[level.Id] && _count[level.Id][diff] || 0),
        scount = supers.reduce((total, sup) => {
          return total + 1 + diff + ((sup['MinGrp'] || 0) + (sup['MaxGrp'] || 0)) / 2;
        }, 0),
        bcount = bosses.reduce((total, mon) => {
          return total + 1 + + ((mon['MinGrp'] || 0) + (mon['MaxGrp'] || 0)) / 2;
        }, 0),
        ucount = avg(l(s('MonUMin')), l(s('MonUMax'))) * 0.8 * 5.5,
        ccount = avg(l(s('MonUMin')), l(s('MonUMax'))) * 0.2 * 3,
        count = acount - ucount - ccount - scount - bcount;

      if (count > 0) {
        let totalpackssize = 0, udiv = 0;

        forEachMonster(level, diff, (mon, mlvl, type) => {
          if (!type) {
            let m = key => mon[key] || 0;
            let packsize = avg(m('PartyMin') + m('PartyMax'), m('MinGrp') + m('MaxGrp'));

            totalpackssize += packsize;
          };

          if (type === 2) {
            udiv++;
          }
        });

        forEachMonster(level, diff, (mon, mlvl, type) => {
          let mult = [count / totalpackssize, ccount / 3 / udiv, ucount / 5.5 / udiv][type];
          level.calc.monsters[diff].push({
            mon,
            mlvl,
            type,
            packCount: mult,
          });
        });
      }

      supers.forEach(sup => {
        let mon = _monstats[sup.Class],
          mlvl = monlevel(mon, level, diff) + 3;

        level.calc.monsters[diff].push({
          mon,
          mlvl,
          type: 3,
          packCount: sup.hcIdx === 19 ? (1 / 7) : 1,
          superMon: sup,
        });
      });

      bosses.forEach(mon => {
        let mlvl = monlevel(mon, level, diff);

        level.calc.monsters[diff].push({
          mon,
          mlvl,
          type: 4,
          packCount: 1,
        });
      });
    }
  });
});

Object.values(_allitems).sort((a, b) => {
  a = a.code;
  b = b.code;
  return a < b ? -1 : a > b ? 1 : 0;
}).forEach(item => {
  let type = _itemtypes[item.type],
    itemname = _strings[item.code] || item.name,
    isExceptional = item.ubercode && item.code === item.ubercode,
    isElite = item.ultracode && item.code === item.ultracode,
    isuber = item.normcode && item.code !== item.normcode,
    isclass = type.Class,
    ratioFuncs = Object.values(_itemratio).filter(data => data.Version && !isuber === !data.Uber && !isclass === !data['Class Specific'])[0].func;

  if (['pk1', 'pk2', 'pk3', 'bet', 'ceh', 'fed', 'tes'].includes(item.code)) {
    item['spawnable'] = true;
    type['Normal'] = true;
  }

  if (!item['spawnable'] || item.code === 'gld') {
    return;
  }

  _uniqueitems.forEach(unique => {
    if (unique.code === item.code && unique['enabled']) {
      let name = _strings[unique.index] || unique.index, level = Math.max(item['level'] || 0, unique['lvl'] || 0);
      data.items.push({
        quality: 'unique',
        code: unique.code,
        item,
        type,
        level,
        name: name + ' [Unique]',
        searchable: [name, itemname, 'Unique', unique.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
        tooltip: [
          'Type: ' + itemname,
          'Code: ' + unique.code,
          'Level: ' + level,
          'Keywords: ' + [name, itemname, 'Unique', unique.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
        ].join('\n'),
        use: false,
        unique,
        func: ratioFuncs,
      });
    }
  });

  _setitems.forEach(set => {
    if (set.item === item.code) {
      let name = _strings[set.index] || set.index, level = Math.max(item['level'] || 0, set['lvl'] || 0);

      data.items.push({
        quality: 'set',
        code: set.item,
        item,
        type,
        level,
        name: name + ' [Set]',
        searchable: [name, itemname, 'Set', set.item, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
        tooltip: [
          'Type: ' + itemname,
          'Code: ' + set.item,
          'Level: ' + level,
          'Keywords: ' + [name, itemname, 'Set', set.item, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
        ].join('\n'),
        use: false,
        set,
        func: ratioFuncs,
      });
    }
  });

  if (type['Rare']) {
    let level = item['level'] || 0;
    data.items.push({
      quality: 'rare',
      code: item.code,
      item,
      type,
      level,
      name: itemname + ' [Rare]',
      searchable: [itemname, 'Rare', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      tooltip: [
        'Code: ' + item.code,
        'Level: ' + level,
        'Keywords: ' + [itemname, 'Rare', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      ].join('\n'),
      use: false,
      func: ratioFuncs,
    });
  }

  if (!type['Normal']) {
    let level = item['level'] || 0;
    data.items.push({
      quality: 'magic',
      code: item.code,
      item,
      type,
      level,
      name: itemname + ' [Magic]',
      searchable: [itemname, 'Magic', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      tooltip: [
        'Code: ' + item.code,
        'Level: ' + level,
        'Keywords: ' + [itemname, 'Magic', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      ].join('\n'),
      use: false,
      func: ratioFuncs,
    });
  }

  if (!type['Magic'] && !type['Normal']) {
    let level = item['level'] || 0;
    data.items.push({
      quality: 'hq',
      code: item.code,
      item,
      type,
      level,
      name: itemname + ' [Superior]',
      searchable: [itemname, 'Superior', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      tooltip: [
        'Code: ' + item.code,
        'Level: ' + level,
        'Keywords: ' + [itemname, 'Superior', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      ].join('\n'),
      use: false,
      func: ratioFuncs,
    });
  }

  if (!type['Magic']) {
    let level = item['level'] || 0;
    data.items.push({
      quality: 'normal',
      code: item.code,
      item,
      type,
      level,
      name: itemname + ' [Normal]',
      searchable: [itemname, 'Normal', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      tooltip: [
        'Code: ' + item.code,
        'Level: ' + level,
        'Keywords: ' + [itemname, 'Normal', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      ].join('\n'),
      use: false,
      func: ratioFuncs,
    });
  }

  if (!type['Magic'] && !type['Normal']) {
    let level = item['level'] || 0;
    data.items.push({
      quality: 'low',
      code: item.code,
      item,
      type,
      level,
      name: itemname + ' [Low Quality]',
      searchable: [itemname, 'Low Quality', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      tooltip: [
        'Code: ' + item.code,
        'Level: ' + level,
        'Keywords: ' + [itemname, 'Low Quality', item.code, ...getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
      ].join('\n'),
      use: false,
      func: ratioFuncs,
    });
  }
});

let calc = false;

let paramstr = window.location.hash.slice(1), pos = 0;

if (paramstr.length) {
  let paramdata = atod(paramstr);

  calc = true;

  data.parammap.forEach(line => {
    data.params[line.key] = paramdata['get' + line.type + (line.size * 8)](pos);
    pos += line.size;
  });

  for (;pos < paramdata.byteLength; pos += 2) {
    let index = paramdata.getUint16(pos);
    data.items[index].use = true;
  }
}

data.visible = true;

watch(data.params, () => {
  if (data.params.group > data.params.players) {
    data.params.group = data.params.players;
  }

  if (data.params.minilvl > data.params.maxilvl) {
    data.params.maxilvl = data.params.minilvl;
  }

  updateHash();
}, {
	deep: true,
});

if (calc) {
  doCalc();
}

</script>

<template>
  <div>
    <p v-if="!data.visible" class="text-center">Loading...</p>
    <template v-else>
      <div class="row mb-3 text-center">
        <div class="col-12 col-lg">
          <label>Magic Find: {{ data.params.mf }}%</label>
          <input type="range" class="form-range form-range-sm" min="0" max="1167" v-model.number="data.params.mf">
        </div>
        <div class="col-12 col-lg">
          <label>Players in Game: {{ data.params.players }}</label>
          <input type="range" class="form-range form-range-sm" min="1" max="8" v-model.number="data.params.players">
        </div>
        <div class="col-12 col-lg">
          <label>Players in Group: {{ data.params.group }}</label>
          <input type="range" class="form-range form-range-sm" min="1" :max="data.params.players" v-model.number="data.params.group">
        </div>
      </div>
      <div class="row mb-3 text-center">
        <div class="col-12 col-lg">
          <label>Minimum ilvl: {{ data.params.minilvl }}</label>
          <input type="range" class="form-range form-range-sm" min="0" :max="110" v-model.number="data.params.minilvl">
        </div>
        <div class="col-12 col-lg">
          <label>Max ilvl: {{ data.params.maxilvl }}</label>
          <input type="range" class="form-range form-range-sm" :min="data.params.minilvl" max="110" v-model.number="data.params.maxilvl">
        </div>
        <div class="col-12 col-lg-auto d-flex align-items-center">
          <button class="btn btn-primary" @click="doCalc">Do It!</button>
        </div>
      </div>
      <div class="row">
        <div class="col-12 col-lg-4">
          <div class="mb-3">
            <label>Items to include:</label>
            <input type="search" class="form-control" placeholder="Search for an item or item code..." v-model="data.itemSearch">
          </div>
          <div v-for="(item, index) in data.items" :key="index">
            <div v-if="item.use || matches(data.itemSearch, item.searchable)" class="form-check" :title="item.tooltip">
              <input type="checkbox" class="form-check-input" @change="updateHash" v-model="item.use">
              <label class="form-check-label">{{ item.name }}</label>
            </div>
          </div>
        </div>
        <div class="col-12 col-lg-4">
          <div v-if="!data.calculating">
            <table v-if="data.visible" class="table table-hover table-sm m-0 text-right">
              <thead class="table-primary">
                <tr>
                  <th class="text-left">Area</th>
                  <th class="text-center" title="Chance">Chance</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="(result, index) in data.areaResults" :title="result.tooltip" :key="index">
                  <td class="text-left">{{ result.name }}</td>
                  <td class="text-center">1:{{ makeRatio(result.chance) }}</td>
                </tr>
              </tbody>
            </table>
          </div>
          <h4 class="text-center" v-else>Calculating: {{ (data.progress * 100).toFixed(0) }}%</h4>
        </div>
        <div class="col-12 col-lg-4">
          <div v-if="!data.calculating">
            <table v-if="data.visible" class="table table-hover table-sm m-0 text-right">
              <thead class="table-primary">
                <tr>
                  <th class="text-left">Monster</th>
                  <th class="text-center" title="Chance">Chance</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="(result, index) in data.packResults" :title="result.tooltip" :key="index">
                  <td class="text-left fw-bold" :style="{color: result.color}">{{ result.name }}</td>
                  <td class="text-center">1:{{ makeRatio(result.chance) }}</td>
                </tr>
              </tbody>
            </table>
          </div>
        </div>
      </div>
    </template>
  </div>
</template>

<style>

</style>
