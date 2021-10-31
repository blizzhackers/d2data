// eslint-disable-next-line no-unused-vars
/* global Vue app */
let encode = arr => {
		arr = arr.map(obj => {
			let ret = {};

			Object.keys(obj).forEach(key => {
				// eslint-disable-next-line eqeqeq
				if (key === 0 || key === '0' || (key | 0) != key || obj[key]) {
					ret[key] = obj[key];
				}
			});

			return ret;
		});

		return btoa(JSON.stringify(arr));
	}, decode = str => {
		str = atob(str);

		return str ? JSON.parse(str) : [];
	};

(async function () {
	let clamp = (a, v, b) => (v < a ? a : (v > b ? b : v));

	window.app = new Vue({
		el: '#skillapp',
		data: {
			d2: {
				skills: await (fetch('https://raw.githubusercontent.com/blizzhackers/d2data/master/json/skills.json').then(res => res.json())),
			},
			classes: [
				{
					name: 'Amazon',
					tabs: [
						{
							name: 'Bow and Crossbow',
							skills: [
								null, { id: 6 }, { id: 7 },
								{ id: 11 }, { id: 12 }, null,
								null, null, { id: 16 },
								{ id: 21 }, { id: 22 }, null,
								null, { id: 26 }, { id: 27 },
								{ id: 31 }, null, null,
							],
						},
						{
							name: 'Passive and Magic',
							skills: [
								{ id: 8 }, null, { id: 9 },
								null, { id: 13 }, null,
								{ id: 17 }, { id: 18 }, null,
								null, null, { id: 23 },
								{ id: 28 }, { id: 29 }, null,
								{ id: 32 }, null, { id: 33 },
							],
						},
						{
							name: 'Javelin and Spear',
							skills: [
								{ id: 10 }, null, null,
								null, { id: 14 }, { id: 15 },
								{ id: 19 }, null, { id: 20 },
								null, { id: 24 }, { id: 25 },
								{ id: 30 }, null, null,
								null, { id: 34 }, { id: 35 },
							],
						},
					],
				},
				{
					name: 'Assassin',
					tabs: [
						{
							name: 'Traps',
							skills: [
								null, { id: 251 }, null,
								{ id: 256 }, null, { id: 257 },
								{ id: 261 }, { id: 262 }, null,
								null, null, { id: 266 },
								{ id: 271 }, { id: 272 }, null,
								{ id: 276 }, null, { id: 277 },
							],
						},
						{
							name: 'Shadow Disciplines',
							skills: [
								null, { id: 252 }, { id: 253 },
								{ id: 258 }, null, null,
								null, { id: 263 }, { id: 264 },
								{ id: 267 }, { id: 268 }, null,
								null, null, { id: 273 },
								{ id: 278 }, { id: 279 }, null,
							],
						},
						{
							name: 'Martial Arts',
							skills: [
								null, { id: 254 }, { id: 255 },
								{ id: 259 }, null, { id: 260 },
								null, { id: 265 }, null,
								{ id: 269 }, null, { id: 270 },
								{ id: 274 }, null, { id: 275 },
								null, { id: 280 }, null,
							],
						},
					],
				},
				{
					name: 'Barbarian',
					tabs: [
						{
							name: 'Combat Skills',
							skills: [
								null, { id: 126 }, null,
								{ id: 132 }, null, { id: 133 },
								null, { id: 139 }, { id: 140 },
								{ id: 143 }, { id: 144 }, null,
								null, null, { id: 147 },
								{ id: 151 }, { id: 152 }, null,
							],
						},
						{
							name: 'Combat Masteries',
							skills: [
								{ id: 127 }, { id: 128 }, { id: 129 },
								{ id: 134 }, { id: 135 }, { id: 136 },
								{ id: 141 }, null, null,
								null, null, { id: 145 },
								{ id: 148 }, null, null,
								null, null, { id: 153 },
							],
						},
						{
							name: 'Warcries',
							skills: [
								{ id: 130 }, null, { id: 131 },
								{ id: 137 }, { id: 138 }, null,
								null, null, { id: 142 },
								{ id: 146 }, null, null,
								null, { id: 149 }, { id: 150 },
								{ id: 154 }, { id: 155 }, null,
							],
						},
					],
				},
				{
					name: 'Druid',
					tabs: [
						{
							name: 'Summoning',
							skills: [
								null, { id: 221 }, { id: 222 },
								{ id: 226 }, { id: 227 }, null,
								null, null, { id: 231 },
								{ id: 236 }, { id: 237 }, null,
								null, null, { id: 241 },
								{ id: 246 }, { id: 247 }, null,
							],
						},
						{
							name: 'Shapeshifting',
							skills: [
								{ id: 223 }, { id: 224 }, null,
								null, null, { id: 228 },
								{ id: 232 }, null, { id: 233 },
								{ id: 238 }, { id: 239 }, null,
								null, { id: 242 }, { id: 243 },
								{ id: 248 }, null, null,
							],
						},
						{
							name: 'Elemental',
							skills: [
								{ id: 225 }, null, null,
								{ id: 229 }, null, { id: 230 },
								{ id: 234 }, null, { id: 235 },
								null, { id: 240 }, null,
								{ id: 244 }, { id: 245 }, null,
								{ id: 249 }, { id: 250 }, null,
							],
						},
					],
				},
				{
					name: 'Necromancer',
					tabs: [
						{
							name: 'Curses',
							skills: [
								null, { id: 66 }, null,
								{ id: 71 }, null, { id: 72 },
								null, { id: 76 }, { id: 77 },
								{ id: 81 }, { id: 82 }, null,
								{ id: 86 }, null, { id: 87 },
								null, { id: 91 }, null,
							],
						},
						{
							name: 'Poison and Bone',
							skills: [
								null, { id: 67 }, { id: 68 },
								{ id: 73 }, { id: 74 }, null,
								null, null, { id: 78 },
								{ id: 83 }, { id: 84 }, null,
								null, null, { id: 88 },
								{ id: 92 }, { id: 93 }, null,
							],
						},
						{
							name: 'Summoning',
							skills: [
								{ id: 69 }, null, { id: 70 },
								null, { id: 75 }, null,
								{ id: 79 }, null, { id: 80 },
								null, { id: 85 }, null,
								{ id: 89 }, { id: 90 }, null,
								null, { id: 94 }, { id: 95 },
							],
						},
					],
				},
				{
					name: 'Paladin',
					tabs: [
						{
							name: 'Combat Skills',
							skills: [
								{ id: 96 }, null, { id: 97 },
								null, { id: 101 }, null,
								{ id: 106 }, null, { id: 107 },
								{ id: 111 }, { id: 112 }, null,
								{ id: 116 }, null, { id: 117 },
								null, { id: 121 }, null,
							],
						},
						{
							name: 'Offensive Auras',
							skills: [
								{ id: 98 }, null, null,
								null, { id: 102 }, { id: 103 },
								{ id: 108 }, null, null,
								{ id: 113 }, { id: 114 }, null,
								null, { id: 118 }, { id: 119 },
								{ id: 122 }, null, { id: 123 },
							],
						},
						{
							name: 'Defensive Auras',
							skills: [
								{ id: 99 }, null, { id: 100 },
								null, { id: 104 }, { id: 105 },
								{ id: 109 }, null, { id: 110 },
								null, { id: 115 }, null,
								{ id: 120 }, null, null,
								null, { id: 124 }, { id: 125 },
							],
						},
					],
				},
				{
					name: 'Sorceress',
					tabs: [
						{
							name: 'Fire',
							skills: [
								null, { id: 36 }, { id: 37 },
								{ id: 41 }, null, null,
								{ id: 46 }, { id: 47 }, null,
								{ id: 51 }, null, { id: 52 },
								null, { id: 56 }, null,
								null, { id: 61 }, { id: 62 },
							],
						},
						{
							name: 'Lightning',
							skills: [
								null, { id: 38 }, null,
								{ id: 42 }, null, { id: 43 },
								{ id: 48 }, { id: 49 }, null,
								null, { id: 53 }, { id: 54 },
								{ id: 57 }, null, { id: 58 },
								null, { id: 63 }, null,
							],
						},
						{
							name: 'Cold',
							skills: [
								null, { id: 39 }, { id: 40 },
								{ id: 44 }, { id: 45 }, null,
								null, null, { id: 50 },
								null, { id: 55 }, null,
								{ id: 59 }, null, { id: 60 },
								{ id: 64 }, { id: 65 }, null,
							],
						},
					],
				},
			],
			skills: {
				// Synergy is visual only, since I haven't
				// found how the game defines these for display.
				'6': {
					'name': 'Magic Arrow',
					'desc': 'creates a magical arrow or bolt that does extra damage',
				},
				'7': {
					'name': 'Fire Arrow',
					'desc': 'magically enhances your arrows or bolts with fire',
					'synergy': [
						[16, '+12%'],
					],
				},
				'8': {
					'name': 'Inner Sight',
					'desc': 'illuminates nearby enemies making them easier to hit for you and your party',
				},
				'9': {
					'name': 'Critical Strike',
					'desc': 'PASSIVE\nyour attacks have a chance to do double damage',
				},
				'10': {
					'name': 'Jab',
					'desc': 'attacks with a series of rapid thrusts using a javelin or spear class weapon',
				},
				'11': {
					'name': 'Cold Arrow',
					'desc': 'magically enhances your arrows or bolts by adding cold damage and a slowing effect\ncold arrows only do half of their regular damage',
					'synergy': [
						[21, '+12%'],
					],
				},
				'12': {
					'name': 'Multiple Shot',
					'desc': 'magically splits one arrow or bolt into many',
				},
				'13': {
					'name': 'Dodge',
					'desc': 'PASSIVE\nyou have a chance to dodge a melee attack when attacking or standing still',
				},
				'14': {
					'name': 'Power Strike',
					'desc': 'adds lightning damage to attacks with javelin and spear class weapons',
					'synergy': [
						[20, '+10%'],
						[24, '+10%'],
						[34, '+10%'],
						[35, '+10%'],
					],
				},
				'15': {
					'name': 'Poison Javelin',
					'desc': 'magically enhances your javelin to leave a trail of poison clouds',
					'synergy': [
						[25, '+12%'],
					],
				},
				'16': {
					'name': 'Exploding Arrow',
					'desc': 'enchants an arrow or bolt that explodes on contact, damaging all nearby enemies',
					'synergy': [
						[7, '+12%'],
					],
				},
				'17': {
					'name': 'Slow Missiles',
					'desc': 'illuminates nearby enemies and slows their ranged attacks',
				},
				'18': {
					'name': 'Avoid',
					'desc': 'PASSIVE\nyou have a chance to dodge enemy missiles when attacking or standing still',
				},
				'19': {
					'name': 'Impale',
					'desc': 'increases attack damage but rapidly degrades the weapon',
				},
				'20': {
					'name': 'Lightning Bolt',
					'desc': 'magically converts your javelin into a bolt of lightning',
					'synergy': [
						[14, '+3%'],
						[24, '+3%'],
						[34, '+3%'],
						[35, '+3%'],
					],
				},
				'21': {
					'name': 'Ice Arrow',
					'desc': 'magically enhances your arrow or bolt to freeze your enemies',
					'synergy': [
						[11, '+8%'],
						[31, '+5% Freeze Len.'],
					],
				},
				'22': {
					'name': 'Guided Arrow',
					'desc': 'enhances your arrows and bolts to track your target or seek one of its own always hits',
				},
				'23': {
					'name': 'Penetrate',
					'desc': 'PASSIVE\nincreases your attack rating',
				},
				'24': {
					'name': 'Charged Strike',
					'desc': 'adds lightning damage to javelin and spear class weapons and releases charged bolts upon impact',
					'synergy': [
						[14, '+10%'],
						[20, '+10%'],
						[34, '+10%'],
						[35, '+10%'],
					],
				},
				'25': {
					'name': 'Plague Javelin',
					'desc': 'magically enhances your javelin to release expanding clouds of poison upon impact',
					'synergy': [
						[15, '+10%'],
					],
				},
				'26': {
					'name': 'Strafe',
					'desc': 'magically splits one arrow into several that target multiple nearby enemies',
				},
				'27': {
					'name': 'Immolation Arrow',
					'desc': 'enhances arrows or bolts to cause severe fire damage and creates a pyre upon impact',
					'synergy': [
						[16, '+10%'],
						[7, '+5% Fire DPS'],
					],
				},
				'28': {
					'name': 'Decoy',
					'desc': 'creates a duplicate of yourself that draws fire from enemies',
				},
				'29': {
					'name': 'Evade',
					'desc': 'PASSIVE\nyou have a chance to dodge a melee or missile attack when walking or running',
				},
				'30': {
					'name': 'Fend',
					'desc': 'attacks all adjacent targets',
				},
				'31': {
					'name': 'Freezing Arrow',
					'desc': 'magically enhances an arrow or bolt to freeze entire groups of monsters',
					'synergy': [
						[11, '+12%'],
						[21, '+5% Freeze Len.'],
					],
				},
				'32': {
					'name': 'Valkyrie',
					'desc': 'summons a powerful Valkyrie ally',
					'synergy': [
						[28, '+20% Life'],
						[23, '+40 Attack Rating'],
						[9],
						[13],
						[18],
						[29],
					],
				},
				'33': {
					'name': 'Pierce',
					'desc': 'PASSIVE\nyour missiles have a chance to pass through enemies that they hit',
				},
				'34': {
					'name': 'Lightning Strike',
					'desc': 'adds lightning damage to javelin and spear class weapons and releases chain lightning upon impact',
					'synergy': [
						[14, '+8%'],
						[20, '+8%'],
						[24, '+8%'],
						[35, '+8%'],
					],
				},
				'35': {
					'name': 'Lightning Fury',
					'desc': 'changes a thrown javelin into a powerful bolt of lightning that splits on impact',
					'synergy': [
						[14, '+1%'],
						[20, '+1%'],
						[24, '+1%'],
						[34, '+1%'],
					],
				},
				'36': {
					'name': 'Fire Bolt',
					'desc': 'creates a magical flaming missile',
				},
				'37': {
					'name': 'Warmth',
					'desc': 'PASSIVE\nincreases the rate at which you recover mana',
				},
				'38': {
					'name': 'Charged Bolt',
					'desc': 'creates multiple, randomly directed bolts of electrical energy',
				},
				'39': {
					'name': 'Ice Bolt',
					'desc': 'creates a magical bolt of ice that damages and slows your enemies',
				},
				'40': {
					'name': 'Frozen Armor',
					'desc': 'increases your defense rating and freezes enemies that hit you',
				},
				'41': {
					'name': 'Inferno',
					'desc': 'creates a continuous jet of flame to scorch your enemies',
				},
				'42': {
					'name': 'Static Field',
					'desc': 'creates an electrical field that reduces life of all nearby enemies',
				},
				'43': {
					'name': 'Telekinesis',
					'desc': 'uses the power of your mind to pick up items, use objects, and knock back enemies',
				},
				'44': {
					'name': 'Frost Nova',
					'desc': 'creates an expanding ring of ice that damages and slows all nearby enemies',
				},
				'45': {
					'name': 'Ice Blast',
					'desc': 'creates a magical sphere of ice that damages and freezes your enemy',
				},
				'46': {
					'name': 'Blaze',
					'desc': 'creates a wall of fire in your wake to scorch your enemies',
				},
				'47': {
					'name': 'Fire Ball',
					'desc': 'creates an explosive sphere of fiery death to engulf your enemies',
				},
				'48': {
					'name': 'Nova',
					'desc': 'creates an expanding ring of lightning to shock nearby enemies',
				},
				'49': {
					'name': 'Lightning',
					'desc': 'creates a powerful lightning bolt to lay waste to your enemies',
				},
				'50': {
					'name': 'Shiver Armor',
					'desc': 'increases your defense rating freezes and damages enemies that hit you',
				},
				'51': {
					'name': 'Fire Wall',
					'desc': 'creates a wall of flame that blocks or burns your enemies',
				},
				'52': {
					'name': 'Enchant',
					'desc': 'enchants equipped weapon of targeted character or minion adds fire damage to melee weapons adds one-third fire damage to ranged weapons',
				},
				'53': {
					'name': 'Chain Lightning',
					'desc': 'creates a bolt of lightning that arcs through several targets',
				},
				'54': {
					'name': 'Teleport',
					'desc': 'instantly moves to a destination within your line of sight',
				},
				'55': {
					'name': 'Glacial Spike',
					'desc': 'creates a magical ice comet that freezes or kills nearby enemies',
				},
				'56': {
					'name': 'Meteor',
					'desc': 'summons a meteor from the heavens to crush and incinerate your enemies',
				},
				'57': {
					'name': 'Thunder Storm',
					'desc': 'summons a deadly thunderstorm that strikes your enemies with bolts of lightning',
				},
				'58': {
					'name': 'Energy Shield',
					'desc': 'creates a magical shield that consumes mana instead of health when you take damage',
				},
				'59': {
					'name': 'Blizzard',
					'desc': 'summons massive shards of ice to destroy your enemies',
				},
				'60': {
					'name': 'Chilling Armor',
					'desc': 'increases defense and discharges an ice bolt in retaliation against ranged attackers',
				},
				'61': {
					'name': 'Fire Mastery',
					'desc': 'PASSIVE\nincreases all damage caused by your fire spells',
				},
				'62': {
					'name': 'Hydra',
					'desc': 'summons a multi-headed beast of flame to reduce your enemies to ashes',
				},
				'63': {
					'name': 'Lightning Mastery',
					'desc': 'PASSIVE\nincreases all damage caused by your lightning spells',
				},
				'64': {
					'name': 'Frozen Orb',
					'desc': 'creates a magical globe that sprays a torrent of ice bolts to lay waste to your enemies',
				},
				'65': {
					'name': 'Cold Mastery',
					'desc': 'PASSIVE\nincreases the damage of your cold attacks by piercing enemies resistances to cold',
				},
				'66': {
					'name': 'Amplify Damage',
					'desc': 'curses a group of enemies, increasing the non-magic damage they receive',
				},
				'67': {
					'name': 'Teeth',
					'desc': 'fires a barrage of summoned barbed teeth',
				},
				'68': {
					'name': 'Bone Armor',
					'desc': 'creates an orbiting shield of bone that absorbs melee damage',
				},
				'69': {
					'name': 'Skeleton Mastery',
					'desc': 'PASSIVE\nincreases life and damage of raised skeletons and revived creatures',
				},
				'70': {
					'name': 'Raise Skeleton',
					'desc': 'cast on the corpse of a slain monster, this raises a skeleton warrior that fights for you',
				},
				'71': {
					'name': 'Dim Vision',
					'desc': 'curses a group of monsters, reducing their vision radius',
				},
				'72': {
					'name': 'Weaken',
					'desc': 'curses a group of enemies, reducing the amount of damage they inflict',
				},
				'73': {
					'name': 'Poison Dagger',
					'desc': 'adds poison to your dagger attacks',
				},
				'74': {
					'name': 'Corpse Explosion',
					'desc': 'cast on the corpse of a slain monster, it explodes, damaging nearby enemies',
				},
				'75': {
					'name': 'Clay Golem',
					'desc': 'creates a golem from the earth to fight by your side',
				},
				'76': {
					'name': 'Iron Maiden',
					'desc': 'curses a group of enemies, causing them to damage themselves when damaging others',
				},
				'77': {
					'name': 'Terror',
					'desc': 'curses a group of monsters, causing them to flee in terror',
				},
				'78': {
					'name': 'Bone Wall',
					'desc': 'creates an impassable barrier of bone and debris',
				},
				'79': {
					'name': 'Golem Mastery',
					'desc': 'Enhances Speed and Life of all your Golems',
				},
				'80': {
					'name': 'Raise Skeletal Mage',
					'desc': 'cast on the corpse of a slain monster, this raises a skeleton mage that fights for you',
				},
				'81': {
					'name': 'Confuse',
					'desc': 'curses a monster to force it to attack random targets',
				},
				'82': {
					'name': 'Life Tap',
					'desc': 'curses a group of monsters so that damaging them gives the attacker life',
				},
				'83': {
					'name': 'Poison Explosion',
					'desc': 'cast on the corpse of a slain monster, toxic gas is released that poisons nearby monsters',
				},
				'84': {
					'name': 'Bone Spear',
					'desc': 'summons a deadly spike of bone to impale your enemies',
				},
				'85': {
					'name': 'Blood Golem',
					'desc': 'creates a golem that shares with you the life it steals and damage it receives',
				},
				'86': {
					'name': 'Attract',
					'desc': 'curses a monster to become the target of all nearby monsters this curse may not be overridden by another curse',
				},
				'87': {
					'name': 'Decrepify',
					'desc': 'curses a group of enemies to make them slow, weak and take amplified damage',
				},
				'88': {
					'name': 'Bone Prison',
					'desc': 'creates a barrier of fossilized bone around your target',
				},
				'89': {
					'name': 'Summon Resist',
					'desc': 'PASSIVE\nincreases the resistances of all summoned creatures',
				},
				'90': {
					'name': 'Iron Golem',
					'desc': 'transforms a metallic item into a golem that gains the properties of the item',
				},
				'91': {
					'name': 'Lower Resist',
					'desc': 'curses an enemy to take more damage from all magical attacks lowers resistances of monsters lowers maximum resistances of hostile players',
				},
				'92': {
					'name': 'Poison Nova',
					'desc': 'emits an expanding ring of concentrated poison',
				},
				'93': {
					'name': 'Bone Spirit',
					'desc': 'releases a spirit of the restless undead that tracks its target or finds one of its own',
				},
				'94': {
					'name': 'Fire Golem',
					'desc': 'creates a golem that converts the damage it receives from fire into life',
				},
				'95': {
					'name': 'Revive',
					'desc': 'returns a monster to life to fight by your side',
				},
				'96': {
					'name': 'Sacrifice',
					'desc': 'increased accuracy and damage at the cost of life',
				},
				'97': {
					'name': 'Smite',
					'desc': 'temporarily stun your enemy by bashing it with your shield',
				},
				'98': {
					'name': 'Might',
					'desc': 'when active, aura increases the damage done by you and your party',
				},
				'99': {
					'name': 'Prayer',
					'desc': 'when active, aura slowly regenerates the life of you and your party',
				},
				'100': {
					'name': 'Resist Fire',
					'desc': 'when active, aura decreases fire damage done to you and your party',
				},
				'101': {
					'name': 'Holy Bolt',
					'desc': 'a bolt of divine energy that damages undead enemies or heals allies',
				},
				'102': {
					'name': 'Holy Fire',
					'desc': 'when active, aura damages nearby enemies with heavenly flames',
				},
				'103': {
					'name': 'Thorns',
					'desc': 'when active, aura reflects damage done to you back at your attacker',
				},
				'104': {
					'name': 'Defiance',
					'desc': 'when active, aura increases the defense rating of you and your party',
				},
				'105': {
					'name': 'Resist Cold',
					'desc': 'when active, aura decreases cold damage done to you and your party',
				},
				'106': {
					'name': 'Zeal',
					'desc': 'allows you to attack multiple adjacent enemies with a single attack',
				},
				'107': {
					'name': 'Charge',
					'desc': 'charge into battle and attack an enemy',
				},
				'108': {
					'name': 'Blessed Aim',
					'desc': 'when active, aura increases the attack rating for you and your party',
				},
				'109': {
					'name': 'Cleansing',
					'desc': 'when active, aura reduces the length of time you and your party will remain poisoned or cursed',
				},
				'110': {
					'name': 'Resist Lightning',
					'desc': 'when active, aura decreases lightning damage done to you and your party',
				},
				'111': {
					'name': 'Vengeance',
					'desc': 'fire, lightning and cold damage are added to each successful attack',
				},
				'112': {
					'name': 'Blessed Hammer',
					'desc': 'summons an ethereal hammer that spirals outwards damaging enemies it hits\n150 Percent Damage to Undead',
				},
				'113': {
					'name': 'Concentration',
					'desc': 'when active, aura increases the damage and decreases the chance that the attack will be interrupted for you and your party ',
				},
				'114': {
					'name': 'Holy Freeze',
					'desc': 'when active, aura freezes nearby monsters',
				},
				'115': {
					'name': 'Vigor',
					'desc': 'when active, aura increases stamina recovery rate, maximum stamina and movement speed for you and your party',
				},
				'116': {
					'name': 'Conversion',
					'desc': 'converts monsters to fight against other foul demons and beasts',
				},
				'117': {
					'name': 'Holy Shield',
					'desc': 'enhances your shield with divine power',
				},
				'118': {
					'name': 'Holy Shock',
					'desc': 'when active, aura causes pulses of electricity to damage nearby enemies adds lightning damage to your attack',
				},
				'119': {
					'name': 'Sanctuary',
					'desc': 'when active, aura damages the undead and knocks them back',
				},
				'120': {
					'name': 'Meditation',
					'desc': 'when active, aura increases mana recovery for you and your party',
				},
				'121': {
					'name': 'Fist of the Heavens',
					'desc': 'lightning strikes your target as holy bolts seek out nearby enemies',
				},
				'122': {
					'name': 'Fanaticism',
					'desc': 'when active, aura increases damage, attack speed, and attack rating for you and your party',
				},
				'123': {
					'name': 'Conviction',
					'desc': 'when active, aura reduces the defenses and resistances of nearby enemies',
				},
				'124': {
					'name': 'Redemption',
					'desc': 'when active, aura attempts to redeem the souls of slain enemies to give you life and mana',
				},
				'125': {
					'name': 'Salvation',
					'desc': 'when active, aura decreases fire, cold and lightning damage done to you and your party',
				},
				'126': {
					'name': 'Bash',
					'desc': 'powerful blow that increases the damage done to enemies and knocks them back',
				},
				'127': {
					'name': 'Sword Mastery',
					'desc': 'PASSIVE\nimproves sword fighting skill',
				},
				'128': {
					'name': 'Axe Mastery',
					'desc': 'PASSIVE\nimproves axe fighting skill',
				},
				'129': {
					'name': 'Mace Mastery',
					'desc': 'PASSIVE\nimproves mace fighting skill',
				},
				'130': {
					'name': 'Howl',
					'desc': 'sends nearby monsters scrambling away in fear',
				},
				'131': {
					'name': 'Find Potion',
					'desc': 'use on the corpse of a slain monster for a chance to find a potion',
				},
				'132': {
					'name': 'Leap',
					'desc': 'leaps away from danger or into the fray',
				},
				'133': {
					'name': 'Double Swing',
					'desc': 'when two weapons are equipped attacks two targets if possible, or one target twice',
				},
				'134': {
					'name': 'Pole Arm Mastery',
					'desc': 'PASSIVE\nimproves pole arm skill',
				},
				'135': {
					'name': 'Throwing Mastery',
					'desc': 'PASSIVE\nimproves thrown weapon skill',
				},
				'136': {
					'name': 'Spear Mastery',
					'desc': 'PASSIVE\nimproves spear fighting skill',
				},
				'137': {
					'name': 'Taunt',
					'desc': 'enrages a monster into relentlessly attacking',
				},
				'138': {
					'name': 'Shout',
					'desc': 'warns of impending danger and improves the defense rating of you and your party',
				},
				'139': {
					'name': 'Stun',
					'desc': 'stuns your target for a short time and increases your attack rating',
				},
				'140': {
					'name': 'Double Throw',
					'desc': 'allows you to throw two different throwing weapons at the same time',
				},
				'141': {
					'name': 'Increased Stamina',
					'desc': 'PASSIVE\nincreases your stamina',
				},
				'142': {
					'name': 'Find Item',
					'desc': 'use on the corpse of a slain monster to find hidden treasures',
				},
				'143': {
					'name': 'Leap Attack',
					'desc': 'leaps to and attacks target enemy in one swift assault',
				},
				'144': {
					'name': 'Concentrate',
					'desc': 'attack that is not interruptible and improves attack and defense rating',
				},
				'145': {
					'name': 'Iron Skin',
					'desc': 'PASSIVE\nimproves defense rating',
				},
				'146': {
					'name': 'Battle Cry',
					'desc': 'fearsome cry that decreases enemies defense rating and damage',
				},
				'147': {
					'name': 'Frenzy',
					'desc': 'allows you to swing two weapons at once each successful attack increases your overall speed requires you to equip two weapons',
				},
				'148': {
					'name': 'Increased Speed',
					'desc': 'PASSIVE\nincreases walk and run speed',
				},
				'149': {
					'name': 'Battle Orders',
					'desc': 'improves the maximum mana, life and stamina of you and your party',
				},
				'150': {
					'name': 'Grim Ward',
					'desc': 'use on the corpse of a slain monster to create a frightening totem that causes nearby monsters to flee',
				},
				'151': {
					'name': 'Whirlwind',
					'desc': 'a whirling dance of death that cuts a path through the legions of your enemies',
				},
				'152': {
					'name': 'Berserk',
					'desc': 'a powerful but reckless attack that increases damage and attack rating but decreases defense rating',
				},
				'153': {
					'name': 'Natural Resistance',
					'desc': 'PASSIVE\nincreases natural resistances to elemental and poison damage',
				},
				'154': {
					'name': 'War Cry',
					'desc': 'injures and stuns all nearby enemies',
				},
				'155': {
					'name': 'Battle Command',
					'desc': 'increases all current skill levels for you and your party',
				},
				'221': {
					'name': 'Raven',
					'desc': 'summon ravens to peck out the eyes of your enemies',
				},
				'222': {
					'name': 'Poison Creeper',
					'desc': 'summon a vine that spreads disease to all it contacts',
				},
				'223': {
					'name': 'Werewolf',
					'desc': 'transform into a werewolf',
				},
				'224': {
					'name': 'Lycanthropy',
					'desc': 'PASSIVE\nimproves duration and life when in werewolf or werebear form',
				},
				'225': {
					'name': 'Firestorm',
					'desc': 'unleash fiery chaos to burn your enemies',
				},
				'226': {
					'name': 'Oak Sage',
					'desc': 'summon a spirit pet that increases life for you and your party',
				},
				'227': {
					'name': 'Summon Spirit Wolf',
					'desc': 'summon a wolf with teleporting ability to fight by your side',
				},
				'228': {
					'name': 'Werebear',
					'desc': 'transform into a werebear',
				},
				'229': {
					'name': 'Molten Boulder',
					'desc': 'launch a boulder of flaming hot magma that knocks back your enemies',
				},
				'230': {
					'name': 'Arctic Blast',
					'desc': 'blast a continuous jet of ice to burn your enemies with frost',
				},
				'231': {
					'name': 'Carrion Vine',
					'desc': 'summon a vine that eats corpses and replenishes your life',
				},
				'232': {
					'name': 'Feral Rage',
					'desc': 'when in werewolf form, go into a frenzied rage to steal increasing amounts of life from your enemies with successive hits',
				},
				'233': {
					'name': 'Maul',
					'desc': 'when in werebear form, maul your enemies for increasing extra damage with successive hits',
				},
				'234': {
					'name': 'Fissure',
					'desc': 'open volcanic vents below your enemies, burning them to a crisp',
				},
				'235': {
					'name': 'Cyclone Armor',
					'desc': 'shield yourself from damage caused by fire, cold, and lightning',
				},
				'236': {
					'name': 'Heart of Wolverine',
					'desc': 'summon a spirit pet that adds to the damage and attack rating of you and your party',
				},
				'237': {
					'name': 'Summon Dire Wolf',
					'desc': 'summon a wolf that becomes enraged, eating corpses to increase damage it does to enemies',
				},
				'238': {
					'name': 'Rabies',
					'desc': 'when in werewolf form, bite your enemies to inflict them with disease that spreads to other monsters',
				},
				'239': {
					'name': 'Fire Claws',
					'desc': 'when in werewolf or werebear form, maul your enemies with a fiery claw attack',
				},
				'240': {
					'name': 'Twister',
					'desc': 'release several small whirlwinds that cut a path through your enemies',
				},
				'241': {
					'name': 'Solar Creeper',
					'desc': 'summon a vine that eats corpses and replenishes your mana',
				},
				'242': {
					'name': 'Hunger',
					'desc': 'when in werewolf or werebear form, bite your enemies to gain life and mana',
				},
				'243': {
					'name': 'Shock Wave',
					'desc': 'when in werebear form, stomp to create a shock wave that stuns nearby enemies',
				},
				'244': {
					'name': 'Volcano',
					'desc': 'summon forth a volcano to rain death and destruction over your enemies',
				},
				'245': {
					'name': 'Tornado',
					'desc': 'create a funnel of wind and debris to blast your enemies',
				},
				'246': {
					'name': 'Spirit of Barbs',
					'desc': 'summon spirit pet that reflects damage taken by you and your party back at your enemies',
				},
				'247': {
					'name': 'Summon Grizzly',
					'desc': 'summon a ferocious grizzly bear',
				},
				'248': {
					'name': 'Fury',
					'desc': 'when in werewolf form, attack either multiple adjacent targets or one target multiple times',
				},
				'249': {
					'name': 'Armageddon',
					'desc': 'create a meteor shower to rain fiery destruction on nearby enemies',
				},
				'250': {
					'name': 'Hurricane',
					'desc': 'create a massive storm of wind and debris to pound your enemies to bits',
				},
				'251': {
					'name': 'Fire Blast',
					'desc': 'throw a fire bomb to blast your enemies to bits',
					'synergy': [
						[256, '+9%'],
						[261, '+9%'],
						[262, '+9%'],
						[271, '+9%'],
						[272, '+9%'],
						[276, '+9%'],
					],
				},
				'252': {
					'name': 'Claw Mastery',
					'desc': 'PASSIVE\nimproves your skill with claw-class weapons',
				},
				'253': {
					'name': 'Psychic Hammer',
					'desc': 'use the power of your mind to create a psychic blast to crush and knock back your enemies',
				},
				'254': {
					'name': 'Tiger Strike',
					'desc': 'CHARGE-UP SKILL\nconsecutive hits add damage bonuses to finishing moves must use a dragon finishing move or normal attack to release charges',
				},
				'255': {
					'name': 'Dragon Talon',
					'desc': 'FINISHING MOVE\nkick your enemies out of your way adds charged-up bonuses to the kick',
				},
				'256': {
					'name': 'Shock Web',
					'desc': 'throw a web of lightning to shock your enemies',
					'synergy': [
						[261, '+11%'],
						[271, '+11%'],
						[276, '+11%'],
						[251, '+1/3 Missile'],
					],
				},
				'257': {
					'name': 'Blade Sentinel',
					'desc': 'set a spinning blade to patrol between you and target point',
				},
				'258': {
					'name': 'Burst of Speed',
					'desc': 'increases attack and movement speed for a period of time',
				},
				'259': {
					'name': 'Fists of Fire',
					'desc': 'CHARGE-UP SKILL\nconsecutive hits add fire damage to finishing moves can only be used with claw-class weapons must use a dragon finishing move or normal attack to release charges',
					'synergy': [
						[280, '+12%'],
					],
				},
				'260': {
					'name': 'Dragon Claw',
					'desc': 'FINISHING MOVE\nslice and dice your enemies with your dual claw-class weapons adds charged-up bonuses to both claw attacks',
				},
				'261': {
					'name': 'Charged Bolt Sentry',
					'desc': 'a trap that emits charged bolts at enemies that pass near',
					'synergy': [
						[271, '+6%'],
						[251, '+6%'],
						[276, '+6%'],
						[271, '+1/4 Shot'],
						[256, '+1/3 Missile'],
					],
				},
				'262': {
					'name': 'Wake of Fire',
					'desc': 'a trap that emits waves of fire',
					'synergy': [
						[251, '+8%'],
						[272, '+8%'],
					],
				},
				'263': {
					'name': 'Weapon Block',
					'desc': 'PASSIVE\nchance to block when you are using dual claw-class weapons',
				},
				'264': {
					'name': 'Cloak of Shadows',
					'desc': 'cast a shadow to blind nearby enemies lowering their defenses for a period of time',
				},
				'265': {
					'name': 'Cobra Strike',
					'desc': 'CHARGE-UP SKILL\nconsecutive hits add life and mana stealing to finishing moves must use a dragon finishing move or normal attack to release charges',
				},
				'266': {
					'name': 'Blade Fury',
					'desc': 'throw spinning blades to slice up your enemies',
				},
				'267': {
					'name': 'Fade',
					'desc': 'raise all resistances and resist curses for a period of time',
				},
				'268': {
					'name': 'Shadow Warrior',
					'desc': 'summon a shadow of yourself that mimics your skills and fights by your side',
				},
				'269': {
					'name': 'Claws of Thunder',
					'desc': 'CHARGE-UP SKILL\nconsecutive hits add lightning damage to finishing moves can only be used with claw-class weapons must use a dragon finishing move or normal attack to release charges',
					'synergy': [
						[280, '+8%'],
					],
				},
				'270': {
					'name': 'Dragon Tail',
					'desc': 'FINISHING MOVE\nknock back your enemies with an explosive kick adds charged-up bonuses to the kick',
				},
				'271': {
					'name': 'Lightning Sentry',
					'desc': 'a trap that shoots lightning to scorch passing enemies',
					'synergy': [
						[256, '+12%'],
						[261, '+12%'],
						[276, '+12%'],
					],
				},
				'272': {
					'name': 'Wake of Inferno',
					'desc': 'trap that sprays fire at passing enemies',
					'synergy': [
						[251, '+10%'],
						[276, '+10%'],
						[262, '+7%'],
						[262, '+1/2 Yard'],
					],
				},
				'273': {
					'name': 'Mind Blast',
					'desc': 'using the power of your mind stun a group of enemies and convert the feeble-minded',
				},
				'274': {
					'name': 'Blades of Ice',
					'desc': 'CHARGE-UP SKILL\nconsecutive hits add cold damage to finishing moves can only be used with claw-class weapons must use a dragon finishing move or normal attack to release charges',
					'synergy': [
						[280, '+8%'],
					],
				},
				'275': {
					'name': 'Dragon Flight',
					'desc': 'FINISHING MOVE\nteleport to your enemies and destroy them with a kick adds charged-up bonuses to the kick',
				},
				'276': {
					'name': 'Death Sentry',
					'desc': 'trap that shoots lightning at your enemies or explodes nearby corpses laying waste to more enemies',
					'synergy': [
						[271, '+12%'],
						[251, '+1/3 Shot'],
					],
				},
				'277': {
					'name': 'Blade Shield',
					'desc': 'spinning blades slice enemies who stray too close',
				},
				'278': {
					'name': 'Venom',
					'desc': 'add poison damage to your weapons',
				},
				'279': {
					'name': 'Shadow Master',
					'desc': 'summon a powerful shadow of yourself to fight by your side',
				},
				'280': {
					'name': 'Phoenix Strike',
					'desc': 'CHARGE-UP SKILL\nadds elemental novas to finishing moves must use a dragon finishing move or normal attack to release charges',
					'synergy': [
						[259, '+10% Fire'],
						[269, '+13% Lightning'],
						[274, '+10% Cold'],
						[259, '+6% Avg. Fire DPS'],
					],
				}
			},
			skillMult: {
				15: 25,
				25: 25,
				41: 25,
				46: 75,
				51: 75,
				73: 25,
				83: 25,
				92: 25,
				222: 25,
				225: 75,
				230: 25,
				238: 25,
				272: 25 / 3,
				278: 25,
			},
			typeMap: {
				phy: 'Physical',
				fire: 'Fire',
				ltng: 'Lightning',
				cold: 'Cold',
				pois: 'Poison',
				stun: 'Physical',
				mag: 'Magic',
			},
			skillsLookup: {},
			builds: [],
			currentBuild: 0,
		},
		computed: {
			totalPoints () {
				return Object.keys(this.skills).reduce((total, id) => total + this.builds[this.currentBuild][id], 0);
			},
		},
		watch: {
			builds: {
				handler () {
					window.location.hash = encode(this.builds);
				},
				deep: true,
			},
		},
		methods: {
			addBuild (build = {}) {
				build.currentClass |= 0;
				build.name = build.name || '';

				Object.keys(this.skills).forEach(key => {
					build[key] |= 0;
				});

				this.builds.push(build);
				this.currentBuild = this.builds.length - 1;
			},
			delBuild (index, e) {
				e.stopPropagation();

				if (index && window.confirm('Do you wish to delete Build ' + (index + 1 + '?'))) {
					this.currentBuild = Math.min(this.currentBuild, this.builds.length - 2);
					this.builds.splice(index, 1);
				}
			},
			setReqs (id) {
				if (this.builds[this.currentBuild][id]) {
					this.skills[id].req.forEach(reqid => {
						if (this.builds[this.currentBuild][reqid] < 1) {
							this.builds[this.currentBuild][reqid]++;
						}

						this.setReqs(reqid);
					});
				}
			},
			skillCheck (id) {
				if (this.skills[id].dep.reduce((t, depid) => {
					return t + this.builds[this.currentBuild][depid];
				}, 0)) {
					this.builds[this.currentBuild][id] = clamp(1, (this.builds[this.currentBuild][id] | 0), 60);
				} else {
					this.builds[this.currentBuild][id] = clamp(0, (this.builds[this.currentBuild][id] | 0), 60);
				}

				this.setReqs(id);
			},
			skillClick (id, left, e) {
				e.preventDefault();
				e.stopPropagation();
				this.builds[this.currentBuild][id] = clamp(0, (this.builds[this.currentBuild][id] | 0) + (left ? 1 : -1), 60);
				this.skillCheck(id);
			},
			resetSkills () {
				if (this.totalPoints && window.confirm('Reset all skills for the current build?')) {
					Object.keys(this.skills).forEach(key => {
						this.builds[this.currentBuild][key] = 0;
					});
				}
			},
			renameBuild (buildIndex) {
				let ret = prompt('Enter a build name: ', this.builds[buildIndex].name || buildIndex);

				if (ret) {
					this.builds[buildIndex].name = ret;
				}
			},
			diminishedValue (lvl, a, b) {
				return (b - a) * Math.floor(110 * lvl / (lvl + 6)) / 100 + a;
			},
			getSkillValue (id, value) {
				let v = p => this.getSkillValue(id, p);

				switch (value) {
				case 'blvl':
					return this.builds[this.currentBuild][id] || 0;
				case 'lvl':
					return this.builds[this.currentBuild][id] || 0;
				case 'par1':
					return this.d2.skills[id].Param1 || 0;
				case 'par2':
					return this.d2.skills[id].Param2 || 0;
				case 'par3':
					return this.d2.skills[id].Param3 || 0;
				case 'par4':
					return this.d2.skills[id].Param4 || 0;
				case 'par5':
					return this.d2.skills[id].Param5 || 0;
				case 'par6':
					return this.d2.skills[id].Param6 || 0;
				case 'par7':
					return this.d2.skills[id].Param7 || 0;
				case 'par8':
					return this.d2.skills[id].Param8 || 0;
				case 'ln12':
					return v('par1') + (v('lvl') - 1) * v('par2');
				case 'ln34':
					return v('par3') + (v('lvl') - 1) * v('par4');
				case 'ln56':
					return v('par5') + (v('lvl') - 1) * v('par6');
				case 'ln78':
					return v('par7') + (v('lvl') - 1) * v('par8');
				case 'dm12':
					return this.diminishedValue(v('lvl'), v('par1'), v('par2')) | 0;
				case 'dm34':
					return this.diminishedValue(v('lvl'), v('par3'), v('par4')) | 0;
				case 'dm56':
					return this.diminishedValue(v('lvl'), v('par5'), v('par6')) | 0;
				case 'dm78':
					return this.diminishedValue(v('lvl'), v('par7'), v('par8')) | 0;
				case 'toht':
					return (this.d2.skills[id].ToHit || 0) + (v('lvl') - 1) * (this.d2.skills[id].LevToHit || 0);
				case 'mana':
					return Math.max((this.d2.skills[id].minmana || 0), (((this.d2.skills[id].mana || 0) + (this.d2.skills[id].lvlmana || 0) * (v('lvl') - 1)) << (this.d2.skills[id].manashift || 0)) / 256);
				default:
					debugger;
					throw new Error('[' + id + '] Unknown value: ' + value);
				}
			},
			evalSkillFormula (ast) {
				switch (ast[0]) {
				case '+':
					return this.evalSkillFormula(ast[1]) + this.evalSkillFormula(ast[2]);

				case '-':
					return this.evalSkillFormula(ast[1]) - this.evalSkillFormula(ast[2]);

				case '*':
					return this.evalSkillFormula(ast[1]) * this.evalSkillFormula(ast[2]);

				case '/':
					return this.evalSkillFormula(ast[1]) / this.evalSkillFormula(ast[2]);

				case 'key':
					return this.getSkillValue(ast[1], ast[2]);

				case 'call': {
					let params = ast.slice(2).map(v => this.evalSkillFormula(v));

					switch (ast[1]) {
					case 'skill':
						return params[0];
					case 'min':
						return Math.min(...params);
					case 'max':
						return Math.max(...params);
					default:
						throw new Error('Unknown call: ' + ast[1]);
					}
				}

				case 'value':
					return ast[1];

				default:
					throw new Error('Unknown ast node: ' + ast[0]);
				}
			},
			parseSkillFormula (formula, id) {
				while (formula[0] === '"') {
					formula = formula.slice(1);
				}

				while (formula[formula.length - 1] === '"') {
					formula = formula.slice(0, -1);
				}

				let tokens = formula.match(/'[^']+'|[a-zA-Z0-9]+|[\S]/g), app = this, pos = 0, accept, call, skillValue, number, value, parenthesis, product, addition, expression;

				accept = function (...expectations) {
					if (pos + expectations.length > tokens.length) {
						return null;
					}

					for (let c = 0; c < expectations.length; c++) {
						switch (typeof expectations[c]) {
						case 'function':
							if (!expectations[c](tokens[pos + c])) {
								return null;
							}

							break;
						case 'string':
							expectations[c] = [expectations[c]];
						case 'object':
							if (expectations[c].test) {
								if (!expectations[c].test(tokens[pos + c])) {
									return null;
								}
							} else if (expectations[c].includes) {
								if (!expectations[c].includes(tokens[pos + c])) {
									return null;
								}
							}

							break;
						default:
							return null;
						}
					}

					let ret = tokens.slice(pos, pos + expectations.length);

					pos += expectations.length;

					return ret.length === 1 ? ret[0] : ret;
				};

				call = function (name) {
					let old = pos;

					if (accept('(')) {
						let params = [], tmp = expression();

						while (tmp) {
							params.push(tmp);

							if (!accept(',')) {
								break;
							}

							tmp = expression();
						}

						if (accept(')')) {
							return ['call', name, ...params];
						}
					}

					pos = old;

					return null;
				};

				skillValue = function () {
					if (tokens[pos][0] === '\'') {
						let old = pos, skillId = +app.skillsLookup[tokens[pos++].slice(1, -1)];

						if (accept('.')) {
							let name = tokens[pos++];

							return ['key', skillId, name];
						}

						pos = old;
					}

					return null;
				};

				number = function () {
					if (/[0-9]/.test(tokens[pos][0])) {
						return ['value', +tokens[pos++]];
					}

					return null;
				};

				value = function () {
					let ret = number() || skillValue();

					if (ret) {
						return ret;
					}

					let name = tokens[pos++];

					return call(name) || ['key', id, name];
				};

				parenthesis = function () {
					let old = pos;

					if (accept('(')) {
						let ret = expression();

						if (ret && accept(')')) {
							return ret;
						}
					}

					pos = old;

					return value();
				};

				product = function () {
					let a = parenthesis(), old = pos;

					if (a) {
						let op = accept(/[*/]/);

						if (op) {
							let b = product();

							if (b) {
								return [op, a, b];
							}
						}
					}

					pos = old;

					return a;
				};

				addition = function () {
					let a = product(), old = pos;

					if (a) {
						let op = accept(/[+-]/);

						if (op) {
							let b = addition();

							if (b) {
								return [op, a, b];
							}
						}
					}

					pos = old;

					return a;
				};

				expression = function () {
					return addition();
				};

				return expression();
			},
			calculateFormula (id, formula) {
				return this.evalSkillFormula(this.parseSkillFormula(formula, id));
			},
			calculateFormulaKey (id, key) {
				if (this.d2.skills[id][key]) {
					return this.calculateFormula(id, this.d2.skills[id][key]);
				}

				return 0;
			},
			stagedDamage: function (l, a, b, c, d, e, f, hitshift = 0, mult = 1) {
				l = l || 0;
				a = a || 0;
				b = b || 0;
				c = c || 0;
				d = d || 0;
				e = e || 0;
				f = f || 0;
				hitshift = hitshift || 0;
				mult = mult || 0;

				if (l > 28) {
					a += f * (l - 28);
					l = 28;
				}

				if (l > 22) {
					a += e * (l - 22);
					l = 22;
				}

				if (l > 16) {
					a += d * (l - 16);
					l = 16;
				}

				if (l > 8) {
					a += c * (l - 8);
					l = 8;
				}

				a += b * (Math.max(0, l) - 1);

				return (mult * a) << hitshift;
			},
			skillMastery (element) {
				switch (element) {
				case 'fire':
					if (this.builds[this.currentBuild][61]) {
						return this.calculateFormulaKey(61, 'passivecalc1');
					}

					break;
				case 'ltng':
					if (this.builds[this.currentBuild][63]) {
						return this.calculateFormulaKey(63, 'passivecalc1');
					}

					break;
				default:
					return 0;
				}

				return 0;
			},
			skillPierce (element) {
				switch (element) {
				case 'cold':
					if (this.builds[this.currentBuild][65]) {
						return this.calculateFormulaKey(65, 'passivecalc1');
					}

					break;
				default:
					return 0;
				}

				return 0;
			},
			skillEffect (id, lvl) {
				let args = {}, ret = {};

				if (!this.d2.skills[id].EType && this.d2.skills[id].EMin) {
					args.min = [this.d2.skills[id].EMin, this.d2.skills[id].EMinLev1, this.d2.skills[id].EMinLev2, this.d2.skills[id].EMinLev3, this.d2.skills[id].EMinLev4, this.d2.skills[id].EMinLev5, this.d2.skills[id].HitShift, this.skillMult[id] || 1];
				}

				if (!this.d2.skills[id].EType && this.d2.skills[id].EMax) {
					args.max = [this.d2.skills[id].EMax, this.d2.skills[id].EMaxLev1, this.d2.skills[id].EMaxLev2, this.d2.skills[id].EMaxLev3, this.d2.skills[id].EMaxLev4, this.d2.skills[id].EMaxLev5, this.d2.skills[id].HitShift, this.skillMult[id] || 1];
				}

				Object.keys(args).forEach(key => {
					ret[key] = this.stagedDamage(lvl, ...args[key]) >> 8;
				});

				return ret;
			},
			skillDamage: function (id, lvl, ignoreMastery = false, args = null) {
				let ret = {};

				if (!args && this.d2.skills[id] && lvl > 0) {
					args = {};

					if ((this.d2.skills[id].MaxDam || this.d2.skills[id].MinDam) && id !== 249) {
						args.phy = args.phy || {};
						args.phy.min = [this.d2.skills[id].MinDam, this.d2.skills[id].MinLevDam1, this.d2.skills[id].MinLevDam2, this.d2.skills[id].MinLevDam3, this.d2.skills[id].MinLevDam4, this.d2.skills[id].MinLevDam5, this.d2.skills[id].HitShift, this.skillMult[id] || 1];
					}

					if ((this.d2.skills[id].MaxDam || this.d2.skills[id].MinDam) && id !== 249) {
						args.phy = args.phy || {};
						args.phy.max = [this.d2.skills[id].MaxDam, this.d2.skills[id].MaxLevDam1, this.d2.skills[id].MaxLevDam2, this.d2.skills[id].MaxLevDam3, this.d2.skills[id].MaxLevDam4, this.d2.skills[id].MaxLevDam5, this.d2.skills[id].HitShift, this.skillMult[id] || 1];
					}

					if (this.d2.skills[id].EType && this.d2.skills[id].EMin) {
						args[this.d2.skills[id].EType] = args[this.d2.skills[id].EType] || {};
						args[this.d2.skills[id].EType].min = [this.d2.skills[id].EMin, this.d2.skills[id].EMinLev1, this.d2.skills[id].EMinLev2, this.d2.skills[id].EMinLev3, this.d2.skills[id].EMinLev4, this.d2.skills[id].EMinLev5, this.d2.skills[id].HitShift, this.skillMult[id] || 1];
					}

					if (this.d2.skills[id].EType && this.d2.skills[id].EMax) {
						args[this.d2.skills[id].EType] = args[this.d2.skills[id].EType] || {};
						args[this.d2.skills[id].EType].max = [this.d2.skills[id].EMax, this.d2.skills[id].EMaxLev1, this.d2.skills[id].EMaxLev2, this.d2.skills[id].EMaxLev3, this.d2.skills[id].EMaxLev4, this.d2.skills[id].EMaxLev5, this.d2.skills[id].HitShift, this.skillMult[id] || 1];
					}
				}

				if (args) {
					let psyn = this.calculateFormulaKey(id, 'DmgSymPerCalc') / 100 + 1, esyn = this.calculateFormulaKey(id, 'EDmgSymPerCalc') / 100 + 1;

					Object.keys(args).forEach(element => {
						ret[element] = ret[element] || {};

						Object.keys(args[element]).forEach(key => {
							ret[element][key] = this.stagedDamage(lvl, ...args[element][key]);
						});
					});

					switch (id) {
					case 94:
						{
							let hfdmg = this.skillDamage(102, lvl + 7, true);

							if (this.d2.skills[id].EMin) {
								ret[this.d2.skills[id].EType].min += (hfdmg.fire.min * 256);
							}

							if (this.d2.skills[id].EMax) {
								ret[this.d2.skills[id].EType].max += (hfdmg.fire.max * 256);
							}
						}

						break;
					case 102: // holy fire
						if (this.d2.skills[id].EMin) {
							ret[this.d2.skills[id].EType].min *= 6; // weapon damage is 6x the aura damage
						}

						if (this.d2.skills[id].EMax) {
							ret[this.d2.skills[id].EType].max *= 6;
						}

						break;
					case 114: // holy freeze
						if (this.d2.skills[id].EMin) {
							ret[this.d2.skills[id].EType].min *= 5; // weapon damage is 5x the aura damage
						}

						if (this.d2.skills[id].EMax) {
							ret[this.d2.skills[id].EType].max *= 5;
						}

						break;
					case 118: // holy shock
						if (this.d2.skills[id].EMax) {
							ret[this.d2.skills[id].EType].max *= 6; // weapon damage is 6x the aura damage
						}

						break;
					//case 24: // charged strike
					//	ret[this.d2.skills[id].EType].max *= 3 + ((lvl / 5) | 0);
					case 227:
					case 237:
					case 247:
						if (this.builds[this.currentBuild][247]) {
							psyn += 0.15 + 0.10 * this.builds[this.currentBuild][247];
						}

						break;
					default:
						break;
					}

					Object.keys(ret).forEach(element => {
						Object.keys(ret[element]).forEach(key => {
							if (element === 'phy') {
								ret.phy[key] *= psyn;
							} else if (key !== 'min' || (this.d2.skills[id].EMinLev1 || this.d2.skills[id].EMinLev2 || this.d2.skills[id].EMinLev3 || this.d2.skills[id].EMinLev4 || this.d2.skills[id].EMinLev5)) {
								ret[element][key] *= esyn;
							}

							if (!ignoreMastery) {
								ret[element][key] *= 1 + this.skillMastery(element) / 100;
							}

							ret[element][key] >>= 8;
						});
					});
				}

				return ret;
			},
			skillDesc: function (id) {
				let ret = [], lvl = this.builds[this.currentBuild][id];

				let renderStagedDamage = (suffix = '') => {
					let dmg = this.skillDamage(id, lvl);

					for (let type in dmg) {
						let obj = { type, desc: (this.typeMap[type] || type) + ' damage: ' };

						if (isFinite(dmg[type].min) && isFinite(dmg[type].max)) {
							obj.desc += dmg[type].min + '-' + dmg[type].max;
						} else if (isFinite(dmg[type].min)) {
							obj.desc += dmg[type].min + ' Min';
						} else if (isFinite(dmg[type].max)) {
							obj.desc += dmg[type].max + ' Max';
						}

						if (type === 'pois') {
							obj.desc += ' / sec';
						}

						if (suffix.length) {
							obj.desc += ' ' + suffix;
						}

						ret.push(obj);
					}
				};

				if (lvl > 0) {
					switch (id) {
					// Simple Passive Chances
					case 9:
					case 13:
					case 18:
					case 29:
					case 33:
						ret.push({type: 'phy', desc: this.calculateFormulaKey(id, 'passivecalc1') + '% Chance'});
						break;

					// Simple Damage Skills
					case 10:
					case 22:
						{
							let dmg = this.calculateFormulaKey(id, 'calc1');

							if (dmg > 0) {
								ret.push({type: 'phy', desc: '+' + dmg + '% Damage'});
							} else if (dmg < 0) {
								ret.push({type: 'phy', desc: dmg + '% Damage'});
							}
						}

						break;

					case 30:
						{
							let dmg = this.calculateFormulaKey(id, 'calc2');

							if (dmg > 0) {
								ret.push({type: 'phy', desc: '+' + dmg + '% Damage'});
							} else if (dmg < 0) {
								ret.push({type: 'phy', desc: dmg + '% Damage'});
							}
						}

						break;

					// Special Cases
					case 6: // Magic Arrow
						{
							let dmg = this.skillDamage(id, lvl).phy.min;
							ret.push({type: 'mag', desc: '+' + lvl + '% Physical to Magic'});
							ret.push({type: 'phy', desc: '+' + dmg + ' Damage'});
						}

						break;
					case 7: // Fire Arrow
						ret.push({type: 'fire', desc: '+' + (1 + lvl * 2) + '% Physical to Fire'});
						renderStagedDamage();

						break;
					case 8: // Inner Sight
						ret.push({type: 'phy', desc: '-' + this.skillEffect(id, lvl).min + ' Enemy Defense'});
						break;
					case 11: // Cold Arrow
						ret.push({type: 'cold', desc: '+' + (1 + lvl * 2) + '% Physical to Cold'});
						renderStagedDamage();
						break;
					case 12: // Multiple Shot
						ret.push({type: 'phy', desc: '3/4 Weapon Damage'});
						ret.push({type: 'phy', desc: this.calculateFormulaKey(id, 'calc1') + ' Arrows'});
						break;
					case 17: // Slow Missiles
						ret.push({type: 'phy', desc: 'Slow Missiles by ' + this.calculateFormulaKey(id, 'aurastatcalc1') + '%'});
						ret.push({type: 'phy', desc: 'Duration: ' + (this.calculateFormulaKey(id, 'auralencalc') / 25) + ' Sec.'});
						ret.push({type: 'phy', desc: 'Range: ' + (Math.round(this.calculateFormulaKey(id, 'aurarangecalc') * 20 / 3) / 10) + ' Yards'});
						break;
					case 19: // Impale
						{
							ret.push({type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'calc1') + '% Damage'});
							ret.push({type: 'phy', desc: this.calculateFormulaKey(id, 'calc2') + '% Durability Loss Chance'});
						}

						break;
					case 20: // Lightning Bolt
						ret.push({type: 'phy', desc: '3/4 Weapon Damage'});
						ret.push({type: 'ltng', desc: '100% Physical to Lightning'});
						renderStagedDamage();
						break;
					case 21: // Ice Arrow
						renderStagedDamage();

						{
							let len = this.stagedDamage(lvl, this.d2.skills[id].ELen, this.d2.skills[id].ELevLen1, this.d2.skills[id].ELevLen2, this.d2.skills[id].ELevLen3, 0, 0, this.d2.skills[id].HitShift, 1);
							let syn = (1 + this.calculateFormulaKey(id, 'ELenSymPerCalc') / 100);
							len = Math.round(((len * syn) >> 8) / 2.5) / 10;
							ret.push({type: 'phy', desc: 'Freeze: ' + len + ' Sec.'});
						}

						break;
					case 31: // Freezing Arrow
						renderStagedDamage();
						ret.push({type: 'phy', desc: 'Radius: ' + (Math.round(this.calculateFormulaKey(id, 'calc1') * 20 / 3) / 10) + ' Yards'});
						ret.push({type: 'phy', desc: 'Freeze: ' + (Math.round((this.d2.skills[id].ELen * (1 + this.calculateFormulaKey(id, 'ELenSymPerCalc') / 100)) / 2.5) / 10) + ' Sec.'});
						break;
					case 23: // Penetrate
						ret.push({type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'passivecalc1') + '% Attack Rating'});
						break;
					case 24: // Charged Strike
						renderStagedDamage();
						ret.push({type: 'phy', desc: (this.calculateFormulaKey(id, 'calc1') | 0) + ' Charged Bolts'});
						break;
					case 26: // Strafe
						ret.push({type: 'phy', desc: '3/4 Weapon Damage'});
						ret.push({type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'calc2') + '% Damage'});
						ret.push({type: 'phy', desc: this.calculateFormulaKey(id, 'calc1') + ' Arrows'});
						break;
					case 28: // Decoy (Dopplezon)
						ret.push({type: 'phy', desc: 'HP: ' + Math.round(this.calculateFormulaKey(id, 'calc3') * (1 + this.calculateFormulaKey(id, 'calc1') / 100)) + '% of Caster'});
						ret.push({type: 'phy', desc: 'Resists: +' + this.calculateFormulaKey(id, 'aurastatcalc1') + '%'});
						ret.push({type: 'phy', desc: 'Duration: ' + (this.calculateFormulaKey(id, 'calc2') / 25) + ' Sec.'});
						break;
					case 32: // Valkyrie
						ret.push({type: 'phy', desc: 'HP: ' + Math.round(440 * (1 + this.calculateFormulaKey(id, 'calc1') / 100))});
						ret.push({type: 'phy', desc: 'Defense/Damage: +' + this.calculateFormulaKey(id, 'passivecalc1') + '%/+' + (this.calculateFormulaKey(id, 'aurastatcalc1') - 25) + '%'});
						ret.push({type: 'phy', desc: 'DEX/Resists: ' + this.calculateFormulaKey(id, 'aurastatcalc2') + '/' + this.calculateFormulaKey(id, 'aurastatcalc3') + '%'});
						ret.push({type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'ToHitCalc') + ' Attack Rating'});
						ret.push({type: 'phy', desc: 'iLvl: ' + this.calculateFormulaKey(id, 'calc2')});
						break;
					case 34: // Lightning Strike
						renderStagedDamage();
						ret.push({type: 'phy', desc: (this.calculateFormulaKey(id, 'calc2') | 0) + ' Hits'});
						break;
					case 35: // Lightning Fury
						renderStagedDamage();
						ret.push({type: 'phy', desc: (this.calculateFormulaKey(id, 'calc1') | 0) + ' Bolts'});
						break;
					case 58: // Energy Shield
						ret.push({type: 'phy', desc: Math.min(95, this.skillEffect(id, lvl).min) + '% Damage Absorbed'});
						break;
					case 61: // Fire mastery
						ret.push({type: 'fire', desc: '+' + this.calculateFormulaKey(id, 'passivecalc1') + '% Fire Damage'});
						break;
					case 63: // Lightning mastery
						ret.push({type: 'ltng', desc: '+' + this.calculateFormulaKey(id, 'passivecalc1') + '% Lightning Damage'});
						break;
					case 65: // Cold Mastery
						ret.push({type: 'cold', desc: '-' + this.calculateFormulaKey(id, 'passivecalc1') + '% Enemy Cold Resist'});
						break;
					case 126: // Bash
						ret.push({type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'calc1') + '% Damage'});
						ret.push({type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'calc2') + ' Damage'});
						break;
					case 254: // Tiger Strike
						ret.push({ type: 'phy', desc: [
							'Charge 1: +' + this.calculateFormula(id, 'ln12') + '% Damage',
							'Charge 2: +' + this.calculateFormula(id, 'ln12 * 2') + '% Damage',
							'Charge 3: +' + this.calculateFormula(id, 'ln12 * 3') + '% Damage',
						].join('\n') });
						break;
					case 259: // Fire Claws
						{
							let dmg = this.skillDamage(id, lvl).fire, edmg = this.skillDamage(id, lvl, false, {
								fire: {
									min: [9, 8, 15.5, 25, 34.5, 46.85, 8, 1],
									max: [15, 8, 15.5, 26.5, 37.5, 50, 8, 1],
								},
							}).fire;

							ret.push({ type: 'fire', desc: [
								'Charge 1: ' + dmg.min + '-' + dmg.max + ' Fire Damage',
								'Charge 2: 2.6 Yard Explosion',
								'Charge 3: ' + edmg.min + '-' + edmg.max + ' Fire Explosion Damage',
							].join('\n') });
						}

						break;
					case 265: // Cobra Strike

						ret.push({type: 'phy', desc: [
							'Charge 1: +' + this.calculateFormula(id, 'ln12') + '% Life Leech',
							'Charge 2: +' + this.calculateFormula(id, 'ln12') + '% Life/Mana Leech',
							'Charge 3: +' + this.calculateFormula(id, 'ln12 * 2') + '% Life/Mana Leech',
						].join('\n')});
						break;
					case 269: // Claws of Thunder
						{
							let dmg = this.skillDamage(id, lvl).ltng, ndmg = this.skillDamage(id, lvl, false, {
									ltng: {
										max: [30, 15, 25, 35, 45, 65, 8, 1],
									},
								}).ltng, bdmg = this.skillDamage(id, lvl, false, {
									ltng: {
										max: [40, 20, 40, 60, 80, 100, 8, 1],
									},
								}).ltng;

							ret.push({ type: 'ltng', desc: [
								'Charge 1: ' + dmg.min + '-' + dmg.max + ' Lightning Damage',
								'Charge 2: 1-' + ndmg.max + ' Nova Damage',
								'Charge 3: 1-' + bdmg.max + ' Charged Bolt Damage',
							].join('\n') });
						}

						break;
					case 274: // Blades of Ice
						{
							let dmg = this.skillDamage(id, lvl).cold;

							ret.push({ type: 'cold', desc: [
								'Charge 1: ' + dmg.min + '-' + dmg.max + ' Cold Damage',
								'Charge 2: 4 Yard Explosion',
								'Charge 3: ' + (Math.round(40 + 4 * (lvl - 1)) / 10) + ' Second Freeze',
							].join('\n') });
						}

						break;
					case 280: // Phoenix Strike (Royal Strike)
						{
							let dmg = this.skillDamage(id, lvl, false, {
								fire: {
									min: [20, 10, 19, 29, 38, 46, 8, 1],
									max: [40, 10, 21, 33, 42, 50, 8, 1],
								},
								ltng: {
									max: [40, 20, 40, 60, 80, 100, 8, 1],
								},
								cold: {
									min: [16, 4, 8, 12, 20, 28, 8, 1],
									max: [32, 4, 8, 13, 21, 29, 8, 1],
								}
							});

							ret.push({ type: 'fire', desc: 'Charge 1: ' + dmg.fire.min + '-' + dmg.fire.max + ' Meteor' });
							ret.push({ type: 'ltng', desc: 'Charge 2: 1-' + dmg.ltng.max + ' Chain Lightning' });
							ret.push({ type: 'cold', desc: 'Charge 2: ' + dmg.cold.min + '-' + dmg.cold.max + ' Chaos Bolt' });
						}

						break;
					default:
						renderStagedDamage();

						{
							let effect = this.skillEffect(id, lvl);

							if (Object.keys(effect).length) {
								ret.push({ type: 'phy', desc: 'Effect: ' + Object.values(effect).join('-') });
							}
						}

						break;
					}

					if (!(id === 32)) {
						if (this.d2.skills[id].ToHitCalc) {
							ret.push({ type: 'phy', desc: '+' + this.calculateFormulaKey(id, 'ToHitCalc') + '% Attack Rating' });
						} else if (isFinite(this.d2.skills[id].ToHit)) {
							ret.push({ type: 'phy', desc: '+' + this.calculateFormula(id, 'toht') + '% Attack Rating' });
						}
					}

					if (isFinite(this.d2.skills[id].mana)) {
						let mana;

						switch (id) {
						case 133:
							mana = (this.calculateFormula(id, 'mana') * 2) | 0;
							break;
						case 140:
							mana = 2;
							break;
						case 147:
							mana = 3;
							break;
						case 151:
							mana = (this.calculateFormula(id, 'mana') + 12.5) | 0;
							break;
						default:
							mana = this.calculateFormula(id, 'mana');
							break;
						}

						mana = ((mana * 10) | 0) / 10;

						ret.push({ type: 'phy', desc: 'Mana Cost: ' + mana });
					}

					if (isFinite(this.d2.skills[id].delay)) {
						ret.push({ type: 'phy', desc: 'Delay: ' + (this.d2.skills[id].delay / 25) + ' Sec.' });
					}
				}

				return ret;
			}
		},
		created: async function () {
			decode(window.location.hash.slice(1)).forEach(build => {
				this.addBuild(build);
			});

			if (!this.builds.length) {
				this.addBuild();
			}

			Object.keys(this.skills).forEach(id => {
				this.skillsLookup[this.d2.skills[id].skill] = id;
				this.skills[id].req = [];
				this.skills[id].dep = [];
			});

			Object.keys(this.skills).forEach(id => {
				[this.d2.skills[id].reqskill1, this.d2.skills[id].reqskill2].forEach(skillName => {
					if (skillName) {
						this.skills[id].req.push(this.skillsLookup[skillName]);
					}
				});

				this.skills[id].req.forEach(reqid => {
					this.skills[reqid].dep.push(id | 0);
				});
			});

			// Skill data patches - These aren't correct somehow.
			this.d2.skills[51].EDmgSymPerCalc = this.d2.skills[51].EDmgSymPerCalc.slice(1);
			this.d2.skills[26].calc1 = 'min(par3 + lvl, par4)';

			this.currentBuild = 0;
		},
	});
})();
