"use strict";

function getCoord(dron) {
  return Promise.all([dron.top(), dron.bottom(), dron.left(), dron.right()]);
}

function check(c, info) {
  return c[0] === info.top && c[1] === info.bottom && c[2] === info.left && c[3] === info.right;
}

function dfs(i, j, mapSize, dron, info) {
  if (j >= mapSize) {
    i += 1;
    j = 0;
  }

  return dron.move([i, j]).then(function (res) {
    if (res) {
      var c = getCoord(dron);
      return c.then(function (coord) {
        if (check(coord, info)) {
          return [i, j];
        } else {
          return dfs(i, j + 1, mapSize, dron, info);
        }
      });
    } else {
      return dfs(i, j + 1, mapSize, dron, info);
    }
  });
}

function solution(dron, downfallInfo, mapSize) {
  return dfs(0, 0, mapSize, dron, downfallInfo);
}

module.exports = solution;