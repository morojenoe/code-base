interface DownfallInfo {
    top: number;
    left: number;
    right: number;
    bottom: number;
  }

  interface Dron {
    move: (position: [number, number]) => Promise<boolean>;
    top: () => Promise<number>;
    left: () => Promise<number>;
    right: () => Promise<number>;
    bottom: () => Promise<number>;
  }

function getCoord(dron: Dron) {
  return Promise.all([dron.top(), dron.bottom(), dron.left(), dron.right()]);
}

function check(c: number[], info: DownfallInfo): boolean {
  return c[0] === info.top && c[1] === info.bottom && c[2] === info.left && c[3] === info.right;
}


function dfs(i: number, j: number, mapSize: number, dron: Dron, info: DownfallInfo): Promise<[number, number]> {
  if (j >= mapSize) {
    i += 1;
    j = 0;
  }
  console.log(i, j);
  return dron.move([i, j]).then(
    res => {
      if (res) {
        const c = getCoord(dron);
        return c.then(
          coord => {
            if (check(coord, info)) {
              return [i, j];
            } else {
              return dfs(i, j + 1, mapSize, dron, info);
            }
          }
        )
      } else {
        return dfs(i, j + 1, mapSize, dron, info);
      }
    }
  );
}

function solution(dron: Dron, downfallInfo: DownfallInfo, mapSize: number): Promise<[number, number]> {
  return dfs(0, 0, mapSize, dron, downfallInfo);
}
  

module.exports = solution;
