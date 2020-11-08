(function() {
  const solution = require('./A.js');

  (function() {
    let a = { w: 10, h: 5 };
    let b = [
        { w: 9, h: 1 },
        { w: 10, h: 5 },
        { w: 8, h: 3 }
    ];
    let res = solution(a, b);
    console.log(res);
  })();

})();
