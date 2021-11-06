/**
 * Compile script for the json data. Basically, put all your txt files into
 * the txt/ directory, and this will compile it all into json. It assumes that
 * you've provided at least 'armor.txt', 'weapons.txt', 'TreasureClass.txt',
 * 'TreasureClassEx.txt', 'ItemTypes.txt', and 'monstats.txt'.
 *
 * @todo Refactor it, since I hacked it together fairly quickly.
 */

 Object.defineProperty(Object.prototype, 'forEach', {
    value: function (func) {
        Object.keys(this).forEach(key => {
            func(this[key], key, this);
        });
    },
});

Object.defineProperty(Object.prototype, 'map', {
    value: function (func) {
        let ret = {};
    
        Object.keys(this).forEach(key => {
            ret[key] = func(this[key], key, this);
        });
    
        return ret;
    },
});

Object.defineProperty(Object.prototype, 'filter', {
    value: function (func = v => Boolean(v)) {
        let ret = {};
    
        Object.keys(this).forEach(key => {
            if(func.apply && func(this[key], key, this)) {
                ret[key] = this[key];
            }
        });
    
        return ret;
    },
});

Object.defineProperty(Object.prototype, 'toArray', {
    value: function () {
        let ret = [];
    
        for (let key in this) {
            ret.push([key, this[key]]);
        }
    
        return ret;
    },
});

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
	armor: 'code',
	ArmType: 'Token',
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
	monstats2: 'Id',
	MonType: 'type',
	npc: 'npc',
	ObjMode: 'Token',
	Overlay: 'overlay',
	pettype: 'pet type',
	PlrMode: 'Code',
	PlrType: 'Token',
	PlayerClass: 'Code',
	Properties: 'code',
	Runes: 'Rune Name',
	SetItems: 'index',
	Sets: 'index',
	shrines: 'Code',
	skillcalc: 'code',
	skills: 'Id',
	SoundEnviron: 'Index',
	Sounds: 'Index',
	states: 'state',
	StorePage: 'Code',
	SuperUniques: 'hcIdx',
	TreasureClass: 'Treasure Class',
	TreasureClassEx: 'Treasure Class',
	weapons: 'code',
	WeaponClass: 'Code',
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

							if (indexColumn >= 0) {
								obj[key].lineNumber = index;
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

	fs.writeFileSync(outDir + fn + '.json', JSON.stringify(keySort(full[fn]), null, ' '));
});

const monstats = {};

full.monstats.forEach(mon => {
    monstats[mon.Id] = mon;
});

const items = Object.assign(
	full.weapons,
	full.armor,
	full.misc
);

let atomic = {};
let atomicTypes = {};
let calcTC = x => Math.min(87, Math.max(1, Math.ceil((x || 0) / 3)) * 3);

[...Object.values(full.weapons), Object.values(full.armor)].forEach(item => {
	if (!item.spawnable) {
		return;
	}
	let tc = calcTC(item.level);

	function handleAtomic(itemType) {
		if (full.ItemTypes[itemType]) {
			if (full.ItemTypes[itemType].TreasureClass) {
				atomicTypes[itemType] = true;
				atomic[itemType + tc] = atomic[itemType + tc] || {};
				atomic[itemType + tc][item.code] = item.code;		
			}

			if (full.ItemTypes[itemType].Equiv1) {
				handleAtomic(full.ItemTypes[itemType].Equiv1);
			}

			if (full.ItemTypes[itemType].Equiv2) {
				handleAtomic(full.ItemTypes[itemType].Equiv2);
			}
		}
	}

	handleAtomic(item.type);
});

atomicTypes = Object.keys(atomicTypes);

for (let c = 3; c <= 87; c += 3) {
	atomicTypes.forEach(type => {
		atomic[type + c] = atomic[type + c] || {};
	});
}

full.atomic = atomic;
fs.writeFileSync(outDir + 'atomic.json', JSON.stringify(keySort(atomic), null, ' '));

const tcKey = [
	'TreasureClass1',
	'TreasureClass2',
	'TreasureClass3',
];

function noDrop(e, nd, ...d) {
	if (nd < 1) {
		return 0;
	}

	e = 1 + Math.max(0, e);
	d = d.reduce((t, v) => t + v, 0);

	if (d < 1) {
		return Infinity;
	}

	let nr = (nd / (nd + d))**e;
	return Math.round(nr / (1 - nr) * d);
}

function getItemList(name, expansion, mult = 1) {
	name = name.toString();

	let itemlist = (atomic[name] ? Object.keys(atomic[name]) : [name]).filter(v => {
		if (!items[v] || v === 'gld') {
			return false;
		}

		if (!expansion && (items[v].expansion || full.ItemTypes[items[v].type].expansion)) {
			return false;
		}

		return true;
	}),
		total = itemlist.reduce((total, code) => {
			return total + (items[code].type && full.ItemTypes[items[code].type] && full.ItemTypes[items[code].type].Rarity ? full.ItemTypes[items[code].type].Rarity : 1);
		}, 0),
		ret = {};
	
	for(let code of itemlist) {
		ret[code] = mult * full.ItemTypes[items[code].type].Rarity / total;
	}

	return ret;
}

let groupsEx = {}, groupsClassic = {};

full.TreasureClassEx.forEach((tc, key) => {
	if (tc.group) {
		groupsEx[tc.group] = groupsEx[tc.group] || [];
		groupsEx[tc.group][tc.level|0] = key;
	}
});

full.TreasureClass.forEach((tc, key) => {
	if (tc.group) {
		groupsClassic[tc.group] = groupsClassic[tc.group] || [];
		groupsClassic[tc.group][tc.level|0] = key;
	}
});

groupsEx = groupsEx.map(group => {
	let length = group.length;
	group = Object.assign({}, group);
	group.length = length;
	return group;
});

groupsClassic = groupsClassic.map(group => {
	let length = group.length;
	group = Object.assign({}, group);
	group.length = length;
	return group;
});

function _getTcItems(treasureClasses, expansion) {
	function get(name, mult = 1, ret = {}) {
		if (!treasureClasses[name]) {
			getItemList(name, expansion, mult).forEach((chance, itc) => {
				ret[itc] = ret[itc] || 0;
				ret[itc] += chance * mult;
			});

			return ret;
		}

		let total = 0, tc = treasureClasses[name];

		for (let c = 1; c <= 9; c++) {
			total += tc['Prob' + c] | 0;
		}

		total += noDrop(1, tc.NoDrop | 0, total);

		for (let c = 1; c <= 9; c++) {
			if (tc['Item' + c]) {
				get(tc['Item' + c], mult * tc['Prob' + c] / total, ret);
			}
		}

		return ret;
	}

	return get;
};

function _adjustTc (tcs, groups) {
	return function (name, mlvl, lvl, difficulty) {
		mlvl = mlvl | 0;
		lvl = lvl | 0;

		if (difficulty) {
			if (tcs[name].group) {
				let grp = groups[tcs[name].group] || [];
	
				for (let c = lvl; c >= 0; c--) {
					if (grp[c]) {
						return { tcName: grp[c], ilvl: difficulty ? lvl : mlvl };
					}
				}
			}
	
			return { tcName: name, ilvl: difficulty ? lvl : mlvl };
		}

		return { tcName: name, ilvl: mlvl };
	}
}

let _s = diff => str => str + ['', '(N)', '(H)'][diff];

function forEachMonster(level, diff, type, func) {
	let s = _s(diff), prefix = diff ? 'nmon' : type ? 'umon' : 'mon', monsters = {}, minions = {}, total = 0, packCount = [
		Math.max(0, (level[s('SizeX')] || 0) * (level[s('SizeY')] || 0) * (level[s('MonDen')] || 0) / 80000 - (((level[s('MonUMin')] || 0) + (level[s('MonUMax')] || 0)) / 2)),
		((level[s('MonUMin')] || 0) + (level[s('MonUMax')] || 0)) * 0.1,
		((level[s('MonUMin')] || 0) + (level[s('MonUMax')] || 0)) * 0.4,
	][type];

	for (let c = 1; c <= 9; c++) {
		if (level[prefix + c] && monstats[level[prefix + c]].enabled && monstats[level[prefix + c]].killable) {
			let mon = monstats[level[prefix + c]], spawnCount = [
				(mon.MinGrp + mon.MaxGrp) / 2,
				3,
				1,
			][type];

			monsters[mon.Id] = monsters[mon.Id] || 0;
			monsters[mon.Id] += spawnCount;
			total += spawnCount;

			if (type != 1 && (mon.minion1 || mon.minion2)) {
				[
					monstats[mon.minion1 || mon.minion2],
					monstats[mon.minion2 || mon.minion1],
				].forEach(minion => {
					minions[minion.Id] = minions[minion.Id] || 0;
					minions[minion.Id] += type ? 4.5 : ((minion.PartyMin || 0) + (minion.PartyMax || 0)) / 4;
					total += type ? 4.5 : ((minion.PartyMin || 0) + (minion.PartyMax || 0)) / 4;
				});	
			}
		}
	}

	monsters.forEach((spawnCount, monId) => func(monstats[monId], packCount * spawnCount / total, type));
	minions.forEach((spawnCount, monId) => func(monstats[monId], packCount * spawnCount / total, 0));
}

function forEachPick(tc, func) {
	let picklist = {};

	if (tc) {
		if (tc.Picks < 0) {
			let picks = -tc.Picks;
	
			for (let c = 1; picks > 0 && c <= 9; c++) {
				if (tc['Item' + c]) {
					for (let d = 1; picks > 0 && d <= tc['Prob' + c]; d++) {
						picklist[tc['Item' + c]] = picklist[tc['Item' + c]] || 0;
						picklist[tc['Item' + c]] += 1;
						picks--;
					}	
				}
			}
		} else if (tc.Picks > 0) {
			let mult = (1 + tc.Picks) / 2, total = 0;
	
			for (let c = 1; c <= 9; c++) {
				total += tc['Prob' + c] | 0;
			}
	
			total += noDrop(1, tc.NoDrop | 0, total);
	
			for (let c = 1; c <= 9; c++) {
				picklist[tc['Item' + c]] = picklist[tc['Item' + c]] || 0;
				picklist[tc['Item' + c]] += tc['Prob' + c] * mult / total;
			}
		}
	}

	picklist.forEach(func);
}

[
	[true, './json/levelCalcTcEx.json'],
	[false, './json/levelCalcTc.json'],
].forEach(([expansion, filename]) => {
	let getTcItems = _getTcItems(full.TreasureClassEx, expansion);
	let adjustTc = _adjustTc(full.TreasureClassEx, groupsEx);

	let levelCalcTc = [0, 1, 2].map(diff => {
		let s = _s(diff);
	
		return full.Levels.map((level, id) => {
			let drops = {};
	
			if ((!level.expansion || expansion) && (id < 133 || diff === 2)) {
				[0, 1, 2].forEach(type => {
					forEachMonster(level, diff, type, (mon, monCount, monType) => {
						if (mon[s(tcKey[type])]) {
							let lvlOffset = [0, 2, 3][monType];
							let {tcName, ilvl} = adjustTc(mon[s(tcKey[type])], mon[s('Level')] + lvlOffset, level['MonLvl' + (diff + 1) + (expansion ? 'Ex' : '')] + lvlOffset, diff);

							forEachPick(full.TreasureClassEx[tcName], (picks, pickName) => {
								getTcItems(pickName).forEach((chance, itc) => {
									drops[itc + '@' + ilvl] = drops[itc + '@' + ilvl] || 0;
									drops[itc + '@' + ilvl] = 1 - ((1 - drops[itc + '@' + ilvl]) * ((1 - chance)**(monCount * picks)));
									if (!drops[itc + '@' + ilvl]) {
										delete drops[itc + '@' + ilvl];
									}
								});
							});	
						}
					});
				});
			}
	
			return drops;
		}).filter(v => Object.keys(v).length);			
	}).filter(v => Object.keys(v).length);
	
	fs.writeFileSync(filename, JSON.stringify(levelCalcTc, null, ' '));
});

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
delete full.Aiparms;
delete full.Arena;
delete full.ArmType;
delete full.AutoMap;
delete full.belts;
delete full.bodylocs;
delete full.colors;
delete full.compcode;
delete full.Composit;
delete full.cubemod;
delete full.cubetype;
delete full.events;
delete full.gamble;
delete full.hiredesc;
delete full.HitClass;
delete full.lowqualityitems;
delete full.LvlWarp;
delete full.misscalc;
delete full.monai;
delete full.monequip;
delete full.MonItemPercent;
delete full.MonName;
delete full.MonPlace;
delete full.MonPreset;
delete full.MonProp;
delete full.monseq;
delete full.monsounds;
delete full.monstats2;
delete full.monumod;
delete full.objgroup;
delete full.ObjMode;
delete full.ObjType;
delete full.pettype;
delete full.PlrType;
delete full.qualityitems;
delete full.RarePrefix;
delete full.RareSuffix;
delete full.skillcalc;
delete full.skilldesc;
delete full.StorePage
delete full.WeaponClass;

fs.writeFileSync(outDir + 'aggregate.json', JSON.stringify(keySort(full)));
