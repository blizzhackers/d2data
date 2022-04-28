/**
 * Compile script for the json data. Basically, put all your txt files into
 * the txt/ directory, and this will compile it all into json. It assumes that
 * you've provided at least 'armor.txt', 'weapons.txt', 'TreasureClassEx.txt',
 * 'ItemTypes.txt', and 'monstats.txt'.
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
const rollingCalc = false;

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
	hitclass: 'Code',
	inventory: 'class',
	itemstatcost: 'Stat',
	itemtypes: 'Code',
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
	monstats: '*hcIdx',
	monstats2: '*hcIdx',
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
	soundenviron: 'Index',
	sounds: '*Index',
	states: 'state',
	storepage: 'Code',
	superuniques: 'hcIdx',
	treasureclassex: 'Treasure Class',
	uniqueitems: '*ID',
	weapons: 'code',
	weaponclass: 'Code',
};

const filterValues = {
	'': true,
	'0': true,
	'unused': true,
	'none': true,
	'null': true,
};

function noDrop(e, nd, ...d) {
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
						if (obj[key]) {
							throw new Error('Duplicate key ' + JSON.stringify(key) + ' in ' + fn);
						} else {
							let tmp = {};

							for (let c = 0; c < header.length; c++) {
								if (indexColumn >= 0 && c === indexColumn || !filterValues[line[c].toString().toLowerCase()]) {
									tmp[header[c] || 'unknown'] = +line[c] == line[c] ? +line[c] : line[c];
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
			let precalc = {};

			if (tc.Picks > 0) {
				let basetotal = 0;

				for (let c = 1; c <= 9; c++) {
					basetotal += tc['Prob' + c] | 0;
				}
	
				[1, 2, 3, 4, 5, 6, 7, 8].forEach(exp => {
					let nodrop = noDrop(exp, tc.NoDrop, basetotal);
	
					total = basetotal + nodrop;

					if (rollingCalc) {
						let otherChance = 1 - (nodrop / total);
		
						for (let i = 0; i < 100 && otherChance > 1e-30; i++) {
							for (let c = 1; c <= 9; c++) {
								if (tc['Item' + c]) {
									let prob = otherChance * (tc['Prob' + c] | 0) / total; 
									otherChance = Math.max(0, otherChance - (tc['Prob' + c] | 0) / total);
									precalc[exp] = precalc[exp] || {};
									precalc[exp][tc['Item' + c]] = precalc[exp][tc['Item' + c]] || 0;
									precalc[exp][tc['Item' + c]] += prob;
								}
							}
						}	
					} else {
						for (let c = 1; c <= 9; c++) {
							if (tc['Item' + c]) {
								let prob = (tc['Prob' + c] | 0) / total; 
								precalc[exp] = precalc[exp] || {};
								precalc[exp][tc['Item' + c]] = precalc[exp][tc['Item' + c]] || 0;
								precalc[exp][tc['Item' + c]] += prob;
							}
						}	
					}		
				});					
			}

			tc.precalc = precalc;
		});
	}

	if (fn === 'superuniques') {
		full[fn][0].areaId = 3;
		full[fn][1].areaId = 18;
		full[fn][2].areaId = 9;
		full[fn][3].areaId = 4;
		full[fn][4].areaId = 5;
		full[fn][5].areaId = 38;
		full[fn][6].areaId = 25;
		full[fn][7].areaId = 30;
		full[fn][9].areaId = 33;
		full[fn][10].areaId = 49;
		full[fn][11].areaId = 60;
		full[fn][12].areaId = 61;
		full[fn][13].areaId = 43;
		full[fn][14].areaId = 59;
		full[fn][15].areaId = 64;
		full[fn][16].areaId = 54;
		full[fn][17].areaId = 44;
		full[fn][18].areaId = 74;
		full[fn][20].areaId = 28;
		full[fn][21].areaId = 85;
		full[fn][22].areaId = 91;
		full[fn][23].areaId = 78;
		full[fn][24].areaId = 94;
		full[fn][25].areaId = 92;
		full[fn][26].areaId = 83;
		full[fn][27].areaId = 83;
		full[fn][28].areaId = 102;
		full[fn][29].areaId = 83;
		full[fn][30].areaId = 102;
		full[fn][31].areaId = 102;
		full[fn][36].areaId = 108;
		full[fn][37].areaId = 108;
		full[fn][38].areaId = 108;
		full[fn][39].areaId = 39;
		full[fn][40].areaId = 8;
		full[fn][41].areaId = 107;
		full[fn][42].areaId = 110;
		full[fn][43].areaId = 120;
		full[fn][44].areaId = 120;
		full[fn][45].areaId = 120;
		full[fn][47].areaId = 115;
		full[fn][48].areaId = 110;
		full[fn][49].areaId = 111;
		full[fn][50].areaId = 111;
		full[fn][51].areaId = 112;
		full[fn][52].areaId = 121;
		full[fn][53].areaId = 119;
		full[fn][56].areaId = 111;
		full[fn][59].areaId = 114;
		full[fn][60].areaId = 124;
		full[fn][61].areaId = 131;
		full[fn][62].areaId = 131;
		full[fn][63].areaId = 131;
		full[fn][64].areaId = 131;
		full[fn][65].areaId = 131;
	}

	if (fn === 'monstats') {
		full[fn][156].areaId = 37;
		full[fn][211].areaId = 73;
		full[fn][242].areaId = 102;
		full[fn][243].areaId = 108;
		full[fn][544].areaId = 132;
		full[fn][704].areaId = 136;
		full[fn][705].areaId = 136;
		full[fn][706].areaId = 135;
		full[fn][707].areaId = 133;
		full[fn][708].areaId = 134;
		full[fn][709].areaId = 136;
	}
});

files.forEach(fn => {
	fs.writeFileSync(outDir + fn + '.json', JSON.stringify(keySort(full[fn]), null, ' '));
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
		if (full.itemtypes[itemType]) {
			if (full.itemtypes[itemType].TreasureClass) {
				atomicTypes[itemType] = true;
				atomic[itemType + tc] = atomic[itemType + tc] || {};
				atomic[itemType + tc][item.code] = item.code;		
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

for (let c = 3; c <= 87; c += 3) {
	atomicTypes.forEach(type => {
		atomic[type + c] = atomic[type + c] || {};
	});
}

atomic.forEach((atom, atomName) => {
	let precalc = {}, total = 0, otherChance = 1;

	atom = atom.map(itc => {
		let rarity = full.itemtypes[items[itc].type].Rarity | 0;
		total += rarity;
		return rarity;
	}).map(chance => chance / total);

	atom.forEach((chance, itc) => {
		precalc[itc] = chance;
	});

	/* rolling computation
	for (let i = 0; i < 100 && otherChance > 1e-30; i++) {
		atom.forEach((chance, itc) => {
			let prob = otherChance * chance;
			otherChance *= 1 - chance;
			precalc[itc] = precalc[itc] || 0;
			precalc[itc] += prob;
		});
	}
	*/

	precalc.forEach((chance, itc) => {
		atomic[atomName][itc] = chance;
	});
});

full.atomic = atomic;
fs.writeFileSync(outDir + 'atomic.json', JSON.stringify(keySort(atomic), null, ' '));

const tcKey = [
	'TreasureClass1',
	'TreasureClass2',
	'TreasureClass3',
];

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

fs.writeFileSync(outDir + 'treasureclassgroupsex.json', JSON.stringify(groupsEx, null, ' '));
