'use strict'; /* global Vue */

(function () {
	let data = fetch('https://raw.githubusercontent.com/blizzhackers/d2data/master/json/weapons.json');

	function first (...values) {
		return values.filter(v => v !== undefined).shift();
	}

	new Vue({
		el: '#weaponapp',
		data: {
			visible: false,
			pageTitle: 'Diablo 2 Weapon Browser',
			items: [],
			sortColumn: undefined,
			contains: '',
			levelreqlower: 0,
			levelrequpper: 99,
			tier: 0,
			sockets: 0,
			maxlevelreq: 99,
			requireonehand: false,
			requiretwohand: false,
			requiremissile: false,
			itemtype: 'All',
			dmgToolTip: 'Damage is averaged and adjusted for speed. This is not a proper dps.',
			itemtypes: {
				All: 'All',
			},
			defaults: {
				value: '??',
				headstyle: 'width:1px;user-select:none;cursor:pointer;text-align:center;',
				style: 'text-align: center;',
			},
			columns: [
				{ label: '', value: '', headstyle: 'width:auto;user-select:none;cursor:pointer;' },
				{ label: 'Item Name (code)', key: 'name', render: item => item.name + ' (' + item.code + ')', headstyle: 'width:1px;user-select:none;cursor:pointer;text-align:center;white-space:nowrap;', style: 'text-align:center;white-space:nowrap;', tooltip: 'The item name (and internal item code).' },
				{ label: 'Type', key: 'type', render: item => item.type || '??', sortDefault: '??', tooltip: 'The category this item belongs to.' },
				{ label: 'Speed', key: 'speed', render: item => item.speed || 0, sortDefault: 0, tooltip: 'Higher values mean slower weapons.' },
				{ label: 'Req Level', key: 'levelreq', render: item => item.levelreq || 0, sortDefault: 0, tooltip: 'The minimum level required to equip this item.' },
				{ label: 'Tier', key: 'tier', render: item => item.tierName, sortDefault: 0, defaultSortOrder: -1, tooltip: 'Each item has Normal, Exceptional, and Elite variants. Elite is the best.' },
				{ label: 'Sock', key: 'gemsockets', render: item => item.gemsockets || 0, sortDefault: 0, tooltip: 'The maximum number of sockets an item can possibly have.' },
				{ label: 'Req Str', key: 'reqstr', render: item => item.reqstr || 0, sortDefault: 0, tooltip: 'The minimum amount of strength required to equip this item (before modifiers).' },
				{ label: 'Req Dex', key: 'reqdex', render: item => item.reqdex || 0, sortDefault: 0, tooltip: 'The minimum amount of dexterity required to equip this item (before modifiers).' },
				{ label: 'Str Use', key: 'StrBonus', render: item => (item.StrBonus || 0) + '%', sortDefault: 0, tooltip: 'The amount that strength contributes to damage. A 75% modifier means every 100 strength is +75% damage bonus.' },
				{ label: 'Dex Use', key: 'DexBonus', render: item => (item.DexBonus || 0) + '%', sortDefault: 0, tooltip: 'The amount that dexterity contributes to damage. A 75% modifier means every 100 dexterity is +75% damage bonus.' },
				{ label: '1h Damage', key: 'dps', render: item => item.dps || '??', sortDefault: 0, defaultSortOrder: -1, tooltip: 'Damage is averaged and adjusted for speed. This is not a proper dps.' },
				{ label: '2h Damage', key: '2handdps', render: item => item['2handdps'] || '??', sortDefault: 0, defaultSortOrder: -1, tooltip: 'Damage is averaged and adjusted for speed. This is not a proper dps.' },
				{ label: 'Rng Damage', key: 'misdps', render: item => item.misdps || '??', sortDefault: 0, defaultSortOrder: -1, tooltip: 'Damage is averaged and adjusted for speed. This is not a proper dps.' },
				{ label: '', value: '', headstyle: 'width:auto;user-select:none;cursor:pointer;' },
			]
		},
		methods: {
			sort: function (column) {
				if (this.sortColumn === column) {
					column.sortOrder = -column.sortOrder;
				} else {
					if (this.sortColumn) {
						delete this.sortColumn.headclass;
					}

					this.sortColumn = column;
					column.sortOrder = column.sortOrder || column.defaultSortOrder || 1;
				}

				column.headclass = column.sortOrder > 0 ? 'text-primary' : 'text-danger';

				this.item = this.items.sort((a, b) => {
					let av = first(column.value, a[column.key], column.sortDefault);
					let bv = first(column.value, b[column.key], column.sortDefault);
					let ret = av < bv ? -column.sortOrder : av > bv ? column.sortOrder : 0;

					return ret;
				});
			},
			resetValues: function () {
				this.contains = '';
				this.levelreqlower = 0;
				this.levelrequpper = this.maxlevelreq;
				this.sockets = 0;
				this.tier = 0;
				this.itemtype = 'All';
				this.requireonehand = false;
				this.requiretwohand = false;
				this.requiremissile = false;
			},
			canShow: function (item) {
				if (item.name.toLowerCase().indexOf(this.contains.toLowerCase()) < 0) {
					return false;
				}

				if (+this.levelreqlower && +item.levelreq < +this.levelreqlower) {
					return false;
				}

				if (+this.levelrequpper && +item.levelreq > +this.levelrequpper) {
					return false;
				}

				if (+this.tier && +item.tier !== +this.tier) {
					return false;
				}

				if (this.itemtype !== 'All' && this.itemtype !== item.type) {
					return false;
				}

				if (this.sockets && (item.gemsockets || 0) < this.sockets) {
					return false;
				}

				if (this.requireonehand && !item.dps) {
					return false;
				}

				if (this.requiretwohand && !item['2handdps']) {
					return false;
				}

				if (this.requiremissile && !item.misdps) {
					return false;
				}

				return true;
			},
			first,
		},
		created: async function () {
			data = await data;
			data = await data.json();
			this.items = Object.values(data).map(v => {
				v.speed = v.speed || 0;
				v.avgdam = (v.mindam + v.maxdam) / 2 || 0;
				v.dps = v.avgdam * (100 - v.speed) / 100 || 0;
				v['2handavgdam'] = (v['2handmindam'] + v['2handmaxdam']) / 2 || 0;
				v['2handdps'] = v['2handavgdam'] * (100 - v.speed) / 100 || 0;
				v.avgmisdam = (v.minmisdam + v.maxmisdam) / 2 || 0;
				v.misdps = v.avgmisdam * (100 - v.speed) / 100 || 0;
				v.levelreq = v.levelreq || 0;
				v.tier = v.code === v.ultracode ? 3 : v.code === v.ubercode ? 2 : 1;
				v.tierName = ['None', 'Norm', 'Excep', 'Elite'][v.tier];
				this.itemtypes[v.type || 'none'] = v.type || 'none';

				return v;
			}).filter(i => i.spawnable);
			this.visible = true;
		},
	});
})();
