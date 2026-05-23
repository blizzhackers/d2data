<?php

declare(strict_types=1);

/**
 * @file
 * Walk and flatten a TC tree, including unique/set/rare/magic factors.
 */

chdir(realpath(__DIR__));

// enable immediate flush
while (ob_get_level()) {
  ob_end_flush();
}

ob_implicit_flush(true);

define('TREASURECLASSEX', json_decode(file_get_contents('json/treasureclassex.json'), TRUE));
define('TREASURECLASSEXBASE', json_decode(file_get_contents('json/base/treasureclassex.json'), TRUE));

foreach ([
  'json/precalctc/' => [TREASURECLASSEX, 'dropsolver'],
  'json/base/precalctc/' => [TREASURECLASSEXBASE, 'dropsolverbase'],
] as $basepath => [$treasureclassex, $simulator]) {
  print("Generating $basepath\n");

  $index = [];

  $tccount = 0;
  $tcmax = count($treasureclassex) * 48;

  foreach ($treasureclassex as $tc_name => $tc) {
    $filename = preg_replace('/[^a-z0-9() -_]\+/i', '_', $tc_name);
    $filename = trim($filename, '_- ');
    $index[$tc_name] = $filename . ".json";
    $filepath = $basepath . $filename . ".json";

    if (file_exists($filepath)) {
      $tccount += 48;
      continue;
    }

    $precalc = [];

    foreach ([0, 1, 2] as $difficulty) {
      foreach ([0, 1] as $desecrated) {
        foreach ([1, 2, 3, 4, 5, 6, 7, 8] as $dropmodifier) {
          $tcindex = $tccount++;
          $tc_name_escaped = escapeshellarg($tc_name);
          $tcpercent = number_format($tcindex / $tcmax * 100, 2);
          print("[$tcpercent%] $tc_name [$dropmodifier][" . ($desecrated ? 'desecrated' : 'normal') . "]..." . PHP_EOL);
          $start = microtime(true);
          $result = shell_exec("./$simulator $tc_name_escaped $dropmodifier 0 $difficulty 1 $desecrated");
          $elapsed = (microtime(true) - $start);
    
          if (!$result) {
            throw new Exception("Simulation failed for $tc_name with drop modifier $dropmodifier");
          }
    
          $data = json_decode($result, TRUE);
    
          if ($data['tc'] !== $tc_name) {
            throw new Exception("Expected TC $tc_name but got " . $data['tc']);
          }
    
          $playermod = $data['playermod'] - 1;
    
          $precalc[$difficulty][$desecrated][$playermod] = $data['drops'];
    
          usort($precalc[$difficulty][$desecrated][$playermod], fn ($a, $b) => $b[1] <=> $a[1]);
    
          print(PHP_EOL);
        }
      }
    }

    if ($precalc) {
      file_put_contents($filepath, json_encode($precalc, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE));
    }
  }

  if ($index) {
    file_put_contents($basepath . '_index.json', json_encode($index, JSON_PRETTY_PRINT));

    $module = '';
    $module_map = [];

    $i = 1;

    foreach ($index as $tc_name => $filename) {
      $variable = $module_map[$tc_name] = "json$i";
      $module .= "import $variable from './$filename' with { type: 'json' };\n";
      $i++;
    }

    $module .= "\nexport default {\n";

    foreach ($module_map as $tc_name => $variable) {
      $module .= "  '$tc_name': $variable,\n";
    }

    $module .= "}\n";

    file_put_contents($basepath . '_all.mjs', $module);
  }
}
