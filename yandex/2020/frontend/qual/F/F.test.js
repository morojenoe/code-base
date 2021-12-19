;
(function () {
    var solution = require('./F.js');
    var data = {
        // абсолютный путь до дирректории проекта в файловой системе  
        absoluteRepoPath: "/var/www/projects/project1",
        // список алиасов по путям из исходной системы сборки  
        aliases: {
            "@": "/var/www/projects/project1/src"
        },
        // список всех входных точек приложения  
        entrypoints: [
            "/var/www/projects/project1/src/pages/a.js",
            "/var/www/projects/project1/src/pages/b.js",
        ],
        // информация о всех модулях данного проекта  
        modules: [
            {
                // относительный от корня путь  
                file: "./src/pages/a.js",
                deps: [
                    // валидная для исходной системы сборки строка, описывающая путь до модуля  
                    // гарантируется, что такой модуль существует и описан в данной секции  
                    "/var/www/projects/project1/src/a.js",
                ]
            },
            {
                file: "./src/pages/b.js",
                deps: [
                    "@/a.js",
                ]
            },
            {
                file: "./src/a.js",
                deps: []
            },
            {
                file: "./src/f.js",
                deps: []
            },
            {
                file: "./src/g.js",
                deps: []
            },
        ]
    };
    var projectAliases = {
        absoluteRepoPath: '/abs/path/to',
        aliases: {
            '@root': '@other/path',
            '@other': './project/test/src/app'
        },
        entrypoints: [
            './entry.js',
            '@other/main.js'
        ],
        modules: [
            { file: './entry.js', deps: [] },
            { file: './project/test/src/app/../../src/app/main.js', deps: ['@root/feature.js'] },
            { file: '@other/path/feature.js', deps: [] },
            { file: './not-exists.js', deps: ['./entry.js'] }
        ]
    };
    (function () {
        var res = solution(projectAliases);
        console.log(res);
    })();
})();
