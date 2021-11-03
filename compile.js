/**
 * Compile script for the json data. Basically, put all your txt files into
 * the txt/ directory, and this will compile it all into json. It assumes that
 * you've provided at least 'armor.txt', 'weapons.txt', 'TreasureClass.txt',
 * 'TreasureClassEx.txt', and 'ItemTypes.txt'.
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

[
    [full.TreasureClass, './json/CalcTc.json', './json/TreasureClassGroups.json', './json/levelCalcTc.json', false],
    [full.TreasureClassEx, './json/CalcTcEx.json', './json/TreasureClassExGroups.json', './json/levelCalcTcEx.json', true],
].forEach(([treasureClass, destinationFile, groupsFile, levelCalcFile, expansion]) => {
	let groups = {};

	treasureClass.forEach((tc, key) => {
		if (tc.group) {
			groups[tc.group] = groups[tc.group] || [];
			groups[tc.group][tc.level|0] = key;
		}
	});

	groups = groups.map(group => {
		let length = group.length;
		group = Object.assign({}, group);
		group.length = length;
		return group;
	});

	if (Object.values(groups).length) {
		fs.writeFileSync(groupsFile, JSON.stringify(groups, null, ' '));
	}
        
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
    
    function getItemList(name, mult = 1) {
        name = name.toString();
    
        let itemlist = (atomic[name] ? Object.keys(atomic[name]) : [name]).filter(v => items[v] && v !== 'gld'),
            total = itemlist.reduce((total, code) => {
                return total + (items[code].type && full.ItemTypes[items[code].type] && full.ItemTypes[items[code].type].Rarity ? full.ItemTypes[items[code].type].Rarity : 1);
            }, 0),
            ret = {};
        
        for(let code of itemlist) {
            ret[code] = mult * full.ItemTypes[items[code].type].Rarity / total;
        }
    
        return ret;
    }
    
    function forEachTCItem(tc, func) {
        for (let c = 1; c <= 9; c++) {
            if (tc['Item' + c]){
                let ret = func(tc['Item' + c], tc['Prob' + c] | 0);
    
                if (ret !== undefined && !ret) {
                    return;
                }
            }
        }
    }
    
    function getTC(name, mult = 1) {
        if (treasureClass[name]) {
            let total = 0, ret = {};
    
            for (let c = 1; c <= 9; c++) {
                total += treasureClass[name]['Prob' + c] | 0;
            }
    
            let picks = Math.abs(treasureClass[name].Picks | 0);
    
            if ((treasureClass[name].Picks | 0) < 0) {
                forEachTCItem(treasureClass[name], (item, prob) => {
                    let count = Math.min(prob, picks);
    
                    getTC(item, count * mult).forEach((v, code) => {
                        ret[code] = ret[code] || 0;
                        ret[code] += v;
                    });
    
                    return picks -= count;
                });
            } else if (treasureClass[name].Picks) {
                let nodrop = noDrop(1, treasureClass[name].NoDrop | 0, total);
                total += nodrop;
                picks = (1 + picks) / 2;
    
                forEachTCItem(treasureClass[name], (item, prob) => {
                    getTC(item, mult * picks * prob / total).forEach((v, code) => {
                        ret[code] = ret[code] || 0;
                        ret[code] += v;
                    });
                });
            }
    
            return ret;
        }
    
        return getItemList(name, mult);
    }
    
    const calculatedTc = {};
    
    [
        ...Object.keys(treasureClass),
        ...Object.keys(atomic),
    ].sort().forEach(key => {
        calculatedTc[key] = getTC(key, 1);
    });
    
    delete calculatedTc.Gold;
    
    fs.writeFileSync(destinationFile, JSON.stringify(calculatedTc, null, ' '));

	function adjustTc(name, mlvl, lvl) {
		mlvl = mlvl | 0;
		lvl = lvl | 0;

		if (lvl > mlvl && treasureClass[name].group) {
			let grp = groups[treasureClass[name].group] || [];

			for (let c = lvl; c >= 0; c--) {
				if (grp[c]) {
					return grp[c];
				}
			}
		}

		return name;
	}

	const levelCalcTc = {};

	full.Levels.forEach(level => {
		if (level.expansion && !expansion) {
			return;
		}

		levelCalcTc[level.LevelName] = {};

		if (level.NumMon) {
			[
				['normal', 'mon', 'TreasureClass1', 'Level', (expansion ? 'MonLvl1Ex' : 'MonLvl1')],
				['normal champs', 'mon', 'TreasureClass2', 'Level', (expansion ? 'MonLvl1Ex' : 'MonLvl1')],
				['normal uniques', 'mon', 'TreasureClass3', 'Level', (expansion ? 'MonLvl1Ex' : 'MonLvl1')],
				['normal boss', 'mon', 'TreasureClass4', 'Level', (expansion ? 'MonLvl1Ex' : 'MonLvl1')],
				['nightmare', 'nmon', 'TreasureClass1(N)', 'Level(N)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['nightmare champs', 'nmon', 'TreasureClass2(N)', 'Level(N)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['nightmare uniques', 'nmon', 'TreasureClass3(N)', 'Level(N)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['nightmare boss', 'nmon', 'TreasureClass4(N)', 'Level(N)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['hell', 'nmon', 'TreasureClass1(H)', 'Level(H)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['hell champs', 'nmon', 'TreasureClass2(H)', 'Level(H)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['hell uniques', 'nmon', 'TreasureClass3(H)', 'Level(H)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
				['hell boss', 'nmon', 'TreasureClass4(H)', 'Level(H)', (expansion ? 'MonLvl2Ex' : 'MonLvl2')],
			].forEach(([difficulty, monprefix, tcname, mlvlkey, lvlkey]) => {
				for (let c = 1; c <= 10; c++) {
					levelCalcTc[level.LevelName][difficulty] = levelCalcTc[level.LevelName][difficulty] || {};

					if (level[monprefix + c] && monstats[level[monprefix + c]]) {
						let mon = monstats[level[monprefix + c]],
							avg = (mon.MinGrp + mon.MaxGrp) / 2,
							minionavg = mon.minion2 ? (mon.PartyMin + mon.PartyMax) / 4 : (mon.PartyMin + mon.PartyMax) / 2,
							tcs = {};
		
						if (mon[tcname]) {
							tcs[adjustTc(mon[tcname], mon[mlvlkey], level[lvlkey])] = avg;
						}
		
						if (mon.minion1 && monstats[mon.minion1][tcname]) {
							let m1tc = adjustTc(monstats[mon.minion1][tcname], monstats[mon.minion1][mlvlkey], level[lvlkey])
							tcs[m1tc] = tcs[m1tc] || 0;
							tcs[m1tc] += minionavg;
						}
		
						if (mon.minion2 && monstats[mon.minion2][tcname]) {
							let m2tc = adjustTc(monstats[mon.minion2][tcname], monstats[mon.minion2][mlvlkey], level[lvlkey]);
							tcs[m2tc] = tcs[m2tc] || 0;
							tcs[m2tc] += minionavg;
						}
		
						let total = Object.values(tcs).reduce((t, v) => t + v, 0);
		
						tcs.forEach((mult, tc) => {
							if (calculatedTc[tc]) {
								for (let itc in calculatedTc[tc]) {
									if (calculatedTc[tc][itc]) {
										let chance = calculatedTc[tc][itc];
										let name = itc + ' - ' + items[itc].name;
										levelCalcTc[level.LevelName][difficulty][name] = levelCalcTc[level.LevelName][difficulty][name] || 0;
										levelCalcTc[level.LevelName][difficulty][name] += chance * mult / total;
									}
								}
							}
						});
					}
				}
			});
		}
	});

	fs.writeFileSync(levelCalcFile, JSON.stringify(levelCalcTc, null, ' '));
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
