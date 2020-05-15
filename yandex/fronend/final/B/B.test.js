"use strict";
(function () {
    var solution = require('./B.js');
    (function () {
        var servers = [
            'srv-a',
            'srv-b',
            'srv-c',
            'srv-d' // fail  
        ];
        var check = function (name) { return new Promise(function (res) { return setTimeout(res, 100); }).then(function () { return name === 'srv-a' || name == 'srv-b' || name == 'srv-c'; }); };
        solution(servers, check).then(function (s) { return console.log(s); });
    })();
})();
