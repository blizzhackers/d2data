#!/usr/bin/env bash
set -euo pipefail

workspace_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
txt_dir="$workspace_dir/txt"
base_dir="$txt_dir/base"
tbl_dir="$workspace_dir/tbl"
json_dir="$workspace_dir/json"

tbl_locales=(chi deu eng esp fra ita kor pol)
all_locales=(chi deu eng esp fra ita jpn kor pol)

if [[ ! -d "$txt_dir" || ! -d "$base_dir" ]]; then
    printf 'Expected txt directories were not found under %s\n' "$workspace_dir" >&2
    exit 1
fi

if [[ ! -d "$tbl_dir" || ! -d "$tbl_dir/strings" || ! -f "$workspace_dir/string.js" ]]; then
    printf 'Expected tbl/string assets were not found under %s\n' "$workspace_dir" >&2
    exit 1
fi

cascconsole_cmd="$(command -v cascconsole || true)"
if [[ -z "$cascconsole_cmd" ]]; then
    printf 'cascconsole was not found on PATH\n' >&2
    exit 1
fi

stage_dir="$(mktemp -d /tmp/d2r-data-download.XXXXXX)"
trap 'rm -rf -- "$stage_dir"' EXIT

node_cmd="$(command -v node || true)"
if [[ -z "$node_cmd" ]]; then
    printf 'node was not found on PATH\n' >&2
    exit 1
fi

run_casc() {
    (
        cd -- "$stage_dir"
        "$cascconsole_cmd" "$@"
    )
}

printf 'Downloading D2R Excel files with %s...\n' "$cascconsole_cmd"
run_casc \
    --mode Pattern \
    --online \
    --eparam 'data/data/global/excel/*.txt' \
    --dest "$stage_dir" \
    --locale enUS \
    --product osi

printf 'Downloading D2R locale tables...\n'
run_casc \
    --mode Pattern \
    --online \
    --eparam 'data/data/local/lng/*/*.tbl' \
    --dest "$stage_dir" \
    --locale All \
    --product osi

printf 'Downloading D2R terms-of-service files...\n'
run_casc \
    --mode Pattern \
    --online \
    --eparam 'data/data/local/lng/*/termsofservice.txt' \
    --dest "$stage_dir" \
    --locale All \
    --product osi

source_root="$stage_dir/data/data/global/excel"
if [[ ! -d "$source_root" || ! -d "$source_root/base" ]]; then
    printf 'CASC extraction did not produce the expected Excel directories\n' >&2
    exit 1
fi

mapfile -t root_files < <(find "$source_root" -maxdepth 1 -type f -name '*.txt' -print | sort)
mapfile -t base_files < <(find "$source_root/base" -maxdepth 1 -type f -name '*.txt' -print | sort)
source_lng="$stage_dir/data/data/local/lng"

for locale in "${all_locales[@]}"; do
    if [[ ! -s "$source_lng/$locale/termsofservice.txt" ]]; then
        printf 'Missing termsofservice.txt for locale %s\n' "$locale" >&2
        exit 1
    fi
done

for locale in "${tbl_locales[@]}"; do
    for table in string.tbl expansionstring.tbl patchstring.tbl; do
        if [[ ! -s "$source_lng/$locale/$table" ]]; then
            printf 'Missing %s for locale %s\n' "$table" "$locale" >&2
            exit 1
        fi
    done
done

mapfile -t tbl_files < <(find "$source_lng" -mindepth 2 -maxdepth 2 -type f -name '*.tbl' -print | sort)
mapfile -t terms_files < <(find "$source_lng" -mindepth 2 -maxdepth 2 -type f -name 'termsofservice.txt' -print | sort)

if (( ${#root_files[@]} == 0 || ${#base_files[@]} == 0 )); then
    printf 'CASC extraction produced no usable Excel files\n' >&2
    exit 1
fi

if (( ${#tbl_files[@]} == 0 || ${#terms_files[@]} == 0 )); then
    printf 'CASC extraction produced no usable locale files\n' >&2
    exit 1
fi

printf 'Replacing %d root files and %d base files...\n' "${#root_files[@]}" "${#base_files[@]}"
find "$txt_dir" -maxdepth 1 -type f -name '*.txt' -delete
find "$base_dir" -maxdepth 1 -type f -name '*.txt' -delete
cp -- "${root_files[@]}" "$txt_dir/"
cp -- "${base_files[@]}" "$base_dir/"

printf 'Replacing %d locale tables and %d terms-of-service files...\n' \
    "${#tbl_files[@]}" "${#terms_files[@]}"
for locale in "${all_locales[@]}"; do
    target_locale="$tbl_dir/$locale"
    mkdir -p "$target_locale"
    find "$target_locale" -maxdepth 1 -type f \( -name '*.tbl' -o -name 'termsofservice.txt' \) -delete
    cp -- "$source_lng/$locale/termsofservice.txt" "$target_locale/"
done
for locale in "${tbl_locales[@]}"; do
    target_locale="$tbl_dir/$locale"
    cp -- \
        "$source_lng/$locale/string.tbl" \
        "$source_lng/$locale/expansionstring.tbl" \
        "$source_lng/$locale/patchstring.tbl" \
        "$target_locale/"
done

printf 'Regenerating JSON string maps with string.js...\n'
(
    cd -- "$workspace_dir"
    "$node_cmd" string.js
)

json_files=("$json_dir/allstrings-eng.json")
for locale in "${tbl_locales[@]}"; do
    json_files+=("$json_dir/localestrings-$locale.json")
done
for json_file in "${json_files[@]}"; do
    if [[ ! -s "$json_file" ]]; then
        printf 'Expected generated JSON file is missing or empty: %s\n' "$json_file" >&2
        exit 1
    fi
done

installed_root_count="$(find "$txt_dir" -maxdepth 1 -type f -name '*.txt' | wc -l)"
installed_base_count="$(find "$base_dir" -maxdepth 1 -type f -name '*.txt' | wc -l)"
installed_tbl_count="$(find "$tbl_dir" -mindepth 2 -maxdepth 2 -type f -name '*.tbl' | wc -l)"
installed_terms_count="$(find "$tbl_dir" -mindepth 2 -maxdepth 2 -type f -name 'termsofservice.txt' | wc -l)"
if (( installed_root_count != ${#root_files[@]} || installed_base_count != ${#base_files[@]} )); then
    printf 'Installed file counts do not match the downloaded file counts\n' >&2
    exit 1
fi
if (( installed_tbl_count != ${#tbl_files[@]} || installed_terms_count != ${#terms_files[@]} )); then
    printf 'Installed locale file counts do not match the downloaded file counts\n' >&2
    exit 1
fi

printf 'Done: %d root files, %d base files, %d tables, and %d terms files installed\n' \
    "$installed_root_count" "$installed_base_count" "$installed_tbl_count" "$installed_terms_count"
