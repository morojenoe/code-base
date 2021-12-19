var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
var TaskManager = /** @class */ (function () {
    function TaskManager(N // общее число роботов-исполнителей (от 1 до 1024)  
    ) {
        this.N = N;
        this.tasks = [];
        this.res = [];
        for (var i = 0; i < N; ++i) {
            this.res.push({
                failedCount: 0,
                successCount: 0,
                tasks: [],
                timeSpent: 0
            });
        }
    }
    TaskManager.prototype.addToQueue = function (task) {
        this.tasks.push(__assign(__assign({}, task), { time: this.tasks.length }));
    };
    TaskManager.prototype.run = function () {
        var _this = this;
        this.tasks.sort(function (a, b) {
            if (a.priority === b.priority) {
                return a.time < b.time ? -1 : 1;
            }
            return a.priority > b.priority ? -1 : 1;
        });
        var p = [];
        this.curTaskId = this.N;
        for (var i = 0; i < Math.min(this.tasks.length, this.N); ++i) {
            p.push(this.take(i, i));
        }
        return Promise.all(p).then(function () { return _this.res; });
    };
    TaskManager.prototype.take = function (robotId, taskId) {
        var _this = this;
        if (taskId === undefined) {
            taskId = this.curTaskId++;
        }
        if (taskId >= this.tasks.length) {
            return Promise.resolve();
        }
        var start = new Date(Date.now());
        return this.tasks[taskId].job().then(function () {
            var end = new Date(Date.now());
            _this.res[robotId].timeSpent += end.getTime() - start.getTime();
            _this.res[robotId].tasks.push(_this.tasks[taskId].id);
            _this.res[robotId].successCount++;
            return _this.take(robotId);
        }, function () {
            var end = new Date(Date.now());
            _this.res[robotId].timeSpent += end.getTime() - start.getTime();
            _this.res[robotId].tasks.push(_this.tasks[taskId].id);
            _this.res[robotId].failedCount++;
            return _this.take(robotId);
        });
    };
    return TaskManager;
}());
module.exports = { TaskManager: TaskManager };
