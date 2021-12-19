(function () {
    var solution = require('./B.js');
    (function () {
        var info = {
            top: 0, left: 0, right: 0, bottom: 0
        };
        var i = 0, j = 0;
        var dron = {
            top: function () {
                return i === 1 && j === 1 ? Promise.resolve(1) : Promise.resolve(0);
            },
            left: function () { return Promise.resolve(0); },
            right: function () { return Promise.resolve(0); },
            bottom: function () { return Promise.resolve(0); },
            move: function (_a) {
                var i = _a[0], j = _a[1];
                return Promise.resolve(true);
            }
        };
        var res = solution(dron, info, 5);
        res.then(function (s) { return console.log(s); });
    })();
})();
