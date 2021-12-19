"use strict";

(function () {
  var solution = require('./A.js');

  (function () {
    var a = {
      w: 10,
      h: 5
    };
    var b = [{
      w: 9,
      h: 1
    }, {
      w: 15,
      h: 1
    }, {
      w: 10,
      h: 5
    }];
    var res = solution(a, b);
    console.log(res);
  })();
})();