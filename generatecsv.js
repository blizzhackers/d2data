const monpopulationest = require('./json/monpopulationest.json');
const superuniques = require('./json/superuniques.json');
const monstats = require('./json/monstats.json');
const levels = require('./json/levels.json');
const localestrings = require('./json/localestrings-eng.json');
const fs = require('fs');

let diffs = ['', '(N)', '(H)'];

for (let diff in diffs) {
  let rows = [
    [
      'Name',
      'Difficulty',
      'Is Super?',
      'Is Boss?',
      'Area Level',
      'Base Monster Level',
      'Actual Monster Level',
      'Area',
      'Area ID',
    ],
  ];
    
  let diffstr = diffs[diff];

  function addRow(level, mlvls, mon, sup) {
    rows[rows.length] = [
      localestrings[sup ? sup.Name : mon.NameStr],
      ['normal', 'nightmare', 'hell'][diff],
      sup ? 'yes' : 'no',
      mon.boss ? 'yes' : 'no',
      level['MonLvlEx' + diffstr],
      mon['Level' + diffstr],
      mlvls[diff],
      localestrings[level.LevelName],
      level.Id,
    ];  
  }

  for (let levelId in monpopulationest) {
    let pop = monpopulationest[levelId];
    let level = levels[levelId];
  
    for (let superid in pop['superunique']) {
      addRow(level, [
        pop['superunique'][superid]['mlvl'],
        pop['superunique'][superid]['mlvl(N)'],
        pop['superunique'][superid]['mlvl(H)'],
      ], monstats[superuniques[superid].Class], superuniques[superid]);
    }
  
    for (let monid in pop['boss']) {
      addRow(level, [
        pop['boss'][monid]['mlvl'],
        pop['boss'][monid]['mlvl(N)'],
        pop['boss'][monid]['mlvl(H)'],
      ], monstats[monid]);
    }
  }

  let data = rows.map(row => row.map(col => JSON.stringify(col)).join(',')).join('\n');
  fs.writeFileSync(['superboss_normal.csv', 'superboss_nightmare.csv', 'superboss_hell.csv'][diff], data);
}
