#!/usr/bin/env bash
set -euo pipefail

./download.sh
bun compile.js
bun string.js
bun generatecsv.js
php generateheaders.php
./build.sh
rm json/precalctc/*.json
rm json/base/precalctc/*.json
php precalctc.php
