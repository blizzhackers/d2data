'use strict'; /* global Vue */

let app;

function createLine(x1 = 0, y1 = 0, x2 = 0, y2 = 0, color = 'black') {
	return {type: 'line', x1, y1, x2, y2, color};
}

function createRect(x = 0, y = 0, width = 0, height = 0, color = 'black') {
	return {type: 'rect', x, y, width, height, color};
}

function createText(x = 0, y = 0, text = 'No Text', color = 'black') {
	return {type: 'text', x, y, text, color};
}

let $ = document.querySelector.bind(document);

(function () {
	app = new Vue({
		el: '#effortapp',
		data: {
			dmgTypes: {
				physical: 'Physical',
				magic: 'Magic',
				fire: 'Fire',
				lightning: 'Lightning',
				cold: 'Cold',
				poison: 'Poison',
			},
			difficulties: {
				0: 'Normal',
				1: 'Nightmare',
				2: 'Hell',
			},
			fontSize: 1,
			d2: {
				MonLvl: fetch('https://raw.githubusercontent.com/blizzhackers/d2data/master/json/MonLvl.json').then(response => response.json()),
				monstats: fetch('https://raw.githubusercontent.com/blizzhackers/d2data/master/json/monstats.json').then(response => response.json()),
				Levels: fetch('https://raw.githubusercontent.com/blizzhackers/d2data/master/json/Levels.json').then(response => response.json()),
			},
			requiredAreas: [ // Areas that we're forced to deal with through questing.
				// Act 1
				2,3,4,5,6,7,10,26,27,28,29,30,31,32,33,34,35,36,37,
				// Act 2
				41,42,43,44,45,46,50,51,52,53,54,56,57,58,60,61,62,63,64,66,67,68,69,70,71,72,73,74,
				// Act 3
				76,77,78,79,80,81,82,83,85,88,89,91,92,93,100,101,102,
				// Act 4
				104,105,106,107,108,
				// Act 5
				110,111,112,113,115,117,118,120,128,129,130,131,
			],
			svg: {
				width: 100,
				height: 100,
				aspectRatio: 1,
				elements: {},
			},
			debugMessage: '',
			visible: false,
			colorKey: {
				physical: '#000000',
				magic: '#C0C0C0',
				fire: '#FF0000',
				lightning: '#FFFF00',
				cold: '#0000FF',
				poison: '#00FF00',
			},
			textColorKey: {
				physical: '#FFFFFF',
				magic: '#000000',
				fire: '#000000',
				lightning: '#000000',
				cold: '#FFFFFF',
				poison: '#000000',
			},
			optionalAreas: false,
			skills: {
				conviction: 0,
				lowerResist: 0,
				amplify: 0,
			},
			pierce: {
				physical: 0,
				magic: 0,
				fire: 0,
				lightning: 0,
				cold: 0,
				poison: 0,
				all: 0,
			},
			mastery: {
				physical: 0,
				magic: 0,
				fire: 0,
				lightning: 0,
				cold: 0,
				poison: 0,
				all: 0,
			},
			bonus: {
				physical: 0,
				magic: 0,
				fire: 0,
				lightning: 0,
				cold: 0,
				poison: 0,
				all: 0,
			}
	},
		methods: {
			updateGraphs: function () {
				this.calculateEfforts();
			},
			calculateEfforts: function () {
				let elementSelect = $('#element-select'),
					difficultySelect = $('#difficulty-select'),
					maxYield = 1,
					elements = {},
					diffs = [0, 1, 2].filter(a => {
						for (let c = 0; c < difficultySelect.options.length; c++) {
							if (difficultySelect.options[c].value == a) {
								return difficultySelect.options[c].selected;
							}
						}

						return false;
					});

				this.bonus.fire = this.bonus.lightning = this.bonus.cold = this.bonus.poison = this.bonus.all;
				this.pierce.fire = this.pierce.lightning = this.pierce.cold = this.pierce.poison = this.pierce.all;
				this.mastery.fire = this.mastery.lightning = this.mastery.cold = this.mastery.all;

				Vue.set(this.svg, 'elements', {});
				
				for (let c = 0; c < elementSelect.options.length; c++) {
					if (elementSelect.options[c].selected) {
						elements[elementSelect.options[c].value] = elementSelect.options[c].value;
					}
				}

				diffs.forEach((diff, diffindex) => {
					let monprefix = ['mon', 'nmon', 'umon'][diff];
					let diffabv = ['', '(N)', '(H)'][diff];
					for (let index in this.d2.Levels) {
						let level = this.d2.Levels[index], key, monid, mon;
						let totalRarity = 0, stats = {
							yield: {
								physical: 0,
								magic: 0,
								fire: 0,
								lightning: 0,
								cold: 0,
								poison: 0,
							},
						};

						for (let c = 1; c <= 10; c++) {
							key = monprefix + c;
							if ((monid = level[key]) && (mon = this.d2.monstats[monid])) {
								let party = [], minions = [this.d2.monstats[mon.minion1], this.d2.monstats[mon.minion2]].filter(Boolean);
								mon.PartyMin = mon.PartyMin || 1;
								mon.PartyMax = mon.PartyMax || 1;
								mon.MinGrp = mon.MinGrp || 0;
								mon.MaxGrp = mon.MaxGrp || 0;
								mon.Rarity = mon.Rarity || 0;
								party.push([mon, (mon.PartyMin + mon.PartyMax) * mon.Rarity / 2]);
	
								minions.forEach(minion => {
									party.push([minion, (mon.MinGrp + mon.MaxGrp) * mon.Rarity / 2 / minions.length]);
								});
	
								party.forEach(mondata => {
									let [mon, rarity] = mondata,
										monlvl = this.d2.MonLvl[[mon.Level, level.MonLvl2Ex, level.MonLvl3Ex][diff]],
										hp = ((mon.minHP || 0) + (mon.maxHP || 0)) / 200 * monlvl['HP' + diffabv],
										xp = (mon.Exp || 0) / 100 * monlvl['XP' + diffabv];
									let calc = (resKey, resName) => {
										if (!xp || !rarity) {
											return 0;
										}
	
										if (!hp) {
											return Infinity;
										}

										let res = mon[resKey] || 0, modifier = 1;

										if (this.skills.conviction > 0 || this.skills.lowerResist > 0) {
											//debugger;
										}

										if (res >= 100) {
											switch(resName) {
												case 'fire':
												case 'lightning':
												case 'cold':
													res -= (this.skills.conviction + this.skills.lowerResist) / 5;
													break;
												case 'poison':
													res -= (this.skills.lowerResist) / 5;
													break;
												case 'physical':
													res -= (this.skills.amplify) / 5;
													break;
											}
										} else {
											switch(resName) {
												case 'fire':
												case 'lightning':
												case 'cold':
													res -= this.skills.conviction + this.skills.lowerResist;
													break;
												case 'poison':
													res -= this.skills.lowerResist;
													break;
													case 'physical':
														res -= this.skills.amplify;
														break;
												}
										}

										switch (resName) {
											case 'cold':
												if (res < 100) {
													res -= 20 + this.mastery.cold * 5;
												}

												break;
											case 'lightning':
												// This is divided by two because sorc lightning skills generally do 1 to X damage,
												// so the effective damage bonus is actually halved when you average it.
												modifier += (0.38 + 0.12 * this.mastery.lightning) / 2;
												break;
											case 'fire':
												modifier += 0.23 + 0.07 * this.mastery.fire;
												break;
										}

										modifier += 0.01 * this.bonus[resName];

										if (res < 100) {
											res -= this.pierce[resName];
										}

										res = Math.min(100, Math.max(-100, res)) / 100;
	
										return modifier * (xp / hp) * (1 - res) * rarity;
									};
									stats.yield.physical += calc('ResDm' + diffabv, 'physical');
									stats.yield.magic += calc('ResMa' + diffabv, 'magic');
									stats.yield.fire += calc('ResFi' + diffabv, 'fire');
									stats.yield.lightning += calc('ResLi' + diffabv, 'lightning');
									stats.yield.cold += calc('ResCo' + diffabv, 'cold');
									stats.yield.poison += calc('ResPo' + diffabv, 'poison');
									totalRarity += rarity;
								});
							}
						}
	
						if (totalRarity) {
							for (let key in stats.yield) {
								stats.yield[key] /= totalRarity;
							}
						}
	
						level['Calculations' + diffabv] = stats;
					}
	
					let acts = [];
	
					for (let lvlNum in this.d2.Levels) {
						if (lvlNum > 0) {
							let current = this.d2.Levels[lvlNum]['Calculations' + diffabv],
								yields = Object.keys(current.yield).sort((a, b) => current.yield[a] - current.yield[b]),
								act = this.d2.Levels[lvlNum].Act || 0;
							acts[act] = acts[act] || {yields: {}};
	
							yields.forEach(key => {
								acts[act].yields[key] = acts[act].yields[key] || [0, 0];
								if (this.optionalAreas || this.requiredAreas.includes(lvlNum|0)) {
									acts[act].yields[key][0] += current.yield[key];
									acts[act].yields[key][1] += 1;
								}
							});
						}
					}
	
					acts = acts.map(current => {
						for (let key in current.yields) {
							if (current.yields[key][0]) {
								current.yields[key] = current.yields[key][0] / current.yields[key][1];
							}
							else {
								current.yields[key] = 0;
							}
	
							maxYield = Math.max(maxYield, current.yields[key]);
						}
	
						return current.yields;
					});
					
					let totalIndex = acts.length, width = 1 / (acts.length + 1), floor = (diffindex + 1) / diffs.length;
					if (diffindex < diffs.length - 1) {
						Vue.set(this.svg.elements, 'lvlfloor' + diffabv, createLine(0, floor, 1, floor, '#000000'));
					}
					acts[totalIndex] = {};
	
					acts.forEach((current, index) => {
						let keys = Object.keys(current).filter(key => elements[key]), subWidth = width / keys.length, text = '';
						keys.forEach((key, subIndex) => {
							if (index < totalIndex) {
								acts[totalIndex][key] = acts[totalIndex][key] || 0;
								acts[totalIndex][key] += current[key];
							} else {
								current[key] /= totalIndex;
							}
	
							let height = current[key] / maxYield / diffs.length,
								x = width * index + subWidth * subIndex,
								y = floor - height;
							Vue.set(this.svg.elements, 'act' + index + key + diffindex, createRect(x, y, subWidth, height, this.colorKey[key] || '#000000'));
							Vue.set(this.svg.elements, 'act' + index + key + '-caption' + diffindex, createText(x + subWidth / 2, (diffindex + 0.9) / diffs.length, key, this.textColorKey[key]));
						});
	
						if (index < totalIndex) {
							text = 'Act ' + (index + 1) + ' ' + diffabv;
						} else {
							text = 'Average ' + diffabv;
						}
	
						if (index > 0) {
							Vue.set(this.svg.elements, 'act' + index + 'divider' + diffindex, createLine(width * index, diffindex / diffs.length, width * index, floor, '#000000'));
						}
						Vue.set(this.svg.elements, 'act' + index + 'text' + diffindex, createText(width * (index + 0.5), (diffindex + 0.1) / diffs.length, text, '#000000'));
					});
				});
			},
		},
		created: async function () {
			for (let key in this.d2) {
				this.d2[key] = await this.d2[key];
			}

			let newmonstats = {};
			for (let index in this.d2.monstats) {
				newmonstats[this.d2.monstats[index].Id] = this.d2.monstats[index];
			}
			this.d2.monstats = newmonstats;
			this.calculateEfforts();
			this.visible = true;

			let windowUpdate = () => {
				let elem = $('#renderer');
				if (elem) {
					this.svg.width = elem.clientWidth;
					this.svg.height = elem.clientHeight;
					this.svg.aspectRatio = this.svg.width / this.svg.height;
					this.fontSize = this.svg.width * 0.008;
					this.debugMessage = this.svg.width + 'x' + this.svg.height;
				}
				window.requestAnimationFrame(windowUpdate);
			};

			windowUpdate();
		},
	});
})();
