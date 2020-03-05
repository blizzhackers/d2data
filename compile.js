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
	ElemTypes: 'Code',
	experience: 'Level',
	gems: 'code',
	inventory: 'class',
	ItemStatCost: 'Stat',
	ItemTypes: 'Code',
	Levels: 'Id',
	LvlMaze: 'Level',
	LvlPrest: 'Def',
	LvlTypes: 'Name',
	misc: 'code',
	Missiles: 'Id',
	MonMode: 'code',
	monstats: 'hcIdx',
	MonType: 'type',
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
};

const filterValues = {
	'': true,
	'0': true,
	'unused': true,
	'none': true,
	'null': true,
};

files.forEach(fn => {
	let data = fs.readFileSync(inDir + fn + '.txt').toString().split(lineEnd);
	let header = data.shift().split(fieldEnd);
	let indexColumn = header.indexOf(indexes[fn]);
	let expansion = false;
	let maxKeyCount = 0;

	if (indexColumn === -1) {
		console.log('Using default Index for:', fn);
	}

	full[fn] = data.reduce((obj, line, index) => {

		if (line.trim()) {
			if (line.toLowerCase().trim() === 'expansion') {
				expansion = true;
			} else if ((line = line.split(fieldEnd))) {
				let key = indexColumn >= 0 ? (line[indexColumn]) : index;

				if (key !== undefined) {
					if (key !== '') {
						if (obj[key]) {
							throw new Error('Duplicate key ' + JSON.stringify(key) + ' in ' + fn);
						} else {
							let tmp = expansion ? {expansion: 1} : {};

							for (let c = 0; c < header.length; c++) {
								if (indexColumn >= 0 && c === indexColumn || !filterValues[line[c].toString().toLowerCase()]) {
									tmp[header[c] || 'unknown'] = +line[c] == line[c] ? +line[c] : line[c];
								}
							}

							let keyCount = Object.keys(tmp).length;

							if (keyCount > 0) {
								obj[key] = tmp;
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

	fs.writeFileSync(outDir + fn + '.json', JSON.stringify(full[fn], null, ' '));
});

// @TODO: Generate atomic classes
let atomic = {};
let calcTC = x => Math.min(87, Math.max(1, Math.ceil((x || 0) / 3)) * 3);
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

Object.values(full.weapons).forEach(item => {
	if (item.rarity) {
		let tc = calcTC(item.level), rarity = item.rarity;
		atomic['weap' + tc] = atomic['weap' + tc] || {};
		atomic['weap' + tc][item.code] = rarity;

		if (item.type === 'bow' || item.type === 'xbow') {
			atomic['bow' + tc] = atomic['bow' + tc] || {};
			atomic['bow' + tc][item.code] = rarity;
		} else {
			atomic['mele' + tc] = atomic['mele' + tc] || {};
			atomic['mele' + tc][item.code] = rarity;
		}
	}
});

Object.values(full.armor).forEach(item => {
	if (item.rarity) {
		let tc = calcTC(item.level);
		atomic['armo' + tc] = atomic['armo' + tc] || {};
		atomic['armo' + tc][item.code] = item.rarity || 0;
	}
});

full.atomic = atomic;
fs.writeFileSync(outDir + 'atomic.json', JSON.stringify(atomic, null, ' '));

delete full.Sounds;
delete full.Missiles;
delete full.objects;
delete full.LvlPrest;
delete full.inventory;
delete full.ItemStatCost;
delete full.ItemTypes;
delete full.MonMode;
delete full.Overlay;
delete full.PlrMode;
delete full.SoundEnviron;
delete full.states;
delete full.UniqueAppellation;
delete full.UniquePrefix;
delete full.UniqueSuffix;
delete full.UniqueUniqueTitle;

fs.writeFileSync(outDir + 'aggregate.json', JSON.stringify(full));
