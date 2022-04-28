'use strict'; /* global Vue */

Object.defineProperty(Object.prototype, 'forEach', {
    value: function (func) {
        Object.keys(this).forEach(key => {
            func(this[key], key, this);
        });
    },
});

Object.defineProperty(Object.prototype, 'reduce', {
    value: function (func, value) {
        return Object.keys(this).reduce((total, key) => {
            return func(total, this[key], key, this);
        }, value);
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

(function () {
	function _s (diff) {
		return str => str + ['', '(N)', '(H)'][diff];
	}

	function idiv (a, b) {
		return (a / b) | 0;
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

	new Vue({
		el: '#dropsapp',
		data() {
			return {
				json: {
					strings: fetch(baseurl + 'localestrings-eng.json').then(res => res.json()),
					levels: fetch(baseurl + 'levels.json').then(res => res.json()),
					count: fetch(baseurl + 'moncountest.json').then(res => res.json()),
					monstats: fetch(baseurl + 'monstats.json').then(res => res.json()),
					super: fetch(baseurl + 'superuniques.json').then(res => res.json()),
					tc: fetch(baseurl + 'treasureclassex.json').then(res => res.json()),
					tcgroups: fetch(baseurl + 'treasureclassgroupsex.json').then(res => res.json()),
					atomic: fetch(baseurl + 'atomic.json').then(res => res.json()),
					itemtypes: fetch(baseurl + 'itemtypes.json').then(res => res.json()),
					itemratio: fetch(baseurl + 'itemratio.json').then(res => res.json()),
					weapons: fetch(baseurl + 'weapons.json').then(res => res.json()),
					armor: fetch(baseurl + 'armor.json').then(res => res.json()),
					misc: fetch(baseurl + 'misc.json').then(res => res.json()),
					uniqueitems: fetch(baseurl + 'uniqueitems.json').then(res => res.json()),
					setitems: fetch(baseurl + 'setitems.json').then(res => res.json()),
					items: null,
				},
				items: [],
				areaResults: [],
				packResults: [],
				visible: false,
				calculating: false,
				progress: 0,
				pageTitle: 'Diablo 2 Drop Calculator',
				params: {
					mf: 0,
					players: 1,
					group: 1,
					minilvl: 0,
					maxilvl: 110,	
				},
				parammap: [
					{key: 'mf', type: 'Uint', size: 2},
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
			};
		},
		watch: {
			params: {
				deep: true,
				handler() {
					if (this.params.group > this.params.players) {
						this.params.group = this.params.players;
					}

					if (this.params.minilvl > this.params.maxilvl) {
						this.params.maxilvl = this.params.minilvl;
					}

					this.updateHash();
				},
			},
		},
		computed: {
			exp() {
				return (this.params.players / 2 + this.params.group / 2) | 0;
			},
		},
		methods: {
			updateHash() {
				let items = [];
				this.items.forEach((item, index) => item.use && items.push(index));
				let paramdv = new DataView(new ArrayBuffer(this.parammap.reduce((t, line) => t + line.size, 0) + items.length * 2)), pos = 0;

				this.parammap.forEach(line => {
					paramdv['set' + line.type + (line.size * 8)](pos, this.params[line.key]);
					pos += line.size;
				});

				items.forEach(num => {
					paramdv.setUint16(pos, num);
					pos += 2;
				});

				window.location.hash = dtoa(paramdv);
			},
			makeRatio(chance) {
				let ratio = 1/chance;
				return Math.round(ratio).toString();
			},
			dropChance(base, divisor, min, diminishFactor) {
				base = base || 0;
				divisor = divisor || 1;
				min = min || 0;
		
				return (ilvl, qlvl, factor) => {
					let mf = diminishFactor ? idiv(this.params.mf * diminishFactor, this.params.mf + diminishFactor) : (this.params.mf | 0);
					let chance = (base - idiv(ilvl - qlvl, divisor)) * 128;
					chance = idiv(chance * 100, 100 + mf);
					chance = Math.max(min, chance);
					chance = (chance - chance * factor / 1024) / 2;
					return Math.min(1, 128 / chance);
				};
			},		
			matches(a, b) {
				if (!a || !a.length) {
					return false;
				}

				a = a.toLowerCase().split(/[^a-zA-Z0-9']+/i).filter(Boolean);
				b = b.toLowerCase().split(/[^a-zA-Z0-9']+/i).filter(Boolean);

				return a.every(av => b.some(bv => bv.indexOf(av) === 0));
			},
			capWords(a) {
				if (a && a.length) {
					return a.split(/([^a-zA-Z0-9']+)/i).map(word => word.charAt(0).toUpperCase() + word.slice(1)).join('');
				}

				return a;
			},
			getKeywords(type, ret = {}) {
				let itemtype = this.json.itemtypes[type];

				ret[itemtype.ItemType] = true;
				itemtype['Equiv1'] && this.getKeywords(itemtype['Equiv1'], ret);
				itemtype['Equiv2'] && this.getKeywords(itemtype['Equiv2'], ret);

				return Object.keys(ret);
			},
			clearResults() {
				this.areaResults.splice(0);
				this.packResults.splice(0);
			},
			adjustTc(name, lvl) {
				let origTcLevel = this.json.tc[name].level || 0;
			
				if (this.json.tc[name].group) {
					let grp = this.json.tcgroups[this.json.tc[name].group] || [];
			
					for (let c = lvl; c >= origTcLevel; c--) {
						if (grp[c]) {
							return grp[c];
						}
					}
				}
			
				return name;
			},
			setValidHere(set, level) {
				return level.Id === 39 || !this.cowsets[set.index];
			},
			async doCalc() {
				let areaResults = [], packResults = [], selectedItems = this.items.filter(item => item.use);

				if (selectedItems.length) {
					if (this.calculating) {
						return;
					}
	
					this.calculating = true;
					this.progress = 0;
					this.clearResults();
					await sleep(0);

					let progressInterval = 1 / 3 / Object.values(this.json.levels).length;
		
					for (let diff = 0; diff < 3; diff++) {
						let s = _s(diff), cache = {};

						for (let level of Object.values(this.json.levels)) {
							let lchance = 0;

							if (diff < 2 && level.Id > 132) {
								this.progress += progressInterval;
								continue;
							}

							level.calc.monsters[diff].forEach(({mon, mlvl, type, superMon, packCount}) => {
								if (mlvl < this.params.minilvl || mlvl > this.params.maxilvl) {
									return;
								}

								let chance = 1, schance = 0;

								let calc = (m, count, mtype, isMinion) => {
									let tc = (superMon && !isMinion) ? superMon[s('TC')] : m[m.Id === 'andariel' ? s('TreasureClass4') : s('TreasureClass' + (Math.min(3, mtype + 1)))];

									if (tc) {				
										tc = this.json.tc[this.adjustTc(tc, mlvl) || tc];

										let cachekey = [tc.lineNumber, mlvl, +(level.Id === 39)].join('|'), pchance = cache[cachekey] === undefined ? this.calcPicks(tc, pickItem => {
											let ichance = 0;

											selectedItems.forEach(item => {
												if (item.set && !this.setValidHere(item.set, level)) {
													return;
												}
		
												if (pickItem === item.code) {
													switch (item.quality) {
														case 'unique':
															if (mlvl >= (item.unique.lvl || 0)) {
																let ucount = this.json.uniqueitems.filter(u => u.enabled && u.code === item.code && mlvl >= (u.lvl || 0)).reduce((t, u) => {
																	return t + (u.rarity || 1);
																}, 0);
		
																if (!ucount) {
																	return;
																}
		
																ichance += item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0) * item.unique.rarity / ucount;
															}
															break;
			
														case 'set':
															if (mlvl >= (item.set.lvl || 0)) {
																let scount = this.json.setitems.filter(set => set.item === item.code && mlvl >= (set.lvl || 0) && this.setValidHere(set, level)).reduce((t, s) => {
																	return t + (s.rarity || 1);
																}, 0);
		
																if (!scount) {
																	return;
																}
		
																ichance += (1 - item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0)) *
																	item.func.set(mlvl, item.item.level || 0, tc.Set || 0) * item.set.rarity / scount;
															}
															break;
			
														case 'rare':
															ichance += (1 - item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0)) *
																(1 - item.func.set(mlvl, item.item.level || 0, tc.Set || 0)) *
																item.func.rare(mlvl, item.item.level || 0, tc.Rare || 0);
															break;
														case 'magic':
															ichance += (item.type.Rare ? (1 - item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0)) : 1) *
																(item.type.Rare ? (1 - item.func.set(mlvl, item.item.level || 0, tc.Set || 0)) : 1) *
																(item.type.Rare ? (1 - item.func.rare(mlvl, item.item.level || 0, tc.Rare || 0)) : 1) *
																item.func.magic(mlvl, item.item.level || 0, tc.Magic || 0);
															break;
														case 'hq':
															ichance += (item.type.Rare ? (1 - item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0)) : 1) *
																(item.type.Rare ? (1 - item.func.set(mlvl, item.item.level || 0, tc.Set || 0)) : 1) *
																(item.type.Rare ? (1 - item.func.rare(mlvl, item.item.level || 0, tc.Rare || 0)) : 1) *
																(1 - item.func.magic(mlvl, item.item.level || 0, tc.Magic || 0)) *
																item.func.hq(mlvl, item.item.level || 0, 0);
															break;
														case 'normal':
															if (item.type.Normal) {
																ichance += 1;
															} else {
																ichance += (item.type.Rare ? (1 - item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0)) : 1) *
																(item.type.Rare ? (1 - item.func.set(mlvl, item.item.level || 0, tc.Set || 0)) : 1) *
																(item.type.Rare ? (1 - item.func.rare(mlvl, item.item.level || 0, tc.Rare || 0)) : 1) *
																(1 - item.func.magic(mlvl, item.item.level || 0, tc.Magic || 0)) *
																(1 - item.func.hq(mlvl, item.item.level || 0, 0)) *
																item.func.normal(mlvl, item.item.level || 0, 0);
															}
															break;
														default:
															ichance += (1 - item.func.unique(mlvl, item.item.level || 0, tc.Unique || 0)) *
																(1 - item.func.set(mlvl, item.item.level || 0, tc.Set || 0)) *
																(1 - item.func.rare(mlvl, item.item.level || 0, tc.Rare || 0)) *
																(1 - item.func.magic(mlvl, item.item.level || 0, tc.Magic || 0)) *
																(1 - item.func.hq(mlvl, item.item.level || 0, 0)) *
																(1 - item.func.normal(mlvl, item.item.level || 0, 0));
															break;
													}	
												}
											});
		
											return ichance;
										}) : cache[cachekey];

										cache[cachekey] = pchance;

										if (!isMinion) {
											schance = pchance;
										}

										chance *= Math.pow(1 - pchance, count);
									}	
								};

								let packSize = superMon ? 1 : this.avg(mon['MinGrp'] || 0, mon['MaxGrp'] || 0);

								calc(mon, packSize, type, false);

								let minionCount = superMon ? this.avg(superMon['MinGrp'] || 0, superMon['MaxGrp'] || 0) : this.avg(mon['PartyMin'] || 0, mon['PartyMax'] || 0);

								if (superMon && minionCount) {
									minionCount += diff;
								}

								if (minionCount) {
									let minions = [
										mon['minion1'] && this.json.monstats[mon['minion1']],
										mon['minion2'] && this.json.monstats[mon['minion2']],
									].filter(Boolean);

									if (superMon && !minions.length) {
										minions[0] = mon;
									}

									minions.forEach(minion => {
										calc(minion, minionCount / minions.length, 0, true);
									});	
								}

								chance = 1 - chance;

								if (chance) {
									packResults.push({
										mon,
										mlvl,
										superMon,
										color: ['#000000', '#3366ff', '#b8860b', '#cc33ff', '#FF0000'][type],
										name: (superMon ? this.json.strings[superMon.Name] : this.json.strings[mon.NameStr]) + (packSize + minionCount > 1 ? ' Pack ' : ' ') + ['[N]', '[NM]', '[H]'][diff],
										chance,
										level,
										tooltip: [
											'Type: ' + ['Normal', 'Champion', 'Unique', 'Superunique', 'Boss'][type],
											'mlvl: ' + mlvl,
											'Area: [' + level.Id + '] ' + this.json.strings[level.LevelName],
											'Act: ' + (level.Id >= 109 ? 5 : level.Id >= 103 ? 4 : level.Id >= 75 ? 3 : level.Id >= 40 ? 2 : 1),
											schance !== chance ? 'Individual Chance: 1:' + this.makeRatio(schance) : null,
										].filter(Boolean).join('\n'),
									});

									lchance = 1 - (1 - lchance) * Math.pow(1 - chance, packCount);
								}
							});

							if (lchance) {
								areaResults.push({
									name: this.json.strings[level.LevelName] + [' [N]', ' [NM]', ' [H]'][diff],
									chance: lchance,
									tooltip: [
										'Id: ' + level.Id,
										'mlvl: ' + level[['MonLvlEx', 'MonLvlEx(N)', 'MonLvlEx(H)'][diff]] || 0,
										'Act: ' + (level.Id >= 109 ? 5 : level.Id >= 103 ? 4 : level.Id >= 75 ? 3 : level.Id >= 40 ? 2 : 1),
									].filter(Boolean).join('\n'),
								});	
							}

							this.progress += progressInterval;
							await sleep(0);
						}
					}

					areaResults = areaResults.sort((a, b) => {
						return b.chance - a.chance;
					});

					packResults = packResults.sort((a, b) => {
						return b.chance - a.chance;
					});
		
					this.areaResults.push(...areaResults);
					this.packResults.push(...packResults);
					this.calculating = false;
				}
			},
			calcPicks(tc, func) {
				if (tc) {
					let totalchance = 1;

					let dopick = item => {
						if (this.json.tc[item]) {
							return this.calcPicks(this.json.tc[item], func);
						} else if (this.json.atomic[item]) {
							return this.json.atomic[item].reduce((total, chance, subitem) => {
								return total + (chance * func(subitem));
							}, 0);
						}

						return func(item);
					};

					if (tc.Picks < 0) {
						for (let c = 1, picks = -tc.Picks; picks > 0 && c <= 9; c++) {
							let picklist = {};

							if (tc['Item' + c]) {
								for (let d = 1; picks > 0 && d <= tc['Prob' + c]; d++) {
									picklist[tc['Item' + c]] = picklist[tc['Item' + c]] || 0;
									picklist[tc['Item' + c]]++;
									picks--;
								}
							}

							picklist.forEach((pickCount, item) => {
								totalchance *= Math.pow(1 - dopick(item), pickCount);
							});
						}
					} else if (tc.Picks > 0) {
						//let picks = (1 + tc.Picks) / 2;
						let aggchance = 0;
						
						tc.precalc[this.exp].forEach((chance, item) => {
							aggchance += chance * dopick(item);
						});

						totalchance *= Math.pow(1 - aggchance, tc.Picks);
					}

					return 1 - totalchance;
				}

				return 0;
			},
			forEachMonster(level, diff, func) {
				let s = _s(diff);

				[0, 1, 2].forEach(type => {
					if (type && !level[s('MonUMin')] && !level[s('MonUMax')]) {
						return;
					}

					let m = num => level[(diff ? 'nmon' : type ? 'umon' : 'mon') + num];

					for (let c = 1; c <= 9; c++) {
						if (m(c)) {
							let mon = this.json.monstats[m(c)];

							if (mon.enabled && mon.killable) {
								let mlvl = this.monlevel(mon, level, diff) + [0, 2, 3][type];

								func(mon, mlvl, type);
							}
						}
					}
				});
			},
			avg(...nums) {
				return nums.reduce((t, v) => t + v, 0) / nums.length || 0;
			},
			monlevel(mon, level, diff) {
				if (!diff) {
					return mon['Level'] || 0;
				}

				let s = _s(diff),
					lvl = level[['MonLvl1Ex', 'MonLvl2Ex', 'MonLvl3Ex'][diff]] || 0,
					mlvl = mon[s('Level')] || 0;

				return lvl > mlvl ? lvl : mlvl;
			},
		},
		created: async function () {
			for (let key in this.json) {
				this.json[key] = await this.json[key];
			}

			this.json.monstats = Object.values(this.json.monstats).reduce((obj, mon) => {
				obj[mon.Id] = mon;
				return obj;
			}, {});

			this.json.itemratio.forEach(data => {
				data.func = {
					unique: this.dropChance(data.Unique, data.UniqueDivisor, data.UniqueMin, 250),
					set: this.dropChance(data.Set, data.SetDivisor, data.SetMin, 500),
					rare: this.dropChance(data.Rare, data.RareDivisor, data.RareMin, 500),
					magic: this.dropChance(data.Magic, data.MagicDivisor, data.MagicMin),
					hq: this.dropChance(data.HiQuality, data.HiQualityDivisor),
					normal: this.dropChance(data.Normal, data.NormalDivisor),
				};
			});

			[0, 1, 2].forEach(diff => {
				let s = _s(diff);
				this.json.levels.forEach(level => {
					let l = key => level[key] || 0;

					level.calc = level.calc || {};
					level.calc.monsters = level.calc.monsters || [];
					level.calc.monsters[diff] = level.calc.monsters[diff] || [];
	
					if (level.Id) {
						let supers = this.json.super.filter(s => s.areaId == level.Id || s.hcIdx === 19 && [66, 67, 68, 69, 70, 71, 72].includes(level.Id | 0)),
							bosses = this.json.monstats.filter(mon => mon.areaId == level.Id),
							acount = (this.json.count[level.Id] && this.json.count[level.Id][diff] || 0),
							scount = supers.reduce((total, sup) => {
								return total + 1 + diff + ((sup['MinGrp'] || 0) + (sup['MaxGrp'] || 0)) / 2;
							}, 0),
							bcount = bosses.reduce((total, mon) => {
								return total + 1 + + ((mon['MinGrp'] || 0) + (mon['MaxGrp'] || 0)) / 2;
							}, 0),
							ucount = this.avg(l(s('MonUMin')), l(s('MonUMax'))) * 0.8 * 5.5,
							ccount = this.avg(l(s('MonUMin')), l(s('MonUMax'))) * 0.2 * 3,
							count = acount - ucount - ccount - scount - bcount;

						let totalpackssize = 0, udiv = 0;

						this.forEachMonster(level, diff, (mon, mlvl, type) => {
							if (!type) {
								let m = key => mon[key] || 0;
								let packsize = this.avg(m('PartyMin') + m('PartyMax'), m('MinGrp') + m('MaxGrp'));

								totalpackssize += packsize;
							};

							if (type === 2) {
								udiv++;
							}
						});

						this.forEachMonster(level, diff, (mon, mlvl, type) => {
							let mult = [count / totalpackssize, ccount / 3 / udiv, ucount / 5.5 / udiv][type];
							level.calc.monsters[diff].push({
								mon,
								mlvl,
								type,
								packCount: mult,
							});
						});

						supers.forEach(sup => {
							let mon = this.json.monstats[sup.Class],
								mlvl = this.monlevel(mon, level, diff) + 3;

							level.calc.monsters[diff].push({
								mon,
								mlvl,
								type: 3,
								packCount: sup.hcIdx === 19 ? (1 / 7) : 1,
								superMon: sup,
							});
						});

						bosses.forEach(mon => {
							let mlvl = this.monlevel(mon, level, diff);

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

			this.json.items = Object.assign({}, this.json.armor, this.json.weapons, this.json.misc);

			[
				...Object.values(this.json.weapons),
				...Object.values(this.json.armor),
				...Object.values(this.json.misc),
			].sort((a, b) => {
				a = a.code;
				b = b.code;
				return a < b ? -1 : a > b ? 1 : 0;
			}).forEach(item => {
				let type = this.json.itemtypes[item.type],
					itemname = this.json.strings[item.code] || item.name,
					isExceptional = item.ubercode && item.code === item.ubercode,
					isElite = item.ultracode && item.code === item.ultracode,
					isuber = item.normcode && item.code !== item.normcode,
					isclass = type.class,
					ratioFuncs = Object.values(this.json.itemratio).filter(data => data.Version && !isuber === !data.Uber && !isclass === !data['Class Specific'])[0].func;

				if (['pk1', 'pk2', 'pk3', 'bet', 'ceh', 'fed', 'tes'].includes(item.code)) {
					item['spawnable'] = true;
					type['Normal'] = true;
				}

				if (!item['spawnable'] || item.code === 'gld') {
					return;
				}

				this.json.uniqueitems.forEach(unique => {
					if (unique.code === item.code && unique['enabled']) {
						let name = this.json.strings[unique.index] || unique.index;
						this.items.push({
							quality: 'unique',
							code: unique.code,
							item,
							type,
							name: name + ' [Unique]',
							searchable: [name, itemname, 'Unique', unique.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
							tooltip: [
								'Type: ' + itemname,
								'Code: ' + unique.code,
								'Keywords: ' + [name, itemname, 'Unique', unique.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
							].join('\n'),
							use: false,
							unique,
							func: ratioFuncs,
						});	
					}
				});

				this.json.setitems.forEach(set => {
					if (set.item === item.code) {
						let name = this.json.strings[set.index] || set.index;

						this.items.push({
							quality: 'set',
							code: set.item,
							item,
							type,
							name: name + ' [Set]',
							searchable: [name, itemname, 'Set', set.item, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
							tooltip: [
								'Type: ' + itemname,
								'Code: ' + set.item,
								'Keywords: ' + [name, itemname, 'Set', set.item, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
							].join('\n'),
							use: false,
							set,
							func: ratioFuncs,
						});
					}
				});

				if (type['Rare']) {
					this.items.push({
						quality: 'rare',
						code: item.code,
						item,
						type,
						name: itemname + ' [Rare]',
						searchable: [itemname, 'Rare', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						tooltip: 'Code: ' + item.code + '\nKeywords: ' + [itemname, 'Rare', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						use: false,
						func: ratioFuncs,
					});
				}

				if (!type['Normal']) {
					this.items.push({
						quality: 'magic',
						code: item.code,
						item,
						type,
						name: itemname + ' [Magic]',
						searchable: [itemname, 'Magic', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						tooltip: 'Code: ' + item.code + '\nKeywords: ' + [itemname, 'Magic', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						use: false,
						func: ratioFuncs,
					});
				}

				if (!type['Magic'] && !type['Normal']) {
					this.items.push({
						quality: 'hq',
						code: item.code,
						item,
						type,
						name: itemname + ' [Superior]',
						searchable: [itemname, 'Superior', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						tooltip: 'Code: ' + item.code + '\nKeywords: ' + [itemname, 'Superior', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						use: false,
						func: ratioFuncs,
					});
				}

				if (!type['Magic']) {
					this.items.push({
						quality: 'normal',
						code: item.code,
						item,
						type,
						name: itemname + ' [Normal]',
						searchable: [itemname, 'Normal', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						tooltip: 'Code: ' + item.code + '\nKeywords: ' + [itemname, 'Normal', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						use: false,
						func: ratioFuncs,
					});
				}

				if (!type['Magic'] && !type['Normal']) {
					this.items.push({
						quality: 'low',
						code: item.code,
						item,
						type,
						name: itemname + ' [Low Quality]',
						searchable: [itemname, 'Low Quality', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
						tooltip: 'Code: ' + item.code + '\nKeywords: ' + [itemname, 'Low Quality', item.code, ...this.getKeywords(type.Code), isExceptional ? 'exceptional' : 'nonexceptional', isElite ? 'elite' : 'nonelite'].join(' '),
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

				this.parammap.forEach(line => {
					this.params[line.key] = paramdata['get' + line.type + (line.size * 8)](pos);
					pos += line.size;
				});

				for (;pos < paramdata.byteLength; pos += 2) {
					let index = paramdata.getUint16(pos);
					this.items[index].use = true;
				}
			}

			this.visible = true;

			if (calc) {
				this.doCalc();
			}
		},
	});
})();
