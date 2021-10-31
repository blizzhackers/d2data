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

[
    [require('./json/TreasureClass.json'), './json/CalcTc.json'],
    [require('./json/TreasureClassEx.json'), './json/CalcTcEx.json'],
].forEach(([treasureClass, destinationFile]) => {
    const atomic = JSON.parse(JSON.stringify(require('./json/atomic.json')));
    const itemTypes = require('./json/ItemTypes.json');
    const fs = require('fs');
    
    const items = Object.assign(
        require('./json/weapons.json'),
        require('./json/armor.json'),
        require('./json/misc.json')
    );
        
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
                return total + (items[code].type && itemTypes[items[code].type] && itemTypes[items[code].type].Rarity ? itemTypes[items[code].type].Rarity : 1);
            }, 0),
            ret = {};
        
        for(let code of itemlist) {
            ret[code] = mult * itemTypes[items[code].type].Rarity / total;
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
    
    const calcTc = {};
    
    [
        ...Object.keys(treasureClass),
        ...Object.keys(atomic),
    ].sort().forEach(key => {
        calcTc[key] = getTC(key, 1);
    });
    
    delete calcTc.Gold;
    
    fs.writeFileSync(destinationFile, JSON.stringify(calcTc, null, ' '));
});
