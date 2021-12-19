var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
var __values = (this && this.__values) || function(o) {
    var s = typeof Symbol === "function" && Symbol.iterator, m = s && o[s], i = 0;
    if (m) return m.call(o);
    if (o && typeof o.length === "number") return {
        next: function () {
            if (o && i >= o.length) o = void 0;
            return { value: o && o[i++], done: !o };
        }
    };
    throw new TypeError(s ? "Object is not iterable." : "Symbol.iterator is not defined.");
};
function sort(arr, L, R) {
    function partition(arr, L, R) {
        var pivot, e, i;
        return __generator(this, function (_a) {
            switch (_a.label) {
                case 0:
                    pivot = arr[R];
                    e = L;
                    i = L;
                    _a.label = 1;
                case 1:
                    if (!(i < R)) return [3 /*break*/, 4];
                    if (!(arr[i] < pivot)) return [3 /*break*/, 3];
                    return [4 /*yield*/, swap(arr, e, i)];
                case 2:
                    _a.sent();
                    e += 1;
                    _a.label = 3;
                case 3:
                    i++;
                    return [3 /*break*/, 1];
                case 4: return [4 /*yield*/, swap(arr, e, R)];
                case 5:
                    _a.sent();
                    return [2 /*return*/, e];
            }
        });
    }
    function swap(a, b, c) {
        var t = a[b];
        a[b] = a[c];
        a[c] = t;
        // [a[b], a[c]] = [a[b], a[c]];
        // [a[b], a[c]] = [a[c], a[b]];
        return a;
    }
    var p;
    if (L === void 0) { L = 0; }
    if (R === void 0) { R = arr.length - 1; }
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                console.log('sort: ', arr, L, R);
                if (!(L < R)) return [3 /*break*/, 4];
                return [5 /*yield**/, __values(partition(arr, L, R))];
            case 1:
                p = _a.sent();
                console.log('sort::p: ', p);
                return [5 /*yield**/, __values(sort(arr, L, p - 1))];
            case 2:
                _a.sent();
                return [5 /*yield**/, __values(sort(arr, p + 1, R))];
            case 3:
                _a.sent();
                _a.label = 4;
            case 4: return [2 /*return*/, arr];
        }
    });
}
module.exports = sort;
