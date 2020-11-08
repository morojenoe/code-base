interface HW {
  h: number;
  w: number;
}

function c(i: number, j: number, d: HW) {
  return i * d.w + j;
}

function get(a: number[], i: number, j: number, d: HW) {
  let mx = -1e20, mn = 1e20;
  for (let t = 0; t < 3; ++t) {
    for (let t2 = 0; t2 < 3; ++t2) {
      const pi = i + t;
      const pj = j + t2;
      const ind = c(pi, pj, d);
      if (ind < a.length) {
        mn = Math.min(mn, a[ind]);
        mx = Math.max(mx, a[ind]);
      }
    }
  }
  return mx - mn;
}

function filter(i: number, j: number, a: number[], r: number[], d: HW) {
  if (i >= d.h) {
    return Promise.resolve(r);
  }
  return new Promise(resolve => {
    setTimeout(() => {
      for (let k = 0; i < d.h && k < 10; ++k, ++i)
      for (; j < d.w; ++j) {
        r[c(i, j, d)] = get(a, i, j, d);
      }
      filter(i + 1, 0, a, r, d).then(() => resolve(r));
    });
  });
}

function solution(a: Uint8ClampedArray, dim) {
  const d: HW = { w: dim.width, h: dim.height };
  let r = [];
  for (let i = 0; i < a.length; i += 4) {

    r.push((0.21 * a[i] + 0.72 * a[i + 1] + 0.07 * a[i + 2]));
  }
  return filter(0, 0, r, r.slice(), d)
    .then((a) => {
      const b = a.slice();
      for (let i = 0; i < d.h; i++) {
        b[c(i, 0, d)] = 0;
        b[c(i, d.w - 1, d)] = 0;
      }
      for (let i = 0; i < d.w; i++) {
        b[c(0, i, d)] = 0;
        b[c(d.h - 1, i, d)] = 0;
      }
      return b;
    })
    .then((a) => {
      const b = a.slice();
      for (let i = 0; i < a.length; ++i) {
        b[i] = a[i] <= 90 ? 0 : 255;
      }
      return new Uint8ClampedArray(b);
    });
}


module.exports = solution;
