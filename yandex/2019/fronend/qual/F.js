"use strict";
function nextIndex(i, length) {
    return (i + 1 === length) ? 0 : i + 1;
}
function calcTriangleArea(p1, p2) {
    return p1[0] * p2[1] - p1[1] * p2[0];
}
function calcArea(poly) {
    var area = 0;
    for (var i = 0; i < poly.length; ++i) {
        var j = nextIndex(i, poly.length);
        area += calcTriangleArea(poly[i], poly[j]);
    }
    return Math.abs(area);
}
function subPoints(p1, p2) {
    return [p1[0] - p2[0], p1[1] - p2[1]];
}
function addPoints(p1, p2) {
    return [p1[0] + p2[0], p1[1] + p2[1]];
}
function getPolyCenter(poly) {
    var center = poly.reduce(function (center, cur) { return addPoints(center, cur); });
    center[0] /= poly.length;
    center[1] /= poly.length;
    return center;
}
function findDividePoint(poly, i, curArea, center, area) {
    var j = nextIndex(i, poly.length);
    var leftPoint = poly[i];
    var rightPoint = poly[j];
    for (var k = 0; k < 1000; ++k) {
        var mid = addPoints(leftPoint, rightPoint);
        mid[0] /= 2;
        mid[1] /= 2;
        var newArea = Math.abs(calcTriangleArea(subPoints(leftPoint, center), subPoints(mid, center)));
        if ((curArea + newArea) * 2 < area) {
            leftPoint = mid;
        }
        else {
            rightPoint = mid;
        }
    }
    return leftPoint;
}
module.exports = function (poly) {
    var area = calcArea(poly);
    console.log('area = ', area);
    var center = getPolyCenter(poly);
    console.log('center = ', center);
    var curArea = 0;
    var index = -1;
    for (var i = 0; i < poly.length && index === -1; ++i) {
        var j = nextIndex(i, poly.length);
        console.log('j = ', j);
        var nextArea = curArea + Math.abs(calcTriangleArea(subPoints(poly[i], center), subPoints(poly[j], center)));
        console.log('nextArea', nextArea);
        if (curArea * 2 < area && nextArea * 2 >= area) {
            index = i;
        }
        else {
            curArea = nextArea;
        }
    }
    console.log(index, curArea);
    var dividePoint = findDividePoint(poly, index, curArea, center, area);
    return [center, dividePoint];
};
// console.log(module.exports([[0, 0], [0, 1], [1, 1], [1, 0]]));
// console.log(module.exports([[1, 1], [5, 1], [6, 2], [6, 4], [5, 5], [1, 5], [0, 4], [0, 2]]));
console.log(module.exports([[1, 1], [5, 1], [6, 2], [6, 4], [1, 5], [0, 4], [0, 2]]));
