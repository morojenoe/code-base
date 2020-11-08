interface A {
    w: number;
    h: number;
}

function calc(a: A, b: A) {
  var x = a.h * b.w / b.h;
  var x2 = b.h * a.w / b.w;
  var res = 1e20;
  if (x >= a.w) {
      res = a.h * (x - a.w);
  }
  if (x2 >= a.h) {
      res = Math.min(res, a.w * (x2 - a.h));
  }
  return res;
}

function getBestFitImageIndex(frame: A, images: A[]) {
    let bestId = 0, bestRes = calc(frame, images[0]);
    images.forEach((val, index) => {
        const r = calc(frame, val);
        
        if (bestRes > r + 1e-9) {
            bestRes = r;
            bestId = index;
        }
    });
    return bestId;
}

module.exports = getBestFitImageIndex;
