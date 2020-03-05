'use strict'; /* global Vue */

(function () {
	let data = fetch('https://raw.githubusercontent.com/blizzhackers/d2data/master/json/armor.json');

	function first (...values) {
		return values.filter(v => v !== undefined).shift();
	}

	new Vue({
		el: '#armorapp',
		data: {
			visible: false,
			pageTitle: 'Diablo 2 Armor Browser',
			items: [],
			sortColumn: undefined,
			contains: '',
			levelreqlower: 0,
			levelrequpper: 99,
			tier: 0,
			sockets: 0,
			weight: -1,
			maxstrreq: 0,
			maxstrreqmax: 0,
			maxlevelreq: 99,
			itemtype: 'All',
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
				{ label: 'Req Level', key: 'levelreq', render: item => item.levelreq || 0, sortDefault: 0, tooltip: 'The minimum level required to equip this item.' },
				{ label: 'Tier', key: 'tier', render: item => item.tierName, sortDefault: 0, defaultSortOrder: -1, tooltip: 'Each item has Normal, Exceptional, and Elite variants. Elite is the best.' },
				{ label: 'Sock', key: 'gemsockets', render: item => item.gemsockets || 0, sortDefault: 0, tooltip: 'The maximum number of sockets an item can possibly have.' },
				{ label: 'Max AC', key: 'maxac', render: item => item.maxac || 0, sortDefault: 0, tooltip: 'The maximum amount of armor class an item can possibly have.' },
				{ label: 'Weight', key: 'speed', render: item => item.weightClass, sortDefault: 0, tooltip: 'The weight of the armor. Medium has a run speed penalty, and Heavy has even more.' },
				{ label: 'Req Str', key: 'reqstr', render: item => item.reqstr || 0, sortDefault: 0, tooltip: 'The minimum amount of strength required to equip this item (before modifiers).' },
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
				this.weight = -1;
				this.maxstrreq = this.maxstrreqmax;
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

				if (+this.weight >= 0 && +(item.speed || 0) !== +this.weight) {
					return false;
				}

				if ((item.reqstr || 0) > this.maxstrreq) {
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
				v.levelreq = v.levelreq || 0;
				v.weightClass = v.speed === 10 ? 'Heavy' : v.speed === 5 ? 'Medium' : 'Light';
				v.tier = v.code === v.ultracode ? 3 : v.code === v.ubercode ? 2 : 1;
				v.tierName = ['None', 'Norm', 'Excep', 'Elite'][v.tier];
				this.maxstrreq = this.maxstrreqmax = Math.max(this.maxstrreqmax, v.reqstr || 0);
				this.itemtypes[v.type || 'none'] = v.type || 'none';

				return v;
			}).filter(i => i.spawnable);
			this.visible = true;
		},
	});
})();
