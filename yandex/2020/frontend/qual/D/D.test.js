(function () {
    var solution = require('./D.js');
    (function () {
        var data = [5, 4, 18, 1, 2, 8, 4, 3, 1, 3, 2, 10, 12, 100];
        var res = solution(data);
        var t;
        do {
            t = res.next();
            console.log(t);
        } while (!t.done);
    })();
})();
