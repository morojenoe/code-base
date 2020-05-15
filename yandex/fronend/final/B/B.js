"use strict";
function go(L, R, servers, check) {
    console.log(L, R);
    if (L + 1 >= R) {
        return Promise.resolve(servers[R]);
    }
    var M = Math.floor((L + R) / 2);
    var name = servers[M];
    return check(name).then(function (value) {
        if (value) {
            // L = M;
            return go(M, R, servers, check);
        }
        else {
            // R = M;
            return go(L, M, servers, check);
        }
    });
}
module.exports = function (servers, check) {
    var L = -1, R = servers.length - 1;
    return go(L, R, servers, check);
};
