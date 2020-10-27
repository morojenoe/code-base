(function() {
  const solution = require('./D.js');

  (function() {
    let data = [5, 4, 18, 1, 2, 8, 4, 3, 1, 3, 2, 10, 12, 100];
    let res = solution(data);
    let t;
    do {
      t = res.next();
      console.log(t);
    } while (!t.done);
  })();

})();
