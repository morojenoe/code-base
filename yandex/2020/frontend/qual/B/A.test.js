(function () {
    var solution = require('./A.js');
    (function () {
        var data = [
            "GALAXY-42/SYSTEM/PLANET:{}",
            "GALAXY-42/SYSTEM/PLANET:{Message}",
            "GALAXY-42/System/PLANET:{Message}",
            "GALAXY-42/SYSTEM/PLANET{Message}",
            "LONGGALAXY-42/SYSTEM/PLANET:{Message}",
            "GALAXY-4/SYSTEM/PLANET:{Message}",
            "GALAXY-4815162342/SYSTEM/PLANET:{Message}",
            "GALAXY-42/THE-SOLAR-SYSTEM/PLANET:{Message}",
            "GALAXY-42/-SYSTEM/PLANET:{Message}",
            "GALAXY-42/SYSTEM1/PLANET:{Message}",
            "GALAXY-42/SYS--TEM/PLANET:{Message}",
            "GALAXY-42/ERROR/NIL:{Message}",
            "GALAXY-42/ERROR/NULL:{Message}",
            "GALAXY-42/ERROR/UNDEFINED:{Message}",
            "GALAXY-42/TYPE/ISNOTUNDEFINED:{Message}",
            "GALAXY-42/SYSTEM/PLANET:{Simple text... @null == undefined@}",
            "GALAXY-42/SYSTEM/PLANET:{@typeof null@@typeof typeof null@}"
        ];
        var res = solution(data);
        console.log(res);
    })();
})();
