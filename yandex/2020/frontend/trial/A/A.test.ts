(function() {
  const solution = require('./A.js');

  (function() {
    let data = [1, 2, 3];
    let res = solution(data);
    console.log(res);
  })();

  (function() {
    let data =  [2,7,4,1,8,1];
    let res = solution(data);
    console.log(res);
  })();

  (function() {
    let data =  [2, 3, 5, 5, 1, 2, 3, 10];
    let res = solution(data);
    console.log(res);
  })();

  (function() {
    let data =  [1, 2, 3, 4, 5];
    let res = solution(data);
    console.log(res);
  })();
})();
