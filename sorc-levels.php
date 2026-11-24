#!/usr/bin/env php
<?php

/**
 * @file
 * Best sorceress build at each level, as a markdown table.
 *
 * Each level() line runs sorcbuild for one character level and adds a row.
 * Edit a line's options to tune that level: bonus skills from gear, quest
 * skill points, required skills, or any other sorcbuild option (see
 * sorcbuild.md). Each level's build is passed on as the next level's --prev,
 * except at the RESPEC levels; a line can still set its own --prev. Options in COMMON apply to every
 * level; a line's own options override them. A TRUE value passes a bare flag.
 * Builds are ranked by experience per second; add '--epm' => TRUE to COMMON to
 * rank by experience per mana instead. Areas are gated by the Ancients (levels
 * 20/40/60); add '--rush' => TRUE to consider every area. Add
 * '--progression' => TRUE to choose builds by how fast they clear progression.
 *
 * Usage: php sorc-levels.php > sorc-levels.md
 */

const COMMON = ['--players' => 1];

// Areas listed per level, best first.
const TOP_AREAS = 3;

// Each level grows from the previous level's build (passed as --prev), except
// at these levels, which start fresh: the respecs. A line's own --prev wins.
const RESPEC = [20, 40, 79];

// Rows collected by level(), printed as one table when the script ends, so
// the columns can follow every line's options.
$rows = [];
register_shutdown_function('print_table');

/**
 * Runs sorcbuild for one level and keeps its row for the table.
 */
function level(int $level, array $options = []) : void {
  global $rows;
  // The last build made, for the next level to grow from.
  static $previous = NULL;
  $all = array_merge(COMMON, $options);
  if (in_array($level, RESPEC, TRUE)) {
    $previous = NULL;
  }
  if ($previous !== NULL && !array_key_exists('--prev', $all)) {
    $all['--prev'] = $previous;
  }
  $row = [
    'level' => $level,
    'epm' => !empty($all['--epm']),
    'rush' => !empty($all['--rush']),
    'progression' => !empty($all['--progression']) || !empty($all['--hybrid']),
    'cells' => ['', '', '', '', ''],
    'clear' => '',
    'build' => '',
  ];

  $args = [__DIR__ . '/sorcbuild', (string) $level, '--top', (string) TOP_AREAS];
  foreach ($all as $flag => $value) {
    if ($value === TRUE) {
      $args[] = $flag;
    }
    elseif ($value !== FALSE && $value !== NULL) {
      $args[] = $flag;
      $args[] = (string) $value;
    }
  }

  $process = proc_open($args, [1 => ['pipe', 'w'], 2 => ['pipe', 'w']], $pipes);
  $stdout = stream_get_contents($pipes[1]);
  $stderr = stream_get_contents($pipes[2]);
  fclose($pipes[1]);
  fclose($pipes[2]);
  $status = proc_close($process);

  $result = $status === 0 ? json_decode($stdout, TRUE) : NULL;
  if ($result === NULL) {
    $error = trim($stderr) ?: 'sorcbuild failed';
    fwrite(STDERR, "Level $level: $error\n");
    $row['cells'][0] = 'error: ' . $error;
    $rows[] = $row;
    return;
  }
  foreach ($result['warnings'] as $warning) {
    fwrite(STDERR, "Level $level: $warning\n");
  }

  $build = $result['builds'][0] ?? NULL;
  if ($build === NULL) {
    $row['cells'][0] = 'none';
    $rows[] = $row;
    return;
  }
  $perSecond = $result['objective'] === 'expPerSecond';
  $areas = [];
  foreach ($build['areas'] as $area) {
    $rate = $perSecond ? compact_number($area['expPerSecond']) . '/s' : number_format($area['expPerMana'], 2, '.', '') . '/mana';
    $areas[] = "{$area['name']} (A{$area['act']}), {$area['difficulty']} ({$area['areaLevel']}): $rate";
  }
  $row['cells'] = [
    $build['skill'],
    $perSecond ? compact_number($build['expPerSecond']) : number_format($build['expPerMana'], 2, '.', ''),
    implode('<br>', $areas),
    $result['expToNext'] <= 0 ? '' : ($perSecond ? duration($build['secondsToNext']) : compact_number($build['manaToNext'])),
  ];
  $row['clear'] = $row['progression'] ? duration($build['progressionSeconds']) : '';
  $row['build'] = build_text($build);
  $previous = $row['build'];
  $rows[] = $row;
}

/**
 * Prints the collected rows as one markdown table.
 */
function print_table() : void {
  global $rows;
  if (!$rows) {
    return;
  }
  $epm = $rows[0]['epm'];
  $objective = $epm ? 'experience per mana' : 'experience per second (casting plus travel)';
  $progressionLevels = array_column(array_filter($rows, fn ($r) => $r['progression']), 'level');
  $anyProgression = (bool) $progressionLevels;

  echo "# Sorceress builds by level\n\n";
  if (!$anyProgression) {
    echo "Best build at each level by $objective.";
  }
  elseif (count($progressionLevels) === count($rows)) {
    echo "Builds are chosen by how fast they clear progression (Travincal's Council, Chaos Sanctuary, the Throne), then judged by $objective.";
  }
  else {
    echo "Best build at each level by $objective. Rows with a progression clear time were instead chosen by how fast they clear progression (Travincal's Council, Chaos Sanctuary, the Throne).";
  }
  echo $rows[0]['rush']
    ? " All areas count as open (rushed).\n\n"
    : " Areas past the Ancients (and the next difficulty) open at levels 20, 40 and 60.\n\n";

  $header = ['Lvl', 'Main skill', $epm ? 'exp/mana' : 'exp/s', 'Top areas', $epm ? 'Mana to level' : 'Time to level'];
  $align = ['-:', '-', '-:', '-', '-:'];
  if ($anyProgression) {
    $header[] = 'Progression clear';
    $align[] = '-:';
  }
  $header[] = 'Build';
  $align[] = '-';
  echo '| ' . implode(' | ', $header) . " |\n";
  echo '|' . implode('|', $align) . "|\n";
  foreach ($rows as $r) {
    $cells = array_merge([$r['level']], $r['cells']);
    if ($anyProgression) {
      $cells[] = $r['clear'];
    }
    $cells[] = $r['build'];
    echo '| ' . implode(' | ', $cells) . " |\n";
  }
}

/**
 * 3725 -> "1h 2m", 95 -> "1m 35s".
 */
function duration(float $seconds) : string {
  $s = (int) round($seconds);
  if ($s >= 3600) {
    return intdiv($s, 3600) . 'h ' . intdiv($s % 3600, 60) . 'm';
  }
  if ($s >= 60) {
    return intdiv($s, 60) . 'm ' . ($s % 60) . 's';
  }
  return $s . 's';
}

/**
 * "Fire Wall 13, Warmth 13 (14); 2 unspent", the format --prev accepts.
 */
function build_text(array $build) : string {
  // Most hard points first; ties keep sorcbuild's order (main skills first).
  $allocation = $build['allocation'];
  usort($allocation, fn ($a, $b) => $b['points'] <=> $a['points']);
  $parts = [];
  foreach ($allocation as $skill) {
    $parts[] = "{$skill['skill']} {$skill['points']}" . ($skill['level'] !== $skill['points'] ? " ({$skill['level']})" : '');
  }
  return implode(', ', $parts) . ($build['unspent'] > 0 ? "; {$build['unspent']} unspent" : '');
}

/**
 * 1234567 -> "1.23M".
 */
function compact_number(float $value) : string {
  $abs = abs($value);
  if ($abs >= 1e9) {
    return number_format($value / 1e9, 2, '.', '') . 'B';
  }
  if ($abs >= 1e6) {
    return number_format($value / 1e6, 2, '.', '') . 'M';
  }
  if ($abs >= 1e4) {
    return number_format($value / 1e3, 1, '.', '') . 'k';
  }
  return number_format($value, $abs < 10 ? 2 : ($abs < 100 ? 1 : 0), '.', '');
}

level(2,  ['--quest-skills' => 0, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0]);
level(3,  ['--quest-skills' => 1, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0]);
level(4,  ['--quest-skills' => 1, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0]);
level(5,  ['--quest-skills' => 1, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0]);
level(6,  ['--quest-skills' => 1, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(7,  ['--quest-skills' => 1, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(8,  ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(9,  ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(10, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(11, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(12, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(13, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(14, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(15, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(16, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova']);
level(17, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova,Telekinesis']);
level(18, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova,Telekinesis,Teleport']);
level(19, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--require' => 'Frost Nova,Telekinesis,Teleport']);
level(20, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(21, ['--quest-skills' => 2, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(22, ['--quest-skills' => 4, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(23, ['--quest-skills' => 4, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(24, ['--quest-skills' => 4, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(25, ['--quest-skills' => 6, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(26, ['--quest-skills' => 6, '--skills' => 0, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(27, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(28, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(29, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(30, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(31, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(32, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(33, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(34, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(35, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(36, ['--quest-skills' => 6, '--skills' => 1, '--fire-skills' => 3, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(37, ['--quest-skills' => 6, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(38, ['--quest-skills' => 6, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(39, ['--quest-skills' => 6, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(40, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(41, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(42, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(43, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(44, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(45, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(46, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(47, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(48, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(49, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(50, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(51, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(52, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(53, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(54, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(55, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(56, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(57, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(58, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(59, ['--quest-skills' => 10, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(60, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(61, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(62, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(63, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(64, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(65, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(66, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(67, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(68, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(69, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(70, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(71, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(72, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(73, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(74, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(75, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(76, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(77, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(78, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(79, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(80, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(81, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(82, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(83, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(84, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(85, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(86, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(87, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(88, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(89, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(90, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(91, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(92, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(93, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(94, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(95, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(96, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(97, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
level(98, ['--quest-skills' => 12, '--skills' => 4, '--fire-skills' => 0, '--cold-skills' => 0, '--lightning-skills' => 0, '--progression' => TRUE, '--require' => 'Frost Nova,Static Field,Telekinesis,Teleport']);
