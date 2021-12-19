(function () {
    var solution = require('./A.js');
    (function () {
        var a = { w: 10, h: 5 };
        var b = [
            { w: 9, h: 1 },
            { w: 10, h: 5 },
            { w: 8, h: 3 }
        ];
        var res = solution(a, b);
        console.log(res);
    })();
})();
