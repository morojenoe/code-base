function check(s) {
    var re = /^[A-Z]{2,8}\-\d{2,8}\/([A-Z\-]+)\/([A-Z]+)\:\{.*\}/;
    var t = re.exec(s);
    if (!t) {
        return false;
    }
    var system = t[1];
    var planet = t[2];
    if (system[0] === '-' || system[system.length - 1] === '-' || system.includes('--')) {
        return false;
    }
    if (planet.includes('UNDEFINED')) {
        return false;
    }
    return true;
}
module.exports = function (input) {
    var result = [];
    input.forEach(function (str) {
        if (check(str)) {
            result.push(str);
        }
    });
    result = result.map(function (s) {
        while (s.indexOf('@') != -1) {
            var r = '';
            var first = s.indexOf('@');
            r = s.slice(0, first);
            r += '<fake>';
            r += s.slice(first + 1);
            s = r;
            var second = s.indexOf('@');
            r = s.slice(0, second);
            r += '<\/fake>';
            r += s.slice(second + 1);
            s = r;
        }
        return s;
    });
    return result;
};
