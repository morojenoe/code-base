let w: number[];
let q: number[];
let n: number;

function maxQ(): number {
    return q.reduce((prev, cur) => Math.max(prev, cur), 0);
}

function extractQ(value: number) {
    const index = q.indexOf(value);
    q.splice(index, 1);
}

function extractMax(): number {
    if (w.length > 0) {
        const maxW = w[w.length - 1];
        const mq = maxQ();
        if (maxW > mq) {
            w.pop();
            return maxW;
        } else {
            extractQ(mq);
            return mq;
        }
    } else {
        const result = maxQ();
        extractQ(result);
        return result;
    }
}

function add(value: number) {
    q.push(value);
    if (q.length > n) {
        w = w.concat(q);
        w.sort((a, b) => a - b);
        q = [];
    }
}

function getAnswer(): number | null {
    if (w.length + q.length === 0) {
        return 0;
    }
    if (w.length + q.length === 1) {
        return w.length === 1 ? w[0] : q[0];
    }
    return null;
}

function findLatestWeight(weights: number[]) {
    w = weights.slice();
    w.sort((a, b) => a - b);
    q = [];
    n = 1;
    while (n < weights.length) {
        n *= 2;
    }

    while (getAnswer() === null) {
        const m1 = extractMax();
        const m2 = extractMax();
        const value = Math.abs(m1 - m2);
        if (value) {
            add(value);
        }
    }

    return getAnswer();
}
   
module.exports = findLatestWeight;
