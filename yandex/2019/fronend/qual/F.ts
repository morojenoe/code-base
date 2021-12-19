function nextIndex(i: number, length: number): number {
  return (i + 1 === length)? 0 : i + 1;
}

function calcTriangleArea(p1: [number, number], p2: [number, number]) {
  return p1[0]*p2[1] - p1[1]*p2[0];
}

function calcArea(poly: Array<[number, number]>) {
  let area = 0;
  for (let i = 0; i < poly.length; ++i) {
    let j = nextIndex(i, poly.length);
    area += calcTriangleArea(poly[i], poly[j]);
  }
  return Math.abs(area);
}

function subPoints(p1: [number, number], p2: [number, number]): [number, number] {
  return [p1[0] - p2[0], p1[1] - p2[1]];
}

function addPoints(p1: [number, number], p2: [number, number]): [number, number] {
  return [p1[0] + p2[0], p1[1] + p2[1]];
}

function getPolyCenter(poly: Array<[number, number]>) {
  let center = poly.reduce((center, cur) => addPoints(center, cur));
  center[0] /= poly.length;
  center[1] /= poly.length;
  return center;
}

function findDividePoint(poly: Array<[number, number]>, i: number,
    curArea: number, center: [number, number], area: number) {
  let j = nextIndex(i, poly.length);
  let leftPoint = poly[i];
  let rightPoint = poly[j];
  for (let k = 0; k < 1000; ++k) {
    let mid = addPoints(leftPoint, rightPoint);
    mid[0] /= 2;
    mid[1] /= 2;
    let newArea = Math.abs(calcTriangleArea(subPoints(leftPoint, center), subPoints(mid, center)));
    if ((curArea + newArea)*2 < area) {
      leftPoint = mid;
    } else {
      rightPoint = mid;
    }
  }
  return leftPoint;
}

module.exports = function (poly: Array<[number, number]>) {
  let area = calcArea(poly);
  console.log('area = ', area);
  let center = getPolyCenter(poly);
  console.log('center = ', center);
  let curArea = 0;
  let index = -1;
  for (let i = 0; i < poly.length && index === -1; ++i) {
    let j = nextIndex(i, poly.length);
    console.log('j = ', j);
    let nextArea = curArea + Math.abs(calcTriangleArea(subPoints(poly[i], center), subPoints(poly[j], center)));
    console.log('nextArea', nextArea);
    if (curArea*2 < area && nextArea*2 >= area) {
      index = i;
    } else {
      curArea = nextArea;
    }
  }
  console.log(index, curArea);
  const dividePoint = findDividePoint(poly, index, curArea, center, area);
  return [center, dividePoint];
};

// console.log(module.exports([[0, 0], [0, 1], [1, 1], [1, 0]]));
// console.log(module.exports([[1, 1], [5, 1], [6, 2], [6, 4], [5, 5], [1, 5], [0, 4], [0, 2]]));
console.log(module.exports([[1, 1], [5, 1], [6, 2], [6, 4], [1, 5], [0, 4], [0, 2]]));