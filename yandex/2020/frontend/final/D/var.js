function c(i, j, d) {
    return i * d.w + j;
}
function get(a, i, j, d) {
    var mx = -1e20, mn = 1e20;
    for (var t = 0; t < 3; ++t) {
        for (var t2 = 0; t2 < 3; ++t2) {
            var pi = i + t;
            var pj = j + t2;
            var ind = c(pi, pj, d);
            if (ind < a.length) {
                mn = Math.min(mn, a[ind]);
                mx = Math.max(mx, a[ind]);
            }
        }
    }
    return mx - mn;
}
function filter(i, j, a, r, d) {
    if (i >= d.h) {
        return Promise.resolve(r);
    }
    return new Promise(function (resolve) {
        setTimeout(function () {
            for (var k = 0; i < d.h && k < 10; ++k, ++i)
                for (; j < d.w; ++j) {
                    r[c(i, j, d)] = get(a, i, j, d);
                }
            filter(i + 1, 0, a, r, d).then(function () { return resolve(r); });
        });
    });
}
function solution(a, dim) {
    var d = { w: dim.width, h: dim.height };
    var r = [];
    for (var i = 0; i < a.length; i += 4) {
        r.push((0.21 * a[i] + 0.72 * a[i + 1] + 0.07 * a[i + 2]));
    }
    return filter(0, 0, r, r.slice(), d)
        .then(function (a) {
        var b = a.slice();
        for (var i = 0; i < d.h; i++) {
            b[c(i, 0, d)] = 0;
            b[c(i, d.w - 1, d)] = 0;
        }
        for (var i = 0; i < d.w; i++) {
            b[c(0, i, d)] = 0;
            b[c(d.h - 1, i, d)] = 0;
        }
        return b;
    })
        .then(function (a) {
        var b = a.slice();
        for (var i = 0; i < a.length; ++i) {
            b[i] = a[i] <= 90 ? 0 : 255;
        }
        return new Uint8ClampedArray(b);
    });
}
module.exports = solution;
