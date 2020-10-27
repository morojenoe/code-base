function* sort(arr, L = 0, R = arr.length - 1) {
  console.log('sort: ', arr, L, R);
  if (L < R) {
      var p = yield * partition(arr, L, R);
      console.log('sort::p: ', p);
      yield * sort(arr, L, p - 1);
      yield * sort(arr, p + 1, R);
  }
  return arr;

  function* partition(arr, L, R) {
      var pivot = arr[R];
      var e = L;
      for (var i = L; i < R; i++) {
          if (arr[i] < pivot) {
              yield swap(arr, e, i);
              e += 1;
          }
      }
      yield swap(arr, e, R);
      return e;
  }

  function swap(a, b, c) {
    let t = a[b];
    a[b] = a[c];
    a[c] = t;
    
    // [a[b], a[c]] = [a[b], a[c]];
    // [a[b], a[c]] = [a[c], a[b]];
    return a;
  }
}

module.exports = sort;