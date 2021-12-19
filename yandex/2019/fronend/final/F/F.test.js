"use strict";
function shuffle(a) {
    var _a;
    for (var i = a.length - 1; i > 0; i--) {
        var j = Math.floor(Math.random() * (i + 1));
        _a = [a[j], a[i]], a[i] = _a[0], a[j] = _a[1];
    }
    return a;
}
(function () {
    var solution = require('./F.js');
    (function () {
        var lastMove = null;
        var turn = [[0, 0], [0, 1], [0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1], [2, 2]];
        shuffle(turn);
        console.log(turn);
        var p1cb;
        var p2cb;
        var p1 = {
            end: function end(result) {
                console.log('first player is ' + result);
            },
            nextTurn: function nextTurn(r) {
                if (r == null) {
                    console.assert(r === lastMove);
                }
                else {
                    if (lastMove == null) {
                        console.assert(false);
                    }
                    else {
                        console.assert(r[0] == lastMove[0] && r[1] == lastMove[1]);
                    }
                }
                console.log('first next turn');
                var move = turn.shift();
                lastMove = [move[0], move[1]];
                p1cb(move);
            },
            retry: function retry() {
                console.log('Error retry');
            },
            on: function on(event, callback) {
                p1cb = callback;
                // cb(move);
            }
        };
        var p2 = {
            end: function end(result) {
                console.log('second player is ' + result);
            },
            nextTurn: function nextTurn(r) {
                if (r == null) {
                    console.assert(r === lastMove);
                }
                else {
                    if (lastMove == null) {
                        console.assert(false);
                    }
                    else {
                        console.assert(r[0] == lastMove[0] && r[1] == lastMove[1]);
                    }
                }
                var move = turn.shift();
                lastMove = [move[0], move[1]];
                p2cb(move);
            },
            retry: function retry() {
                console.log('Error retry');
            },
            on: function on(event, callback) {
                p2cb = callback;
                // cb(move);
            }
        };
        solution(p1, p2);
    })();
})();
