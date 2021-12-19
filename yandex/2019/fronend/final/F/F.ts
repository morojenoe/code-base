interface PlayerClient {  
  on(event: 'move', callback: (move: [number, number]) => void): void;  
  nextTurn(rivalMove: [number, number] | null): void;  
  retry(): void;  
  end(result: 'win' | 'lose' | 'tie'): void;  
}

let b: [Array<number>, Array<number>, Array<number>];
let moves: [Array<[number, number]|null>, Array<[number, number]|null>];
let turn: number;
let p: [PlayerClient, PlayerClient];
let err: number;
let gameIsOver: number;
let lastMove = (id: number) => moves[id][moves[id].length - 1];
let step: number;

function isEnd(): number {
  if (gameIsOver != -1) {
    return gameIsOver;
  }
  let finish = true;
  for (let i = 0; i < 3; ++i) {
    for (let j = 0; j < 3; ++j) {
      if (b[i][j] === -1) {
        finish = false;
      }
    }
  }
  let row: boolean;
  for (let i = 0; i < 3; ++i) {
    row = b[i][0] == b[i][1] && b[i][0] == b[i][2];
    if (row && b[i][0] != -1) {
      return gameIsOver = b[i][0];
    }
  }
  for (let i = 0; i < 3; ++i) {
    let row = b[0][i] == b[1][i] && b[0][i] == b[2][i];
    if (row && b[0][i] != -1) {
      return gameIsOver = b[0][i];
    }
  }
  row = b[0][0] == b[1][1] && b[0][0] == b[2][2];
  if (row && b[0][0] != -1) {
    return gameIsOver = b[0][0];
  }

  row = b[0][2] == b[1][1] && b[0][2] == b[2][0];
  if (row && b[0][2] != -1) {
    return gameIsOver = b[0][2];
  }

  if (finish) {
    return gameIsOver = 2;
  }
  return -1;
}

function tryMakeMove(who: number, move: [number, number]): boolean {
  if (isEnd() != -1) {
    return false;
  }

  if (b[move[0]][move[1]] != -1) {
    return false;
  }
  b[move[0]][move[1]] = who;
  return true;
}

function finishGame(whoWin: number) {
  gameIsOver = whoWin;
  if (whoWin != 2) {
    p[whoWin].end('win');
    p[1 - whoWin].end('lose');
  } else {
    p[0].end('tie');
    p[1].end('tie');
  }
}

function makeMove(who: number, move: [number, number]) {
  ++step;
  if (who !== turn) {
    return;
  }
  if (isEnd() != -1) {
    return;
  }
  if (!tryMakeMove(who, move)) {
    ++err;
    if (err == 3) {
      finishGame(1 - who);
    } else {
      p[who].retry();
    }
  } else {
    moves[who].push(move);
    if (isEnd() != -1) {
      finishGame(isEnd());
      return;
    }
    err = 0;
    turn = 1 - who;
    p[1 - who].nextTurn(lastMove(who));
  }
}

module.exports = function(p1: PlayerClient, p2: PlayerClient) {
  b = [[-1, -1, -1], [-1, -1, -1], [-1, -1, -1]];
  moves = [[null], [null]];
  turn = 0;
  p = [p1, p2];
  err = 0;
  gameIsOver = -1;
  step = 0;

  p1.on('move', (move: [number, number]) => makeMove(0, move));
  p2.on('move', (move: [number, number]) => makeMove(1, move));
  
  p[0].nextTurn(lastMove(1 - turn));
}
