"use strict";
var b;
var moves;
var turn;
var p;
var err;
var gameIsOver;
var lastMove = function (id) { return moves[id][moves[id].length - 1]; };
var step;
function isEnd() {
    if (gameIsOver != -1) {
        return gameIsOver;
    }
    var finish = true;
    for (var i = 0; i < 3; ++i) {
        for (var j = 0; j < 3; ++j) {
            if (b[i][j] === -1) {
                finish = false;
            }
        }
    }
    var row;
    for (var i = 0; i < 3; ++i) {
        row = b[i][0] == b[i][1] && b[i][0] == b[i][2];
        if (row && b[i][0] != -1) {
            return gameIsOver = b[i][0];
        }
    }
    for (var i = 0; i < 3; ++i) {
        var row_1 = b[0][i] == b[1][i] && b[0][i] == b[2][i];
        if (row_1 && b[0][i] != -1) {
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
function tryMakeMove(who, move) {
    if (isEnd() != -1) {
        return false;
    }
    if (b[move[0]][move[1]] != -1) {
        return false;
    }
    b[move[0]][move[1]] = who;
    return true;
}
function finishGame(whoWin) {
    gameIsOver = whoWin;
    if (whoWin != 2) {
        p[whoWin].end('win');
        p[1 - whoWin].end('lose');
    }
    else {
        p[0].end('tie');
        p[1].end('tie');
    }
}
function makeMove(who, move) {
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
        }
        else {
            p[who].retry();
        }
    }
    else {
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
module.exports = function (p1, p2) {
    b = [[-1, -1, -1], [-1, -1, -1], [-1, -1, -1]];
    moves = [[null], [null]];
    turn = 0;
    p = [p1, p2];
    err = 0;
    gameIsOver = -1;
    step = 0;
    p1.on('move', function (move) { return makeMove(0, move); });
    p2.on('move', function (move) { return makeMove(1, move); });
    p[0].nextTurn(lastMove(1 - turn));
};
