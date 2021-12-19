(function () {
    const solution = require('./A.js');
    (function () {
        let data = [1, 2, 3];
        let res = solution(data);
        console.log(res);
    })();
    (function () {
        let data = [2, 7, 4, 1, 8, 1];
        let res = solution(data);
        console.log(res);
    })();
    (function () {
        let data = [2, 3, 5, 5, 1, 2, 3, 10];
        let res = solution(data);
        console.log(res);
    })();

    (function () {
        let data = [99, 11, 22];
        let res = solution(data);
        console.log(res);
    })();

    (function () {
        let data = [];
        for (let i = 0; i < 1000000; ++i) {
            data.push(Math.floor(Math.random()*1000000));
        }
        let res = solution(data);
        console.log(res);
    })();
})();
