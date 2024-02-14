/**
 * Compile script for the json data. Basically, put all your txt files into
 * the txt/ directory, and this will compile it all into json. It assumes that
 * you've provided at least 'armor.txt', 'weapons.txt', 'TreasureClassEx.txt',
 * 'ItemTypes.txt', and 'monstats.txt'.
 *
 * @todo Refactor it, since I hacked it together fairly quickly.
 */

require('./objext.js');
const fs = require('fs');
const lineEnd = /[\n\r]+/g, fieldEnd = /\t/g, full = {};
const inDir = 'txt/';
const outDir = 'json/';
const files = fs.readdirSync(inDir).filter(fn => fn.slice(-4) === '.txt').map(fn => fn.slice(0, -4));

function keySort(obj) {
  let keys = Object.keys(obj).sort(), ret = {};

  keys.forEach(key => {
    ret[key] = obj[key];
  });

  return ret;
}

const indexes = {
  actinfo: 'act',
  armor: 'code',
  armtype: 'Token',
  bodylocs: 'Code',
  books: 'Name',
  charstats: 'class',
  colors: 'Code',
  compcode: 'code',
  composit: 'Name',
  cubemod: 'Code',
  difficultylevels: 'Name',
  elemtypes: 'Code',
  experience: 'Level',
  events: 'event',
  gems: 'code',
  hirelingdesc: 'id',
  hitclass: 'Code',
  inventory: 'class',
  itemstatcost: 'Stat',
  itemtypes: 'Code',
  levelgroups: 'Name',
  levels: 'Id',
  lvlmaze: 'Level',
  lvlprest: 'Def',
  lvltypes: 'Name',
  misc: 'code',
  misscalc: 'code',
  missiles: 'Missile',
  monai: 'AI',
  monmode: 'code',
  monprop: 'Id',
  monstats: 'Id',
  monstats2: 'Id',
  monsounds: 'Id',
  montype: 'type',
  monumod: 'id',
  npc: 'npc',
  objmode: 'Token',
  overlay: 'overlay',
  pettype: 'pet type',
  plrmode: 'Code',
  plrtype: 'Token',
  playerclass: 'Code',
  properties: 'code',
  runes: '*Rune Name',
  setitems: 'index',
  sets: 'index',
  shrines: 'Code',
  skillcalc: 'code',
  skilldesc: 'code',
  skills: '*Id',
  soundenviron: 'Handle',
  sounds: '*Index',
  states: 'state',
  storepage: 'Code',
  superuniques: 'Superunique',
  treasureclassex: 'Treasure Class',
  uniqueitems: '*ID',
  weapons: 'code',
  weaponclass: 'Code',
};

const filterValues = {
  '': true,
  'unused': true,
  'none': true,
  'null': true,
};

function noDrop(e, nd, ...d) {
  if (e <= 1) {
    return nd | 0;
  }

  e = e | 0;
  nd = nd | 0;
  d = d.reduce((t, v) => t + v | 0, 0);

  if (d < 1) {
      return Infinity;
  }

  return (d / (((nd + d) / nd)**e - 1)) | 0;
}

files.forEach(fn => {
  let data = fs.readFileSync(inDir + fn + '.txt').toString().split(lineEnd);
  let header = data.shift().split(fieldEnd);
  let indexColumn = header.indexOf(indexes[fn]);
  let usesVersion = header.includes('version');
  let expansion = false;
  let maxKeyCount = 0;

  if (indexColumn === -1) {
    console.log('Using default Index for:', fn);
  }

  full[fn] = data.reduce((obj, line, index) => {
    if (line.trim()) {
      line = line.split(fieldEnd).map(v => v.trim());

      if (line[0].toLowerCase() === 'expansion') {
        expansion = true;
      } else if (header.length === 1 || line.filter(Boolean).length > 1) {
        let key = indexColumn >= 0 ? (line[indexColumn]) : index;

        if (key !== undefined) {
          if (key !== '') {
            while (obj[key]) {
              console.warn('Duplicate key ' + JSON.stringify(key) + ' in ' + fn);
              key += ' [dup]';
            }

            {
              let tmp = {};

              for (let c = 0; c < header.length; c++) {
                if (indexColumn >= 0 && c === indexColumn || !filterValues[line[c].toString().toLowerCase()]) {
                  tmp[header[c] || 'unknown'] = line[c] !== 'Infinity' && Number(line[c]).toString() === line[c].trim() ? Number(line[c]) : line[c];
                }
              }

              let keyCount = Object.keys(tmp).length;

              if (keyCount > 0) {
                if (usesVersion) {
                  if (tmp.version >= 100) {
                    tmp.expansion = 1;
                  }
                } else if (expansion) {
                  tmp.expansion = 1;
                }

                obj[key] = tmp;

                delete obj[key]['*eol'];
                delete obj[key]['*EOL'];
                delete obj[key]['eol'];
                delete obj[key]['EOL'];

                if (indexColumn >= 0) {
                  obj[key].lineNumber = index;
                }
              }

              maxKeyCount = Math.max(maxKeyCount, keyCount);
            }
          }
        } else {
          throw new Error('No viable key in: ' + fn + ' : ' + key);
        }
      }
    }

    return obj;
  }, {});

  if (maxKeyCount === 1) {
    full[fn] = Object.values(full[fn]).map(line => Object.values(line)[0]);
    console.log(fn, 'was reduced!');
  }

  if (fn === 'treasureclassex') {
    full[fn].forEach(tc => {
      let precalc = {}, nodropcalc = {
        1: 0,
        2: 0,
        3: 0,
        4: 0,
        5: 0,
        6: 0,
        7: 0,
        8: 0,
      };

      if (tc.Picks > 0) {
        let total = 0;

        for (let c = 1; c <= 9; c++) {
          if (tc['Item' + c]) {
            total += tc['Prob' + c] | 0;
          }
        }

        [1, 2, 3, 4, 5, 6, 7, 8].forEach(exp => {
          nodropcalc[exp] = noDrop(exp, tc.NoDrop, total);
        });

        for (let c = 1; c <= 9; c++) {
          if (tc['Item' + c]) {
            let prob = (tc['Prob' + c] | 0) / total;
            precalc[tc['Item' + c]] = precalc[tc['Item' + c]] || 0;
            precalc[tc['Item' + c]] += prob;
          }
        }

        precalc = precalc.map(v => v * tc.Picks);
        tc['*ItemProbTotal'] = total;
      }
      else if (tc.Picks < 0) {
        let picksleft = -tc.Picks;

        for (let c = 1; c <= 9; c++) {
          if (tc['Item' + c] && picksleft > 0) {
            let pickcount = Math.min(picksleft, tc['Prob' + c] | 0);

            if (pickcount > 0) {
              precalc[tc['Item' + c]] = precalc[tc['Item' + c]] || 0;
              precalc[tc['Item' + c]] += pickcount;
              picksleft -= pickcount;
            }
          }
        }
      }

      tc.nodropcalc = nodropcalc;
      tc.precalc = precalc;
    });
  }

  if (fn === 'superuniques') {
    full[fn]['Bishibosh'].areaId = 3;
    full[fn]['Bonebreak'].areaId = 18;
    full[fn]['Coldcrow'].areaId = 9;
    full[fn]['Rakanishu'].areaId = 4;
    full[fn]['Treehead WoodFist'].areaId = 5;
    full[fn]['Griswold'].areaId = 38;
    full[fn]['The Countess'].areaId = 25;
    full[fn]['Pitspawn Fouldog'].areaId = 30;
    full[fn]['Boneash'].areaId = 33;
    full[fn]['Radament'].areaId = 49;
    full[fn]['Bloodwitch the Wild'].areaId = 60;
    full[fn]['Fangskin'].areaId = 61;
    full[fn]['Beetleburst'].areaId = 43;
    full[fn]['Leatherarm'].areaId = 59;
    full[fn]['Coldworm the Burrower'].areaId = 64;
    full[fn]['Fire Eye'].areaId = 54;
    full[fn]['Dark Elder'].areaId = 44;
    full[fn]['The Summoner'].areaId = 74;
    full[fn]['The Smith'].areaId = 28;
    full[fn]['Web Mage the Burning'].areaId = 85;
    full[fn]['Witch Doctor Endugu'].areaId = 91;
    full[fn]['Stormtree'].areaId = 78;
    full[fn]['Sarina the Battlemaid'].areaId = 94;
    full[fn]['Icehawk Riftwing'].areaId = 92;
    full[fn]['Ismail Vilehand'].areaId = 83;
    full[fn]['Geleb Flamefinger'].areaId = 83;
    full[fn]['Bremm Sparkfist'].areaId = 102;
    full[fn]['Toorc Icefist'].areaId = 83;
    full[fn]['Wyand Voidfinger'].areaId = 102;
    full[fn]['Maffer Dragonhand'].areaId = 102;
    full[fn]['Infector of Souls'].areaId = 108;
    full[fn]['Lord De Seis'].areaId = 108;
    full[fn]['Grand Vizier of Chaos'].areaId = 108;
    full[fn]['The Cow King'].areaId = 39;
    full[fn]['Corpsefire'].areaId = 8;
    full[fn]['The Feature Creep'].areaId = 107;
    full[fn]['Siege Boss'].areaId = 110;
    full[fn]['Ancient Barbarian 1'].areaId = 120;
    full[fn]['Ancient Barbarian 2'].areaId = 120;
    full[fn]['Ancient Barbarian 3'].areaId = 120;
    full[fn]['Bonesaw Breaker'].areaId = 115;
    full[fn]['Dac Farren'].areaId = 110;
    full[fn]['Megaflow Rectifier'].areaId = 111;
    full[fn]['Eyeback Unleashed'].areaId = 111;
    full[fn]['Threash Socket'].areaId = 112;
    full[fn]['Pindleskin'].areaId = 121;
    full[fn]['Snapchip Shatter'].areaId = 119;
    full[fn]['Sharp Tooth Sayer'].areaId = 111;
    full[fn]['Frozenstein'].areaId = 114;
    full[fn]['Nihlathak Boss'].areaId = 124;
    full[fn]['Baal Subject 1'].areaId = 131;
    full[fn]['Baal Subject 2'].areaId = 131;
    full[fn]['Baal Subject 3'].areaId = 131;
    full[fn]['Baal Subject 4'].areaId = 131;
    full[fn]['Baal Subject 5'].areaId = 131;
  }

  if (fn === 'monstats') {
    full[fn]['bloodraven'].areaId = 17;
    full[fn]['andariel'].areaId = 37;
    full[fn]['duriel'].areaId = 73;
    full[fn]['mephisto'].areaId = 102;
    full[fn]['diablo'].areaId = 108;
    full[fn]['baalcrab'].areaId = 132;
    full[fn]['ubermephisto'].areaId = 136;
    full[fn]['uberdiablo'].areaId = 136;
    full[fn]['uberizual'].areaId = 135;
    full[fn]['uberandariel'].areaId = 133;
    full[fn]['uberduriel'].areaId = 134;
    full[fn]['uberbaal'].areaId = 136;
  }
});

const items = {};

[
  ...Object.values(full.weapons).sort((a, b) => a.lineNumber - b.lineNumber),
  ...Object.values(full.armor).sort((a, b) => a.lineNumber - b.lineNumber),
  ...Object.values(full.misc).sort((a, b) => a.lineNumber - b.lineNumber),
].forEach((item, classid) => {
  item.classid = classid;
  items[item.code] = item;
});

let atomic = {};
let atomicTypes = {};
let atomicMax = 87;

let calcTC = x => {
  let ret = Math.max(1, Math.ceil((x || 0) / 3)) * 3;
  atomicMax = Math.max(ret, atomicMax);
  return ret;
}

let weaponsarmor = [...Object.values(full.weapons), ...Object.values(full.armor)];

weaponsarmor.forEach(item => {
  if (!item.spawnable) {
    return;
  }

  let tc = calcTC(item.level);

  function handleAtomic(itemType) {
    if (full.itemtypes[itemType] && itemType !== 'tpot') {
      if (full.itemtypes[itemType].TreasureClass) {
        atomicTypes[itemType] = true;
        atomic[itemType + tc] = atomic[itemType + tc] || [];
        atomic[itemType + tc][item.lineNumber] = item.code;
      }

      if (full.itemtypes[itemType].Equiv1) {
        handleAtomic(full.itemtypes[itemType].Equiv1);
      }

      if (full.itemtypes[itemType].Equiv2) {
        handleAtomic(full.itemtypes[itemType].Equiv2);
      }
    }
  }

  handleAtomic(item.type);
});

atomicTypes = Object.keys(atomicTypes);

for (let c = 3; c <= atomicMax; c += 3) {
  atomicTypes.forEach(type => {
    atomic[type + c] = atomic[type + c] || [];
  });
}

atomic.forEach((atom, atomName) => {
  let precalc = {}, total = 0;

  atom.forEach((itc, i) => {
    let rarity = full.itemtypes[items[itc].type].Rarity | 0;
    total += rarity;
    atom[i] = [itc, rarity];
  });

  atom.forEach(([itc, chance]) => {
    precalc[itc] = chance / total;
  });

  atomic[atomName] = precalc;
});

full.atomic = atomic;

let groupsEx = {};

full.treasureclassex.forEach((tc, key) => {
  if (tc.group) {
    groupsEx[tc.group] = groupsEx[tc.group] || [];
    groupsEx[tc.group][tc.level|0] = key;
  }
});

groupsEx = groupsEx.map(group => {
  let length = group.length;
  group = Object.assign({}, group);
  group.length = length;
  return group;
});

function avg(...nums) {
  return nums.reduce((t, v) => t + v, 0) / nums.length || 0;
}

function _s(diff) {
  return (str) => str + ["", "(N)", "(H)"][diff];
}

function monlevel(mon, level, diff) {
  if (!diff) {
    return mon["Level"] || 0;
  }

  let s = _s(diff),
    lvl = level[s("MonLvlEx")] || 0,
    mlvl = mon[s("Level")] || 0;

  return (diff && !mon.boss) ? lvl : mlvl;
}

function forEachMonster(level, diff, func) {
  let s = _s(diff);

  [0, 1, 2].forEach((type) => {
    if (type && !level[s("MonUMin")] && !level[s("MonUMax")]) {
      return;
    }

    let m = (num) => level[(diff ? "nmon" : type ? "umon" : "mon") + num];

    for (let c = 1; c <= 9; c++) {
      if (m(c)) {
        let mon = full.monstats[m(c)];

        if (mon && mon.enabled && mon.killable) {
          let mlvl = monlevel(mon, level, diff) + [0, 2, 3][type];

          func(mon, mlvl, type);
        }
      }
    }
  });
}

const moncountest = require('./json/moncountest.json');

let monpopulation = {};

[0, 1, 2].forEach((diff) => {
  let uniqueCount = 3.5 + diff;
  let champCount = 3;
  let s = _s(diff);
  full.levels.forEach((level) => {
    let l = (key) => level[key] || 0;

    monpopulation[level.Id] = monpopulation[level.Id] || {
      'normal': {},
      'champion': {},
      'unique': {},
      'superunique': {},
      'boss': {},
    };

    if (level.Id) {
      let supers = full.superuniques.filter(s => s.areaId == level.Id || (s.hcIdx === 19 && [66, 67, 68, 69, 70, 71, 72].includes(level.Id | 0))),
        bosses = full.monstats.filter((mon) => mon.areaId == level.Id),
        acount = (moncountest[level.Id] && moncountest[level.Id][diff]) || 0,
        scount = supers.reduce((total, sup) => {
          let mon = full.monstats[sup.Class];

          return (
            total +
            1 +
            diff +
            avg(
              (sup["MinGrp"] || 0),
              (sup["MaxGrp"] || 0)
            ) +
            avg(
              (mon["PartyMin"] || 0),
              (mon["PartyMax"] || 0)
            )
          );
        }, 0),
        bcount = bosses.reduce((total, mon) => {
          return (
            total +
            1 +
            avg(
              (mon["MinGrp"] || 0),
              (mon["MaxGrp"] || 0)
            ) +
            avg(
              (mon["PartyMin"] || 0),
              (mon["PartyMax"] || 0)
            )
          );
        }, 0),
        ucount = avg(l(s("MonUMin")), l(s("MonUMax"))) * 0.2 * uniqueCount,
        ccount = avg(l(s("MonUMin")), l(s("MonUMax"))) * 0.8 * champCount,
        count = acount - ucount - ccount - scount - bcount;

      if (count > 0) {
        let totalpackssize = 0,
          udiv = 0;

        forEachMonster(level, diff, (mon, mlvl, type) => {
          if (!type) {
            let m = (key) => mon[key] || 0;
            let packsize = avg(
              m("PartyMin") + m("PartyMax"),
              m("MinGrp") + m("MaxGrp")
            );

            totalpackssize += packsize;
          }

          if (type === 2) {
            udiv++;
          }
        });

        forEachMonster(level, diff, (mon, mlvl, type) => {
          let mult = [
            count / totalpackssize,
            ccount / champCount / udiv,
            ucount / uniqueCount / udiv,
          ][type];
          monpopulation[level.Id][['normal', 'champion', 'unique'][type]][mon.Id] = monpopulation[level.Id][['normal', 'champion', 'unique'][type]][mon.Id] || {
            "mlvl": 0,
            "packCount": 0,
            "mlvl(N)": 0,
            "packCount(N)": 0,
            "mlvl(H)": 0,
            "packCount(H)": 0,
          };
          monpopulation[level.Id][['normal', 'champion', 'unique'][type]][mon.Id][s('mlvl')] = mlvl;
          monpopulation[level.Id][['normal', 'champion', 'unique'][type]][mon.Id][s('packCount')] = mult;
        });
      }

      supers.forEach((sup) => {
        let mon = full.monstats[sup.Class],
          mlvl = monlevel(mon, level, diff) + 3;

        monpopulation[level.Id]['superunique'][sup.Superunique] = monpopulation[level.Id]['superunique'][sup.Superunique] || {
          "mlvl": 0,
          "packCount": 0,
          "mlvl(N)": 0,
          "packCount(N)": 0,
          "mlvl(H)": 0,
          "packCount(H)": 0,
          "hasStaticLevel": false,
        };

        monpopulation[level.Id]['superunique'][sup.Superunique][s('mlvl')] = mlvl;
        monpopulation[level.Id]['superunique'][sup.Superunique][s('packCount')] = sup.hcIdx === 19 ? 1 / 7 : 1;
        monpopulation[level.Id]['superunique'][sup.Superunique].hasStaticLevel = Boolean(mon.boss);
      });

      bosses.forEach((mon) => {
        let mlvl = monlevel(mon, level, diff);

        monpopulation[level.Id]['boss'][mon.Id] = monpopulation[level.Id]['boss'][mon.Id] || {
          "mlvl": 0,
          "packCount": 0,
          "mlvl(N)": 0,
          "packCount(N)": 0,
          "mlvl(H)": 0,
          "packCount(H)": 0,
          "hasStaticLevel": false,
        };
        monpopulation[level.Id]['boss'][mon.Id][s('mlvl')] = mlvl;
        monpopulation[level.Id]['boss'][mon.Id][s('packCount')] = 1;
        monpopulation[level.Id]['boss'][mon.Id].hasStaticLevel = Boolean(mon.boss);
      });
    }
  });
});

let tcprecalc = {};

full.treasureclassex.forEach((tc, key) => {
  tcprecalc[key] = tcprecalc[key] || {};
  tcprecalc[key].droprate = tc.nodropcalc.map(noDrop => noDrop ? tc['*ItemProbTotal'] / (noDrop + tc['*ItemProbTotal']) : 1);
  tcprecalc[key].droprateRoot = {};
  tcprecalc[key].counts = tc.precalc;
  delete tc['nodropcalc'];
  delete tc['precalc'];
});

atomic.forEach((precalc, key) => {
  tcprecalc[key] = {
    droprate: {
      1: 1,
      2: 1,
      3: 1,
      4: 1,
      5: 1,
      6: 1,
      7: 1,
      8: 1,
    },
    droprateRoot: {},
    counts: precalc,
  };
});

// Formulas and coefficients for the 6 item cap are from https://github.com/realmonster/diablo2_drop_calc
// He did a lot of work figuring out the formulas that I don't care to replicate,
// so I'm taking the path of least resistance.

// Adjust droprates for TCs with 7 picks for the 6 item cap.
tcprecalc.forEach((basetc, basekey) => {
  if (full.treasureclassex[basekey] && full.treasureclassex[basekey].Picks === 7) {
    [1, 2, 3, 4, 5, 6, 7, 8].forEach(playerCount => {
      let newvalue = basetc.droprate[playerCount] * (7 - basetc.droprate[playerCount]**6) / 7;
      basetc.droprateRoot[playerCount] = newvalue;
    });
  } else {
    basetc.droprateRoot = Object.assign({}, basetc.droprate);
  }
});

[
  "Duriel",
  "Duriel Desecrated A",
  "Duriel Desecrated B",
  "Duriel Desecrated C",
  "Duriel (N)",
  "Duriel (N) Desecrated A",
  "Duriel (N) Desecrated B",
  "Duriel (N) Desecrated C",
  "Duriel (H)",
  "Duriel (H) Desecrated A",
  "Duriel (H) Desecrated B",
  "Duriel (H) Desecrated C",
  "Duriel (H) Desecrated D",
  "Durielq",
  "Durielq (N)",
  "Durielq (H)",
].forEach(tcname => {
  for (let c = 1; c < 9; c++) {
    tcprecalc[tcname]['droprateRoot'][c] *= 5 / 11;
  }
});

tcprecalc.forEach(tc => {
  if (tc['counts']['Sunder Charms']) {
    delete tc['counts']['Sunder Charms'];
  }
});

// Flatten and abstract countess rune TCs so we can adjust the drop rate of each via coefficient.
//tcprecalc.forEach((tc, key) => {
  ({
    'Countess Rune': tcprecalc['Countess Rune'],
    'Countess Rune (N)': tcprecalc['Countess Rune (N)'],
    'Countess Rune (H)': tcprecalc['Countess Rune (H)'],
  }).forEach((tc, baseName) => {
    function flattenAndAbstract (tcName, mult = 1, ret = {}) {
      if (tcprecalc[tcName]) {
        tcprecalc[tcName].counts.forEach((submult, subtcName) => {
          flattenAndAbstract(subtcName, mult * submult, ret);
        });
      } else {
        let newtcName = `${baseName} - ${tcName}`;

        if (!tcprecalc[newtcName]) {
          tcprecalc[newtcName] = {
            droprate: {
              1: 1,
              2: 1,
              3: 1,
              4: 1,
              5: 1,
              6: 1,
              7: 1,
              8: 1,
            },
            droprateRoot: {
              1: 1,
              2: 1,
              3: 1,
              4: 1,
              5: 1,
              6: 1,
              7: 1,
              8: 1,
            },
            counts: {
              [tcName]: 1,
            }
          };
        }

        ret[newtcName] = ret[newtcName] || 0;
        ret[newtcName] += mult;
      }

      return ret;
    }

    tc.counts = flattenAndAbstract(baseName);
  });
//});

// Multiply the coefficients to the abstracted TCs
({
  'Countess Rune': {"1":{"0.8412177979895897":["r01"],"0.8412177979895898":["r02"],"0.8279977514350507":["r03"],"0.8279977514350506":["r04"],"0.8238064081864378":["r05","r06","r07","r08"]},"2":{"0.5384142786164905":["r01","r02"],"0.4988295919434789":["r03"],"0.498829591943479":["r04"],"0.4862413242371927":["r05","r08"],"0.48624132423719274":["r06","r07"]},"3":{"0.43127418667153955":["r01","r02"],"0.38274414977638443":["r03","r04"],"0.3673191805912878":["r05","r08"],"0.3673191805912879":["r06","r07"]},"4":{"0.4019832189168574":["r01"],"0.40198321891685734":["r02"],"0.3499170812603648":["r03"],"0.34991708126036486":["r04"],"0.3333333333333333":["r05","r07","r08"],"0.33333333333333337":["r06"]},"5":{"0.4019832189168574":["r01"],"0.40198321891685734":["r02"],"0.3499170812603648":["r03"],"0.34991708126036486":["r04"],"0.3333333333333333":["r05","r07","r08"],"0.33333333333333337":["r06"]},"6":{"0.4019832189168574":["r01"],"0.40198321891685734":["r02"],"0.3499170812603648":["r03"],"0.34991708126036486":["r04"],"0.3333333333333333":["r05","r07","r08"],"0.33333333333333337":["r06"]},"7":{"0.4019832189168574":["r01"],"0.40198321891685734":["r02"],"0.3499170812603648":["r03"],"0.34991708126036486":["r04"],"0.3333333333333333":["r05","r07","r08"],"0.33333333333333337":["r06"]},"8":{"0.4019832189168574":["r01"],"0.40198321891685734":["r02"],"0.3499170812603648":["r03"],"0.34991708126036486":["r04"],"0.3333333333333333":["r05","r07","r08"],"0.33333333333333337":["r06"]}},
  'Countess Rune (N)': {"1":{"0.8256244546455895":["r01","r02","r05","r06","r11","r14","r16"],"0.8256244546455894":["r03","r07","r09","r12","r13","r15"],"0.8256244546455896":["r04","r08","r10"]},"2":{"0.491703901847278":["r01","r06"],"0.4917039018472779":["r02","r03","r07","r09","r12","r15","r16"],"0.49170390184727797":["r04","r05","r08","r10","r11","r13","r14"]},"3":{"0.37401224832526186":["r01","r02","r05","r06","r11","r12","r14","r15","r16"],"0.3740122483252619":["r03","r04","r07","r08","r09","r10","r13"]},"4":{"0.34053127677806344":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r11"],"0.3405312767780634":["r12","r13","r14","r15","r16"]},"5":{"0.34053127677806344":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r11"],"0.3405312767780634":["r12","r13","r14","r15","r16"]},"6":{"0.34053127677806344":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r11"],"0.3405312767780634":["r12","r13","r14","r15","r16"]},"7":{"0.34053127677806344":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r11"],"0.3405312767780634":["r12","r13","r14","r15","r16"]},"8":{"0.34053127677806344":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r11"],"0.3405312767780634":["r12","r13","r14","r15","r16"]}},
  'Countess Rune (H)': {"1":{"0.8219588445252253":["r01","r06"],"0.8219588445252254":["r02","r03","r04","r05","r07","r08","r09","r10","r11","r12","r13","r15","r17","r18","r19","r20","r22","r23","r24"],"0.8219588445252255":["r14","r16","r21"]},"2":{"0.4893751399649079":["r01","r02","r11","r17","r19"],"0.48937513996490795":["r03","r05","r06","r07","r09","r12","r13","r15","r16","r18","r20","r21","r22","r23","r24"],"0.489375139964908":["r04","r08","r10","r14"]},"3":{"0.3733514492176993":["r01","r17"],"0.37335144921769925":["r02","r03","r04","r05","r06","r07","r08","r09","r10","r11","r12","r14","r15","r16","r19","r20","r21","r22","r23","r24"],"0.3733514492176992":["r13","r18"]},"4":{"0.34053976872957364":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r12","r13","r14","r15","r16","r17","r19","r20","r23","r24"],"0.3405397687295737":["r11","r18","r21"],"0.3405397687295736":["r22"]},"5":{"0.34053976872957364":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r12","r13","r14","r15","r16","r17","r19","r20","r23","r24"],"0.3405397687295737":["r11","r18","r21"],"0.3405397687295736":["r22"]},"6":{"0.34053976872957364":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r12","r13","r14","r15","r16","r17","r19","r20","r23","r24"],"0.3405397687295737":["r11","r18","r21"],"0.3405397687295736":["r22"]},"7":{"0.34053976872957364":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r12","r13","r14","r15","r16","r17","r19","r20","r23","r24"],"0.3405397687295737":["r11","r18","r21"],"0.3405397687295736":["r22"]},"8":{"0.34053976872957364":["r01","r02","r03","r04","r05","r06","r07","r08","r09","r10","r12","r13","r14","r15","r16","r17","r19","r20","r23","r24"],"0.3405397687295737":["r11","r18","r21"],"0.3405397687295736":["r22"]}},
}).forEach((data, baseName) => {
  [1, 2, 3, 4, 5, 6, 7, 8].forEach(players => {
    data[players].forEach((runes, value) => {
      value = Number(value);
      runes.forEach(runeName => {
        tcprecalc[baseName + ' - ' + runeName]['droprate'][players] *= value;
      });
    });
  });
});

files.forEach(fn => {
  fs.writeFileSync(outDir + fn + '.json', JSON.stringify(keySort(full[fn]), null, ' '));
});

fs.writeFileSync(outDir + 'items.json', JSON.stringify(items, null, ' '));
fs.writeFileSync(outDir + 'atomic.json', JSON.stringify(keySort(atomic), null, ' '));
fs.writeFileSync(outDir + 'treasureclassgroupsex.json', JSON.stringify(groupsEx, null, ' '));
fs.writeFileSync(outDir + 'monpopulationest.json', JSON.stringify(monpopulation, null, ' '));
fs.writeFileSync(outDir + 'tcprecalc.json', JSON.stringify(tcprecalc, null, ' '));
