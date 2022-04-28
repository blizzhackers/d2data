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
        discardGarbage(fs.readFileSync('tbl/' + lang + '/string.tbl').toString().split('\0')),
        discardGarbage(fs.readFileSync('tbl/' + lang + '/expansionstring.tbl').toString().split('\0')),
        discardGarbage(fs.readFileSync('tbl/' + lang + '/patchstring.tbl').toString().split('\0')),
    ].forEach(lines => {
        while (lines.length) {
            let key = lines.shift(), str = lines.shift();
    
            if (key.trim().length) {
                strings[key.trim()] = str;
            }    
        }
    });
    
    fs.writeFileSync('./json/localestrings-' + lang + '.json', JSON.stringify(strings, null, ' '));
});
