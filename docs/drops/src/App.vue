<script setup>
import { reactive, computed } from "vue";

import "../../../objext.js";
import levels from "../../../json/levels.json";

levels[47]['*StringName'] = 'Act 2 ' + levels[47]['*StringName'];
levels[48]['*StringName'] = 'Act 2 ' + levels[48]['*StringName'];
levels[49]['*StringName'] = 'Act 2 ' + levels[49]['*StringName'];
levels[92]['*StringName'] = 'Act 3 ' + levels[92]['*StringName'];
levels[93]['*StringName'] = 'Act 3 ' + levels[93]['*StringName'];

const data = reactive({});

</script>

<template>
  <pre>{{ JSON.stringify(levels, null, ' ') }}</pre>
</template>

<style>

</style>
