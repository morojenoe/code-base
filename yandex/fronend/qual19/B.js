"use strict";
function downloadFile(input) {
    return new Promise(function (resolve, reject) {
        var isDataTransmitted = false;
        function timeOut() {
            if (!isDataTransmitted) {
                reject("Timed out");
            }
        }
        setTimeout(timeOut, 1000);
        var chunksLeft = input.chunkCount;
        var transferredIds = new Set();
        var chunks = [];
        input.emitter.on(function (chunk) {
            if (transferredIds.has(chunk.id)) {
                reject("Duplicate: " + chunk.id);
            }
            transferredIds.add(chunk.id);
            chunks.push(chunk);
            chunksLeft--;
            if (chunksLeft == 0) {
                isDataTransmitted = true;
                chunks.sort(function (lft, rgh) {
                    var lftTime = lft.timestamp.getTime();
                    var rghTime = rgh.timestamp.getTime();
                    if (lftTime < rghTime) {
                        return -1;
                    }
                    if (lftTime > rghTime) {
                        return 1;
                    }
                    return 0;
                });
                resolve(chunks.reduce(function (prev, cur) { return prev + cur.data; }, ""));
            }
        });
    });
}
module.exports = downloadFile;
function test() {
    downloadFile({
        chunkCount: 3,
        emitter: { on: function (fn) {
                fn({ id: 5314, data: "The Good, ", timestamp: new Date("2019-01-01") });
                fn({ id: 1543, data: "d the Ugly", timestamp: new Date("2019-01-03") });
                fn({ id: 2494, data: "the Bad an", timestamp: new Date("2019-01-02") });
            } }
    })
        .then(function (result) { return console.log(result); })
        .catch(function (err) { return console.log(err); });
}
test();
