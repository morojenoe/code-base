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

(function() {
  const solution = require('./B.js');

  (function() {
    const info: DownfallInfo = {
      top: 0, left: 0, right: 0, bottom: 0
    };
    let i = 0, j = 0;
    const dron: Dron = {
      top: () => {
        return i === 1 && j === 1 ? Promise.resolve(1) : Promise.resolve(0);
      },
      left: () => Promise.resolve(0),
      right: () => Promise.resolve(0),
      bottom: () => Promise.resolve(0),
      move: ([i, j]: [number, number]) => {
        return Promise.resolve(true);
      }
    }
    let res = solution(dron, info, 5);
    res.then(s => console.log(s));
  })();

})();
