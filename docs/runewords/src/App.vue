<script setup>
import { reactive, computed } from "vue";

import "../../../objext.js";
import runes from "../../../json/runes.json";
import itemtypes from "../../../json/itemtypes.json";
import items from "../../../json/items.json";
import gems from "../../../json/gems.json";
import skills from "../../../json/skills.json";
import properties from "../../../json/properties.json";
import strings from "../../../json/localestrings-eng.json";
import modOrder from "./modorder.json"; 

itemtypes.pala.ItemType = 'Paladin Shield';
itemtypes.h2h.ItemType = 'Claw';
itemtypes.h2h2.ItemType = 'Claw';
itemtypes.sppl.ItemType = 'Spear or Polearm';
itemtypes.blde.ItemType = 'Sword or Dagger';
itemtypes.rod.ItemType = 'Staff or Rod';

const data = reactive({
  usedRunes: {},
  advanced: false,
  ladder: true,
  search: {
    name: '',
    types: '',
    items: '',
    mods: '',
  },
  sockets: '',
});

function getTypes (types, ret = {}) {
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

function getSubTypes (types, ret = {}) {
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

function intersect (a, b) {
  return a.some(elem => b.includes(elem));
}

function stripHtml (html) {
   let tmp = document.createElement("DIV");
   tmp.innerHTML = html;
   return tmp.textContent || tmp.innerText || "";
}

function escapeRegexp (string) {
    return string.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
}

function sortMods (a, b) {
  return modOrder.indexOf(a.property.code) - modOrder.indexOf(b.property.code);
}

let modFormatters = {
  'skilltab': ({min, max, param}) => {
    let tabname = [
      'Bow & Crossbow Skills (Amazon)',
      'Passive & Magic Skills (Amazon)',
      'Spear & Javelin Skills (Amazon)',
      'Fire Skills (Sorceress)',
      'Lightning Skills (Sorceress)',
      'Cold Skills (Sorceress)',
      'Curses (Necromancer)',
      'Poison & Bone Skills (Necromancer)',
      'Summoning Skills (Necromancer)',
      'Offensive Auras (Paladin)',
      'Combat Skills (Paladin)',
      'Defensive Auras (Paladin)',
      'Masteries (Barbarian)',
      'Combat Skills (Barbarian)',
      'Warcries (Barbarian)',
      'Summoning Skills (Druid)',
      'Shapeshifting Skills (Druid)',
      'Elemental Skills (Druid)',
      'Trap Skills (Assassin)',
      'Shadow Disciplines (Assassin)',
      'Martial Arts (Assassin)',
    ][param];

    return `+${fv(min, max)} to ${tabname}`;
  },
  'res-fire': ({min, max}) => `Fire Resist +${fv(min, max)}%`,
  'res-fire-max': ({min, max}) => `+${fv(min, max)}% to Maximum Fire Resist`,
  'res-ltng': ({min, max}) => `Lightning Resist +${fv(min, max)}%`,
  'res-ltng-max': ({min, max}) => `+${fv(min, max)}% to Maximum Lightning Resist`,
  'res-pois': ({min, max}) => `Poison Resist +${fv(min, max)}%`,
  'res-pois-max': ({min, max}) => `+${fv(min, max)}% to Maximum Poison Resist`,
  'res-cold': ({min, max}) => `Cold Resist +${fv(min, max)}%`,
  'res-cold-max': ({min, max}) => `+${fv(min, max)}% to Maximum Cold Resist`,
  'res-all': ({min, max}) => `All Resistances +${fv(min, max)}%`,
  'str': ({min, max}) => `+${fv(min, max)} to Strength`,
  'str/lvl': ({param}) => `${param/8}-${param/8 * 99}% to Strength (Char Level)`,
  'dex': ({min, max}) => `+${fv(min, max)} to Dexterity`,
  'vit': ({min, max}) => `+${fv(min, max)} to Vitality`,
  'vit/lvl': ({param}) => `${param/8}-${param/8 * 99}% to Vitality (Char Level)`,
  'enr': ({min, max}) => `+${fv(min, max)} to Energy`,
  'all-stats': ({min, max}) => `+${fv(min, max)} to All Attributes`,
  'hp': ({min, max}) => `+${fv(min, max)} to Life`,
  'hp%': ({min, max}) => `Increase Maximum Life ${fv(min, max)}%`,
  'hp/lvl': ({min}) => `${min/8}-${min/8 * 99} to Life (Char Level)`,
  'mana': ({min, max}) => `+${fv(min, max)} to Mana`,
  'mana%': ({min, max}) => `Increase Maximum Mana ${fv(min, max)}%`,
  'mana/lvl': ({param}) => `${param/8}-${param/8 * 99} to Mana (Char Level)`,
  'regen-mana': ({min, max}) => `Regenerate Mana ${fv(min, max)}%`,
  'ac': ({min, max}) => `+${fv(min, max)} Defense`,
  'ac%': ({min, max}) => `+${fv(min, max)}% Enhanced Defense`,
  'ac/lvl': ({min}) => `${min/8}-${min/8 * 99} Defense (Char Level)`,
  'ac-miss': ({min, max}) => `+${fv(min, max)} Defense vs. Missile`,
  'red-dmg': ({min, max}) => `Damage Reduced by ${fv(min, max)}`,
  'red-dmg%': ({min, max}) => `Damage Reduced by ${fv(min, max)}%`,
  'red-mag': ({min, max}) => `Magic Damage Reduced by ${fv(min, max)}`,
  'dmg%': ({min, max}) => `+${fv(min, max)}% Enhanced Damage`,
  'dmg': ({min, max}) => `Damage +${fv(min, max)}`,
  'dmg-demon': ({min, max}) => `+${fv(min, max)}% Damage to Demons`,
  'dmg-dem/lvl': ({param}) => `${param/8}-${param/8 * 99}% Damage to Demons (Char Level)`,
  'dmg-undead': ({min, max}) => `+${fv(min, max)}% Damage to Undead`,
  'dmg-min': ({min, max}) => `+${fv(min, max)} to Minimum Damage`,
  'dmg-max': ({min, max}) => `+${fv(min, max)} to Maximum Damage`,
  'att': ({min, max}) => `+${fv(min, max)} to Attack Rating`,
  'att%': ({min, max}) => `${fv(min, max)}% Bonus to Attack Rating`,
  'att-demon': ({min, max}) => `+${fv(min, max)} to Attack Rating against Demons`,
  'att-undead': ({min, max}) => `+${fv(min, max)} to Attack Rating against Undead`,
  'reduce-ac': ({min, max}) => `-${fv(min, max)}% Target Defense`,
  'dmg-ac': ({min, max}) => `${fv(min, max)} to Monster Defense Per Hit`,
  'dmg-to-mana': ({min, max}) => `${fv(min, max)}% Damage Taken Goes to Mana`,
  'crush': ({min, max}) => `${fv(min, max)}% Chance of Crushing Blow`,
  'openwounds': ({min, max}) => `${fv(min, max)}% Chance of Open Wounds`,
  'deadly': ({min, max}) => `${fv(min, max)}% Deadly Strike`,
  'deadly/lvl': ({param}) => `${param/8}-${param/8 * 99}% Deadly Strike (Char Level)`,
  'freeze': ({min, max}) => `Freezes Target +${fv(min, max)}`,
  'noheal': () => `Prevent Monster Heal`,
  'knock': () => `Knockback`,
  'ignore-ac': () => `Ignore Target's Defense`,
  'indestruct': () => `Indestructible`,
  'ethereal': () => `Ethereal`,
  'nofreeze': () => `Cannot Be Frozen`,
  'half-freeze': () => `Half Freeze Duration`,
  'rip': () => `Slain Monsters Rest in Peace`,
  'stupidity': ({min, max}) => `Hit Blinds Target +${fv(min, max)}`,
  'slow': ({min, max}) => `Slows Target by ${fv(min, max)}%`,
  'howl': ({min, max}) => `Hit Causes Monster to Flee ${fv(min, max)}%`,
  'pierce': ({min, max}) => `Piercing Attack +${fv(min, max)}%`,
  'cast2': ({min, max}) => `+${fv(min, max)}% Faster Cast Rate`,
  'cast3': ({min, max}) => `+${fv(min, max)}% Faster Cast Rate`,
  'swing1': ({min, max}) => `+${fv(min, max)}% Increased Attack Speed`,
  'swing2': ({min, max}) => `+${fv(min, max)}% Increased Attack Speed`,
  'swing3': ({min, max}) => `+${fv(min, max)}% Increased Attack Speed`,
  'block2': ({min, max}) => `+${fv(min, max)}% Faster Block Rate`,
  'balance2': ({min, max}) => `+${fv(min, max)}% Faster Hit Recovery`,
  'balance3': ({min, max}) => `+${fv(min, max)}% Faster Hit Recovery`,
  'regen': ({min, max}) => `Replenish Life +${fv(min, max)}`,
  'heal-kill': ({min, max}) => `+${fv(min, max)} To Life After Each Kill`,
  'demon-heal': ({min, max}) => `+${fv(min, max)} To Life After Each Demon Kill`,
  'lifesteal': ({min, max}) => `+${fv(min, max)}% Life Stolen per Hit`,
  'mana-kill': ({min, max}) => `+${fv(min, max)} To Mana After Each Kill`,
  'manasteal': ({min, max}) => `+${fv(min, max)}% Mana Stolen per Hit`,
  'aura': ({min, max, param}) => `Level ${fv(min, max)} ${fs(param)} Aura When Equipped`,
  'charged': ({min, max, param}) => `Level ${max} ${fs(param)} (${min} Charges)`,
  'oskill': ({min, max, param}) => `+${fv(min, max)} to ${fs(param)}`,
  'hit-skill': ({min, max, param}) => `${min}% Chance to Cast Level ${max} ${fs(param)} on Striking`,
  'att-skill': ({min, max, param}) => `${min}% Chance to Cast Level ${max} ${fs(param)} on Attack`,
  'gethit-skill': ({min, max, param}) => `${min}% Chance to Cast Level ${max} ${fs(param)} when Struck`,
  'kill-skill': ({min, max, param}) => `${min}% Chance to Cast Level ${max} ${fs(param)} When You Kill an Enemy`,
  'death-skill': ({min, max, param}) => `${min}% Chance to Cast Level ${max} ${fs(param)} When You Die`,
  'levelup-skill': ({min, max, param}) => `${min}% Chance to Cast Level ${max} ${fs(param)} When You Level-Up`,
  'skill': ({min, max, param}) => `+${fv(min, max)} to ${fs(param)} (${fsc(param)} only)`,
  'allskills': ({min, max}) => `+${fv(min, max)} to All Skills`,
  'fireskill': ({min, max}) => `+${fv(min, max)} to Fire Skills`,
  'ama': ({min, max}) => `+${fv(min, max)} to Amazon Skills`,
  'nec': ({min, max}) => `+${fv(min, max)} to Necromancer Skills`,
  'sor': ({min, max}) => `+${fv(min, max)} to Sorceress Skills`,
  'bar': ({min, max}) => `+${fv(min, max)} to Barbarian Skills`,
  'pal': ({min, max}) => `+${fv(min, max)} to Paladin Skills`,
  'dru': ({min, max}) => `+${fv(min, max)} to Druid Skills`,
  'ass': ({min, max}) => `+${fv(min, max)} to Assassin Skills`,
  'explosivearrow': ({min, max}) => `Fires Level ${fv(min, max)} Explosive Arrow`,
  'dmg-elem': ({min, max}) => `Adds ${min}-${max} Fire Damage<br>Adds ${min}-${max} Lightning Damage<br>Adds ${min}-${max} Cold Damage`,
  'dmg-fire': ({min, max}) => `Adds ${min}-${max} Fire Damage`,
  'dmg-ltng': ({min, max}) => `Adds ${min}-${max} Lightning Damage`,
  'dmg-cold': ({min, max}) => `Adds ${min}-${max} Cold Damage`,
  'dmg-mag': ({min, max}) => `Adds ${min}-${max} Magic Damage`,
  'dmg-pois': ({min, max, param}) => `Adds ${fv(Math.trunc(min * param / 256), Math.trunc(max * param / 256))} Poison Damage Over ${param/25} Seconds`,
  'extra-fire': ({min, max}) => `+${fv(min, max)}% to Fire Skill Damage`,
  'extra-ltng': ({min, max}) => `+${fv(min, max)}% to Lightning Skill Damage`,
  'extra-cold': ({min, max}) => `+${fv(min, max)}% to Cold Skill Damage`,
  'extra-pois': ({min, max}) => `+${fv(min, max)}% to Poison Skill Damage`,
  'pierce-fire': ({min, max}) => `-${fv(min, max)}% to Enemy Fire Resistance`,
  'pierce-ltng': ({min, max}) => `-${fv(min, max)}% to Enemy Lightning Resistance`,
  'pierce-cold': ({min, max}) => `-${fv(min, max)}% to Enemy Cold Resistance`,
  'pierce-pois': ({min, max}) => `-${fv(min, max)}% to Enemy Poison Resistance`,
  'abs-fire': ({min, max}) => `Fire Absorb ${fv(min, max)}`,
  'abs-ltng': ({min, max}) => `Lightning Absorb ${fv(min, max)}`,
  'abs-cold': ({min, max}) => `Cold Absorb ${fv(min, max)}`,
  'abs-mag': ({min, max}) => `Magic Absorb ${fv(min, max)}`,
  'ease': ({min, max}) => `Requirements ${fv(min, max)}%`,
  'light': ({min, max}) => `+${fv(min, max)} to Light Radius`,
  'mag%': ({min, max}) => `${fv(min, max)}% Better Chance of Finding Magic Items`,
  'mag%/lvl': ({param}) => `${param/8}-${param/8*99}% Better Chance of Finding Magic Items (Char Level)`,
  'gold%': ({min, max}) => `${fv(min, max)}% Extra Gold from Monsters`,
  'gold%/lvl': ({param}) => `${param/8}-${param/8 * 99}% Extra Gold from Monsters (Char Level)`,
  'move2': ({min, max}) => `+${fv(min, max)}% Faster Run/Walk`,
  'move3': ({min, max}) => `+${fv(min, max)}% Faster Run/Walk`,
  'stamdrain': ({min, max}) => `${fv(min, max)}% Slower Stamina Drain`,
  'cheap': ({min, max}) => `Reduces All Vendor Prices ${fv(min, max)}%`,
  'res-pois-len': ({min, max}) => `Poison Length Reduced by ${fv(min, max)}%`,
  'reanimate': ({min, max}) => `${fv(min, max)}% Chance to Reanimate as: Returned`,
  'rep-dur': ({param}) => `Repairs 1 Durability Every ${100/param} Seconds`,
  'thorns': ({min, max}) => `Attacker Takes Damage of ${fv(min, max)}%`,
  'block': ({min, max}) => `${fv(min, max)}% Increased Chance of Blocking`,
  'stam': ({min, max}) => `+${fv(min, max)} Maximum Stamina`,
};

function getModText (mod) {
  if (modFormatters[mod.property.code] && modFormatters[mod.property.code].apply) {
    return `<span>` + modFormatters[mod.property.code](mod) + '</span>';
  }

  return `<span>` + (mod.property['*Tooltip'] || '(no mod formatter)') + '</span>';
}

function combineMods (a, b) {
  if ([
    'oskill',
    'skill',
  ].includes(a.property.code)) {
    if (a.param === b.param) {
      a.min += b.min;
      a.max += b.max;
      return true;
    }

    return false;
  } else if ([
    'dmg',
    'dmg%',
    'ac',
    'ac-miss',
    'ac%',
    'red-dmg',
    'red-mag',
    'res-all',
    'res-fire',
    'res-ltng',
    'res-cold',
    'res-pois',
    'res-fire-max',
    'dmg-undead',
    'dmg-fire',
    'dmg-ltng',
    'dmg-cold',
    'balance1',
    'balance2',
    'balance3',
    'block1',
    'block2',
    'crush',
    'openwounds',
    'att',
    'str',
    'dex',
    'vit',
    'enr',
    'light',
    'lifesteal',
    'manasteal',
    'gold%',
    'mag%',
    'dmg-demon',
  ].includes(a.property.code)) {
    a.min += b.min;
    a.max += b.max;
    return true;
  } else if (a.property.code === 'dmg-pois') {
    a.min += b.min;
    a.max += b.max;
    a.param = (a.param + b.param) / 2;
    return true;
  } else if ([
    'noheal',
    'ignore-ac',
  ].includes(a.property.code)) {
    return true;
  } else if ([
    'hit-skill',
    'gethit-skill',
    'charged',
  ].includes(a.property.code)) {
    return false;
  }

  return false;
}

items.forEach(item => {
  item.types = Object.keys(getTypes(item.type));
});

runes.forEach(runeword => {
  if (!runeword['complete']) {
    return;
  }

  runeword.runes = [];
  runeword.types = [];
  runeword.weaponMods = [];
  runeword.helmMods = [];
  runeword.shieldMods = [];

  for (let c = 0; c < 10; c++) {
    if (runeword['itype' + c]) {
      runeword.types.push(runeword['itype' + c]);
    }
  }

  runeword.subTypes = Object.keys(getSubTypes(runeword.types)).filter(type => !runeword.types.includes(type) && itemtypes[type]['MaxSockets3']);
  runeword.allTypes = [...runeword.types, ...runeword.subTypes];
  runeword.superTypes = Object.keys(getTypes(runeword.types));
  runeword.isWeapon = intersect(runeword.superTypes, ['weap']);
  runeword.isArmor = intersect(runeword.superTypes, ['tors']);
  runeword.isHelm = intersect(runeword.superTypes, ['helm']);
  runeword.isShield = intersect(runeword.superTypes, ['shld', 'pala']);

  if (!runeword.isWeapon && !runeword.isArmor && !runeword.isHelm && !runeword.isShield) {
    debugger;
  }

  for (let c = 0; c < 10; c++) {
    if (runeword['Rune' + c]) {
      let runeName = runeword['Rune' + c];
      runeword.runes.push(runeName);
      data.usedRunes[runeword['Rune' + c]] = data.usedRunes[runeword['Rune' + c]] || false;

      if (gems[runeName]) {
        for (let i = 0; i < 10; i++) {
          if (runeword.isWeapon && gems[runeName]['weaponMod' + i + 'Code']) {
            runeword.weaponMods.push({
              property: properties[gems[runeName]['weaponMod' + i + 'Code']],
              param: gems[runeName]['weaponMod' + i + 'Param'],
              min: gems[runeName]['weaponMod' + i + 'Min'],
              max: gems[runeName]['weaponMod' + i + 'Max'],
            });
          }

          if ((runeword.isArmor || runeword.isHelm) && gems[runeName]['helmMod' + i + 'Code']) {
            runeword.helmMods.push({
              property: properties[gems[runeName]['helmMod' + i + 'Code']],
              param: gems[runeName]['helmMod' + i + 'Param'],
              min: gems[runeName]['helmMod' + i + 'Min'],
              max: gems[runeName]['helmMod' + i + 'Max'],
            });
          }

          if (runeword.isShield && gems[runeName]['shieldMod' + i + 'Code']) {
            runeword.shieldMods.push({
              property: properties[gems[runeName]['shieldMod' + i + 'Code']],
              param: gems[runeName]['shieldMod' + i + 'Param'],
              min: gems[runeName]['shieldMod' + i + 'Min'],
              max: gems[runeName]['shieldMod' + i + 'Max'],
            });
          }
        }
      }
    }

    if (runeword['T1Code' + c]) {
      let mod = {
        property: properties[runeword['T1Code' + c]],
        param: runeword['T1Param' + c],
        min: runeword['T1Min' + c],
        max: runeword['T1Max' + c],
      };

      if (runeword.isWeapon) {
        runeword.weaponMods.push(mod);
      }

      if (runeword.isArmor || runeword.isHelm) {
        runeword.helmMods.push(mod);
      }

      if (runeword.isShield) {
        runeword.shieldMods.push(mod);
      }
    }
  }

  [
    runeword.weaponMods,
    runeword.helmMods,
    runeword.shieldMods,
  ].forEach(mods => {
    let hasResists = mods.some(mod => ['res-fire', 'res-ltng', 'res-cold', 'res-ltng'].includes(mod.property.code));

    if (hasResists) {
      mods.forEach(mod => {
        if (mod.property.code === 'res-all') {
          mod.property = properties['res-fire'];

          mods.push({
            property: properties['res-ltng'],
            param: mod.param,
            min: mod.min,
            max: mod.max,
          });

          mods.push({
            property: properties['res-cold'],
            param: mod.param,
            min: mod.min,
            max: mod.max,
          });

          mods.push({
            property: properties['res-pois'],
            param: mod.param,
            min: mod.min,
            max: mod.max,
          });
        }
      });
    }

    for (let c = 0; c < mods.length; c++) {
      if (mods[c]) {
        for (let d = c + 1; d < mods.length; d++) {
          if (mods[d] && mods[c].property === mods[d].property) {
            if (combineMods(mods[c], mods[d])) {
              mods[d] = null;
            }
          }
        }
      }
    }
  });

  runeword.weaponMods = runeword.weaponMods.filter(Boolean).sort(sortMods);
  runeword.helmMods = runeword.helmMods.filter(Boolean).sort(sortMods);
  runeword.shieldMods = runeword.shieldMods.filter(Boolean).sort(sortMods);


  runeword.validItems = Object.values(items).filter(item => {
    return intersect(runeword.types, item.types) && runeword.runes.length <= item.gemsockets;
  }).sort((a, b) => itemtypes[a.type].lineNumber - itemtypes[b.type].lineNumber || a.level - b.level);

  runeword.modText = {};

  if (runeword.isWeapon) {
    runeword.modText.weapon = runeword.weaponMods.map(getModText).join('<br>');
  }

  if (runeword.isArmor || runeword.isHelm) {
    runeword.modText.helm = runeword.helmMods.map(getModText).join('<br>');
  }

  if (runeword.isShield) {
    runeword.modText.shield = runeword.shieldMods.map(getModText).join('<br>');
  }

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
    mods: Object.values(runeword.modText).map(stripHtml).join(' '),
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

    let sockets = data.sockets.split(/\s+/gi).map(Number).filter(isFinite).filter(v => v > 0);

    if (sockets.length) {
      ret = ret.filter(runeword => sockets.includes(runeword.runes.length));
    }

    if (!data.ladder) {
      ret = ret.filter(runeword => !runeword.server);
    }

    data.search.forEach((text, key) => {
      if (text.length) {
        ret = ret.filter(runeword => {
          let condition = new RegExp('(' + escapeRegexp(text).split(/\s+/gi).map(word => /^(or|and)$/i.test(word) ? ')|(' : '\\b' + word).join('\\s*') + ')', 'gi');
          return condition.test(runeword.search[key]);
        });
      }
    });
  } catch (e) {
    console.error(e);
  }

  return ret;
});

function fv (a, b) {
  return a === b ? `${a}` : `<span class="text-light">${a}</span><span class="magic-mod-light">-</span><span class="text-light">${b}</span>`;
}

function fs (a) {
  if (a != Number(a)) {
    for (let c in skills) {
      if (skills[c].skill === a) {
        a = Number(c);
        break;
      }
    }
  }

  let skillName = strings['skillname' + a] || strings['Skillname' + (a + 1)] || 'Unknown Skill';

  return `${skillName}`;
}

function fsc (a) {
  if (a != Number(a)) {
    return a;
  }

  a = Number(a);

  let className = 'Unknown Class';

  if (a >= 6 && a <= 35) {
    className = 'Amazon';
  } else if (a >= 36 && a <= 65) {
    className = 'Sorceress';
  } else if (a >= 66 && a <= 95) {
    className = 'Necromancer';
  } else if (a >= 96 && a <= 125) {
    className = 'Paladin';
  } else if (a >= 126 && a <= 155) {
    className = 'Barbarian';
  } else if (a >= 221 && a <= 250) {
    className = 'Druid';
  } else if (a >= 251 && a <= 280) {
    className = 'Assassin';
  }

  return `${className}`;
}

</script>

<template>
  <div class="row">
    <div class="col-auto">
      <div>
        <button :class="{
          'btn': true,
          'btn-outline-success': !data.advanced,
          'btn-outline-secondary': data.advanced,
          'mb-2': true,
          'px-1': true,
        }" style="width:4.25em" @click="data.advanced = !data.advanced">Basic</button>
      </div>
      <div>
        <button :class="{
          'btn': true,
          'btn-outline-success': data.ladder,
          'btn-outline-secondary': !data.ladder,
          'mb-2': true,
          'px-1': true,
        }" style="width:4.25em" @click="data.ladder = !data.ladder">Ladder</button>
      </div>
      <label class="form-label text-center d-block"><strong>Runes<br>Used</strong></label>
      <div v-for="rune in Object.keys(data.usedRunes).sort().reverse()" :key="rune" class="my-1 avquest">
        <button :class="{
          'btn': true,
          'btn-outline-warning': data.usedRunes[rune],
          'btn-outline-secondary': !data.usedRunes[rune],
          'fw-bold': true,
        }" style="width:4.25em" @click="() => {
          data.usedRunes[rune] = !data.usedRunes[rune];
        }" @focus="e => e.target.blur()">{{ strings[rune + 'L'] }}</button>
      </div>
    </div>
    <div class="col">
      <div class="row">
        <div :class="data.advanced ? 'col-12' : 'col'">
          <input type="search" class="form-control bg-secondary" placeholder="Search a runeword name..." v-model="data.search.name">
        </div>
        <div v-if="data.advanced" class="col-12 col-lg mt-3">
          <input type="search" class="form-control bg-secondary" placeholder="Search an item type..." v-model="data.search.types">
        </div>
        <div v-if="data.advanced" class="col-12 col-lg mt-3">
          <input type="search" class="form-control bg-secondary" placeholder="Search a base item..." v-model="data.search.items">
        </div>
        <div v-if="data.advanced" class="col-12 col-lg mt-3">
          <input type="search" class="form-control bg-secondary" placeholder="Search an item modifier..." v-model="data.search.mods">
        </div>
        <div v-if="data.advanced" class="col-12 col-lg-auto mt-3">
          <input type="search" class="form-control bg-secondary" placeholder="Sockets..." v-model="data.sockets">
        </div>
      </div>
      <div class="row">
        <div v-for="runeword in runewords" :key="runeword.Name" class="col-12 col-lg-6 col-xl-4 col-xxl-3 text-center px-2 pt-3 runeword-display">
          <div class="border border-secondary rounded h-100 p-1 position-relative">
            <div><span class="unique-title">{{ runeword['*Rune Name'] }}</span></div>
            <div v-if="runeword.server" class="ladder-tag">Ladder<br>Only</div>
            <div class="rune-list">{{ runeword.runes.map(rune => strings[rune + 'L']).join(' ') }}</div>
            <div class="item-type-list mt-2">
              <template v-for="(type, index) in runeword.types"><template v-if="index">, </template>{{ itemtypes[type].ItemType }}</template>
            </div>
            <div class="magic-mod">
              <div v-if="runeword.isWeapon" class="mt-2">
                <div class="header" v-if="runeword.isHelm || runeword.isArmor || runeword.isShield">For Weapons</div>
                <div v-html="runeword.modText.weapon" />
              </div>
              <div v-if="runeword.isArmor" class="mt-2">
                <div class="header" v-if="runeword.isHelm || runeword.isWeapon || runeword.isShield">For Armor</div>
                <div v-html="runeword.modText.helm" />
              </div>
              <div v-if="runeword.isHelm" class="mt-2">
                <div class="header" v-if="runeword.isWeapon || runeword.isArmor || runeword.isShield">For Helms</div>
                <div v-html="runeword.modText.helm" />
              </div>
              <div v-if="runeword.isShield" class="mt-2">
                <div class="header" v-if="runeword.isHelm || runeword.isArmor || runeword.isWeapon">For Shields</div>
                <div v-html="runeword.modText.shield" />
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style>
  @import "https://blizzhackers.github.io/d2data/css/d2font.css";
  @import url('https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap');

  body {
    font-family: 'Roboto', sans-serif;
  }

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
  
  .runeword-display {
    line-height: 1.25;
  }

  .unique-title {
    color: hsl(51, 24%, 51%);
    font-family: 'AvQuest';
    font-size: 1.25em;
    font-weight: 700;
    letter-spacing: 1px;
  }
  
  .rune-list {
    color: hsl(45, 100%, 45%);
    font-family: 'AvQuest';
    font-size: 1.1em;
    font-weight: 700;
    letter-spacing: 1px;
  }

  .item-type-list {
    color: hsl(0, 0%, 76%);
    font-size: 1.1em;
    letter-spacing: 1px;
  }

  .magic-mod {
    color: hsl(216, 100%, 66%);
  }

  .magic-mod-light {
    color: hsl(290, 100%, 50%);
  }

  .magic-mod .header{
    color: hsl(216, 98%, 82%);
  }

  .ladder-tag {
    position: absolute;
    top: 0.5em;
    left: 0.75em;
    font-size: 0.69em;
    color: hsl(0, 0%, 76%);
  }

</style>
