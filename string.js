const fs = require('fs');

function discardGarbage(lines) {
    while (lines.length && ![
        'A4Q2ExpansionSuccessTyrael',
        'Cutthroat1',
        'WarrivAct1IntroGossip1',
    ].includes(lines[0])) {
        lines.shift();
    }

    return lines;
}

[
    'chi',
    'deu',
    'eng',
    'esp',
    'fra',
    'ita',
    'kor',
    'pol',
].forEach(lang => {
    let strings = {};

    [
      'string.tbl',
      'expansionstring.tbl',
      'patchstring.tbl',
    ].forEach(name => {
      console.log('Processing: ', lang, name);

      let lines = discardGarbage(fs.readFileSync('tbl/' + lang + '/' + name).toString().split('\0'));

      while (lines.length) {
            let key = lines.shift(), str = lines.shift();
    
            if (key.trim().length) {
                strings[key.trim()] = str;
            }    
        }
    });
    
    fs.writeFileSync('./json/localestrings-' + lang + '.json', JSON.stringify(strings, null, ' '));
});
