"use strict";
module.exports = function (a) {
    var x = 0, y = 0;
    for (var i = 0; i < a.length; ++i) {
        x += a[i][0];
        y += a[i][1];
    }
    if (x % 2 !== 0 || y % 2 !== 0) {
        return null;
    }
    x /= 2;
    y /= 2;
    for (var i = 0; i < a.length; ++i) {
        if (x > 0 && a[i][0] === 1) {
            --x;
            a[i][0] = -1;
        }
        if (y > 0 && a[i][1] === 1) {
            --y;
            a[i][1] = -1;
        }
    }
    return a;
};
