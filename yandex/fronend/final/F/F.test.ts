interface PlayerClient {  
  on(event: 'move', callback: (move: [number, number]) => void): void;
  nextTurn(rivalMove: [number, number] | null): void;  
  retry(): void;  
  end(result: 'win' | 'lose' | 'tie'): void;  
}

function shuffle(a: Array<[number, number]>) {
  for (let i = a.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [a[i], a[j]] = [a[j], a[i]];
  }
  return a;
}

(function() {
  const solution = require('./F.js');

  (function() {
    let lastMove: [number, number] | null = null;
    let turn: Array<[number, number]> = [[0, 0], [0, 1], [0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1], [2, 2]];
    shuffle(turn);
    console.log(turn);
    let p1cb: any;
    let p2cb: any;
    let p1: PlayerClient = {
      end: function end(result: string) {
        console.log('first player is ' + result)
      },
      nextTurn: function nextTurn(r: [number, number] | null) {
        if (r == null) {
          console.assert(r === lastMove);
        } else {
          if (lastMove == null) {
            console.assert(false);
          } else {
            console.assert(r[0] == lastMove[0] && r[1] == lastMove[1])
          }
        }
        
        console.log('first next turn');
        let move = <[number, number]>turn.shift();
        lastMove = [move[0], move[1]];
        p1cb(move);
      },
      retry: function retry() {
        console.log('Error retry');
      },
      on: function on(event: 'move', callback: (move: [number, number]) => void) {
        p1cb = callback;
        // cb(move);
      }
    };
    let p2: PlayerClient = {
      end: function end(result: string) {
        console.log('second player is ' + result)
      },
      nextTurn: function nextTurn(r: [number, number] | null) {
        if (r == null) {
          console.assert(r === lastMove);
        } else {
          if (lastMove == null) {
            console.assert(false);
          } else {
            console.assert(r[0] == lastMove[0] && r[1] == lastMove[1])
          }
        }

        let move = <[number, number]>turn.shift();
        lastMove = [move[0], move[1]];
        p2cb(move);
      },
      retry: function retry() {
        console.log('Error retry');
      },
      on: function on(event: 'move', callback: (move: [number, number]) => void) {
        
        p2cb = callback;
        // cb(move);
      }
    };
    solution(p1, p2);
  })();
})();
