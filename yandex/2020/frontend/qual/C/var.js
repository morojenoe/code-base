module.exports = (function () {
    let prevFrames = [];
    let offsetMs = 100;
    let p = [0, 0, 0];

    return function (data, api) {
        let {width, height} = api.getDimensions();
        let currentTime = api.getTime();

        const length = width * height;

        prevFrames.push({time: currentTime, data: data.slice()});

        function check(offset, tm, i) {
          return tm - prevFrames[i].time >= offset;
        }

        function getFrameFor(offset, index) {
            return currentTime => {
              while (p[index] + 1 < prevFrames.length && check(offset, currentTime, p[index] + 1)) {
                p[index]++;
              }
              return check(offset, currentTime, p[index]) ? prevFrames[p[index]] : undefined;
            };
        }
        const getRedFrame = getFrameFor(0, 0),
            getGreenFrame = getFrameFor(offsetMs, 1),
            getBlueFrame = getFrameFor(2 * offsetMs, 2);
        const res = new Uint8ClampedArray(data.length);

        const red = getRedFrame(currentTime), green = getGreenFrame(currentTime), blue = getBlueFrame(currentTime);
        for (let i = 0; i < length; i++) {
            if (red &&
                green &&
                blue) {
                    res[4 * i] = red[4 * i];
                    res[4 * i + 1] = green[4 * i + 1];
                    res[4 * i + 2] = blue[4 * i + 2];
                    res[4 * i + 3] = 255;
            } else {
                res[4 * i] = data[4 * i];
                res[4 * i + 1] = data[4 * i + 1];
                res[4 * i + 2] = data[4 * i + 2];
                res[4 * i + 3] = 255;
            }
        }

        return Promise.resolve(res);
    };
})();
