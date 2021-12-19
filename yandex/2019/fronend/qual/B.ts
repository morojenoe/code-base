interface Input {  
  chunkCount: number;  
  emitter: Emitter;  
}  

interface Emitter {  
  on: (callback: (chunk: Chunk) => void) => void;  
}  

interface Chunk {  
  id: number;  
  timestamp: Date;  
  data: string;  
}

function downloadFile(input: Input) {
  return new Promise(function(resolve, reject) {
    let isDataTransmitted = false;
    function timeOut() {
      if (!isDataTransmitted) {
        reject("Timed out");
      }
    }

    setTimeout(timeOut, 1000);
    
    let chunksLeft = input.chunkCount;
    let transferredIds = new Set<number>();
    let chunks: Array<Chunk> = [];

    input.emitter.on((chunk: Chunk) => {
      if (transferredIds.has(chunk.id)) {
        reject(`Duplicate: ${chunk.id}`);
      }
      transferredIds.add(chunk.id);
      chunks.push(chunk);
      chunksLeft--;
      if (chunksLeft == 0) {
        isDataTransmitted = true;
        chunks.sort((lft: Chunk, rgh: Chunk) => {
          let lftTime = lft.timestamp.getTime();
          let rghTime = rgh.timestamp.getTime();
          if (lftTime < rghTime) {
            return -1;
          }
          if (lftTime > rghTime) {
            return 1;
          }
          return 0;
        });
        resolve(chunks.reduce((prev, cur) => prev + cur.data, ""));
      }
    });
  });
}

module.exports = downloadFile;

function test() {
  downloadFile({  
    chunkCount: 3,  
    emitter: {on: (fn) => {  
        fn({id: 5314, data: "The Good, ", timestamp: new Date("2019-01-01")});  
        fn({id: 1543, data: "d the Ugly", timestamp: new Date("2019-01-03")});  
        fn({id: 2494, data: "the Bad an", timestamp: new Date("2019-01-02")});  
    }}
  })
  .then(result => console.log(result))
  .catch(err => console.log(err));

}

test();