/**
 * Compile script for the json data. Basically, put all your txt files into
 * the txt/ directory, and this will compile it all into json. It assumes that
 * you've provided at least 'armor.txt' and 'weapons.txt'.
 * 
 * @todo Refactor it, since I hacked it together fairly quickly.
 */

const fs = require('fs');
const lineEnd = /[\n\r]+/g, fieldEnd = /\t/g, full = {};
const inDir = 'txt/';
const outDir = 'json/';
const files = fs.readdirSync(inDir).filter(fn => fn.slice(-4) === '.txt').map(fn => fn.slice(0, -4));

const indexes = {
    armor: 'code',
    charstats: 'class',
    difficultylevels: 'Name',
    experience: 'Level',
    inventory: 'class',
    ItemStatCost: 'Stat',
    ItemTypes: 'Code',
    Levels: 'Id',
    LvlMaze: 'Level',
    LvlPrest: 'Def',
    LvlTypes: 'Id',
    misc: 'code',
    Missiles: 'Id',
    MonMode: 'code',
    monstats: 'hcIdx',
    npc: 'npc',
    Overlay: 'overlay',
    PlrMode: 'Code',
    Properties: 'code',
    Runes: 'Rune Name',
    SetItems: 'index',
    shrines: 'Code',
    skills: 'Id',
    SoundEnviron: 'Index',
    Sounds: 'Index',
    states: 'state',
    SuperUniques: 'hcIdx',
    TreasureClassEx: 'Treasure Class',
    weapons: 'code',
    UniqueItems: 'index',
};

files.forEach(fn => {
    let data = fs.readFileSync(inDir + fn + '.txt').toString().split(lineEnd).filter(line => line.trim().toLowerCase() !== 'expansion');
    let header = data.shift().split(fieldEnd);
    let indexColumn = header.indexOf(indexes[fn]);
    full[fn] = data.reduce((obj, line, index) => {
        if (line.trim() && (line = line.split(fieldEnd))) {
            let key = indexColumn >= 0 ? (line[indexColumn]) : index;
            obj[key] = {};
            for (let c = 0; c < header.length; c++) {
                obj[key][header[c] || 'unknown'] = line[c];
            }
        }

        return obj;
    }, {});

    fs.writeFileSync(outDir + fn + '.json', JSON.stringify(full[fn], null, ' '));
});

// @TODO: Generate atomic classes
let atomic = {};
let calcTC = x => Math.min(87, Math.max(1, Math.ceil(x/3))*3);
let typeRarity = {
    'abow': 1,
    'ajav': 1,
    'aspe': 1,
    'orb': 1,
    'scep': 1,
    'staf': 1,
    'wand': 1,
    'ashd': 1,
    'head': 1,
    'pelt': 1,
    'phlm': 1,
    'h2h': 2,
    'h2h2': 2,
    'default': 3,
};

Object.values(full['weapons']).forEach(item => {
    let tc = calcTC(item.level), rarity = typeRarity[item.type] || typeRarity.default;
    atomic['weap' + tc] = atomic['weap' + tc] || {};
    atomic['weap' + tc][item.code] = rarity;

    if (item.type === 'bow' || item.type === "xbow") {
        atomic['bow' + tc] = atomic['bow' + tc] || {};
        atomic['bow' + tc][item.code] = rarity;
    } else if (tc <= 39) {
        atomic['mele' + tc] = atomic['mele' + tc] || {};
        atomic['mele' + tc][item.code] = rarity;
    }
});

Object.values(full['armor']).forEach(item => {
    let tc = calcTC(item.level);
    atomic['armo' + tc] = atomic['armo' + tc] || {};
    atomic['armo' + tc][item.code] = typeRarity[item.type] || typeRarity.default;;
});

full['atomic'] = atomic;
fs.writeFileSync(outDir + 'atomic.json', JSON.stringify(atomic, null, ' '));

delete full['Sounds'];
delete full['Missiles'];
delete full['objects'];
delete full['LvlPrest'];
delete full['inventory'];
delete full['ItemStatCost'];
delete full['ItemTypes'];
delete full['MonMode'];
delete full['Overlay'];
delete full['PlrMode'];
delete full['SoundEnviron'];
delete full['states'];
delete full['UniqueAppellation'];
delete full['UniquePrefix'];
delete full['UniqueSuffix'];
delete full['UniqueUniqueTitle'];

fs.writeFileSync(outDir + 'aggregate.json', JSON.stringify(full));
