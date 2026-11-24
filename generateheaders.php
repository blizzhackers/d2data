<?php

/**
 * @file
 * Generate header files for all TXT files in the txt/ directory.
 */

function cid(string $name, string $altname, bool $pascalcase = TRUE) : string {
  $newname = trim(preg_replace('/[^a-z0-9_ ]+/i', ' ', $name), ' ');
  $newname = $pascalcase && str_contains($newname, ' ') ? ucwords($newname) : $newname;
  $newname = str_replace(' ', '', $newname);

  if (!$newname) {
    $newname = "$altname";
  }

  if (is_numeric($newname[0]) || in_array($newname, [
    // C++ reserved keywords.
    'alignas',
    'alignof',
    'and',
    'and_eq',
    'asm',
    'auto',
    'bitand',
    'bitor',
    'bool',
    'break',
    'case',
    'catch',
    'char',
    'char8_t',
    'char16_t',
    'char32_t',
    'class',
    'compl',
    'concept',
    'const',
    'const_cast',
    'consteval',
    'constexpr',
    'constinit',
    'continue',
    'co_await',
    'co_return',
    'co_yield',
    'decltype',
    'default',
    'delete',
    'do',
    'double',
    'dynamic_cast',
    'else',
    'enum',
    'explicit',
    'export',
    'extern',
    'false',
    'float',
    'for',
    'friend',
    'goto',
    'if',
    'inline',
    'int',
    'long',
    'mutable',
    'namespace',
    'new',
    'noexcept',
    'not',
    'not_eq',
    'nullptr',
    'operator',
    'or',
    'or_eq',
    'private',
    'protected',
    'public',
    'register',
    'reinterpret_cast',
    'requires',
    'return',
    'short',
    'signed',
    'sizeof',
    'static',
    'static_assert',
    'static_cast',
    'struct',
    'switch',
    'template',
    'this',
    'thread_local',
    'throw',
    'true',
    'try',
    'typedef',
    'typeid',
    'typename',
    'union',
    'unsigned',
    'using',
    'virtual',
    'void',
    'volatile',
    'wchar_t',
    'while',
    'xor_eq',
  ])) {
    $newname = "_$newname";
  }

  return $newname;
}


/**
 * Infer the narrowest C++ type that can hold a raw cell value.
 */
function celltype(string $value) : string {
  if ($value === '') {
    return 'void';
  }

  if (preg_match('/^\s*[+-]?0*(\d+)\s*$/', $value, $matches)) {
    // Longer than 18 digits can't be range checked safely as a PHP int.
    if (strlen($matches[1]) > 18) {
      return 'std::string';
    }

    $int = (int) trim($value);
    return $int >= -2147483648 && $int <= 2147483647 ? 'int32_t' : 'int64_t';
  }

  return is_numeric($value) ? 'double' : 'std::string';
}

/**
 * Widen a column type so it can also hold another type.
 */
function widentype(string $a, string $b) : string {
  $rank = ['void' => 0, 'int32_t' => 1, 'int64_t' => 2, 'double' => 3, 'std::string' => 4];
  return $rank[$a] >= $rank[$b] ? $a : $b;
}

foreach ([
  ['ROTW', 'txtrotw', 'txt/*.txt'],
  ['BASE', 'txtbase', 'txt/base/*.txt'],
] as [$namespace, $filebase, $path]) {
  $typedefs = [];

  foreach (glob(__DIR__ . '/' . $path) as $i => $file) {
    $name = cid(basename($file, '.txt'), "txt_$i");

    // Files use CRLF line endings. Only strip the line ending: a leading or
    // trailing tab is an empty cell and must keep its column position.
    $handle = fopen($file, 'r');
    $headers = explode("\t", rtrim(fgets($handle), "\r\n"));
    $headerTypes = array_map(fn () => 'void', $headers);

    while (($line = fgets($handle)) !== false) {
      $values = explode("\t", rtrim($line, "\r\n"));

      foreach ($values as $col => $value) {
        if (isset($headerTypes[$col])) {
          $headerTypes[$col] = widentype($headerTypes[$col], celltype($value));
        }
      }
    }

    fclose($handle);

    // Keep every column by position; duplicate header names must not shift
    // later columns, and must not produce duplicate member names.
    $fields = [];
    $used = [];
    foreach ($headers as $col => $header) {
      $id = '';
      if ($headerTypes[$col] !== 'void') {
        $id = cid($header, "field_$col", FALSE);
        if (isset($used[$id])) {
          $id .= "_$col";
        }
        $used[$id] = TRUE;
      }
      $fields[] = ['col' => $col, 'header' => $header, 'type' => $headerTypes[$col], 'id' => $id];
    }

    $typedefs[$name] = $fields;
  }

  $output = <<<CPP
    #include <cstdint>
    #include <string>
    #include <vector>

    namespace D2::$namespace {
    CPP;

  $output .= "\n\n";

  foreach ($typedefs as $name => $fields) {
    $name = 't_' . $name;
    $output .= "  struct $name {\n";

    foreach ($fields as ['col' => $col, 'header' => $header, 'type' => $type, 'id' => $id]) {
      if ($type === 'void') {
        $output .= "    // Unused column: $header\n";
      }
      else {
        $default_value = $type === 'std::string' ? '""' : '0';
        $output .= "    $type $id = $default_value;\t// Column $col\n";
      }
    }

    $output .= "\n    size_t read(const char* line);\n";
    $output .= "    static std::vector<$name> readfile(std::string filename);\n";

    $output .= "  };\n\n";
  }

  $output .= "}\n";

  file_put_contents(__DIR__ . '/' . $filebase . '.h', $output);

  $output = <<<CPP
    #include "$filebase.h"
    #include <cstdlib>
    #include <string>
    #include <vector>
    #include <fstream>
    #include <sstream>

    namespace D2::$namespace {

      // Split a line on tabs, ignoring any trailing CR/LF.
      static std::vector<std::string> splitline(const char* line) {
        std::vector<std::string> values;
        std::string text(line);

        while (!text.empty() && (text.back() == '\\r' || text.back() == '\\n')) {
          text.pop_back();
        }

        std::stringstream ss(text);
        std::string value;

        while (std::getline(ss, value, '\\t')) {
          values.push_back(value);
        }

        return values;
      }
    CPP;

  $output .= "\n\n";

  foreach ($typedefs as $name => $fields) {
    $name = 't_' . $name;

    $output .= <<<CPP
      size_t $name::read(const char* line) {
        std::vector<std::string> values = splitline(line);
    CPP;
    $output .= "\n\n";

    foreach ($fields as ['col' => $col, 'type' => $type, 'id' => $id]) {
      $value = "values[$col]";
      $parse = match ($type) {
        'void' => NULL,
        'int32_t' => "$id = (int32_t) std::strtol($value.c_str(), nullptr, 10);",
        'int64_t' => "$id = std::strtoll($value.c_str(), nullptr, 10);",
        'double' => "$id = std::strtod($value.c_str(), nullptr);",
        'std::string' => "$id = $value;",
      };
      if ($parse !== NULL) {
        $output .= "    if (values.size() > $col) { $parse }\n";
      }
    }

    $output .= "\n    return values.size();\n  }\n\n";

    $output .= <<<CPP
      std::vector<$name> $name::readfile(std::string filename) {
        std::vector<$name> ret;
        std::ifstream file(filename);
  
        if (!file.is_open()) {
          return ret; // Return empty vector if file cannot be opened
        }
  
        std::string line;
        if (!std::getline(file, line)) {
          return ret; // Return empty vector if file is empty
        }
        while (std::getline(file, line)) {
          $name v;
          v.read(line.c_str());
          ret.push_back(v);
        }
  
        return ret;
      }
    CPP;

    $output .= "\n\n";
  }

  $output .= "}\n";

  file_put_contents(__DIR__ . '/' . $filebase . '.cpp', $output);
}
