"use strict";

Vue && Vue.directive('tooltip', {
  bind: function (el, binding) {
    if (binding.value) {
      $(el).tooltip({
        title: binding.value,
        placement: 'bottom',
      });
    }
  },
});
