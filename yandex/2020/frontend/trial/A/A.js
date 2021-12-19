const maximumTwo = (arr) => {
    let max1 = arr[0];
    let max2 = arr[1];
    let max1I = 0;
    let max2I = 1;
    for(let i = 2; i < arr.length; i++) {
        if (arr[i] > max1) {
            if (max1 > max2) {
                max2 = arr[i];
                max2I = i;
            } else {
                max1 = arr[i];
                max1I = i;
            }
        } else if (arr[i] > max2) {
            max2 = arr[i];
            max2I = i;
        }
    }

    if (max1 > max2) return [max2, max1, max2I, max1I];
    return [max1, max2, max1I, max2I];
};



const fn = function(weights) {
    if (weights.length <= 1) {
        return weights[0];
    }

    do {
        const [x, y, xI, yI] =  maximumTwo(weights);
        if (x === 0) {
            return y;
        }

        weights[xI] = 0;
        weights[yI] = y - x;

    } while(true);
};


module.exports = fn;
