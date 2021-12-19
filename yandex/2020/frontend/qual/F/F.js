;
function getAbsPath(project, path) {
    if (path.startsWith('/')) {
        return path;
    }
    if (path.startsWith('./')) {
        return project.absoluteRepoPath + path.slice(1);
    }
    if (path.startsWith('..')) {
        return project.absoluteRepoPath + '/' + path;
    }
    var i = path.indexOf('/');
    if (i === -1) {
        i = path.length;
    }
    var alias = path.slice(0, i);
    return getAbsPath(project, project.aliases[alias] + path.slice(i));
}
function absPathClean(path) {
    while (path.includes('//')) {
        var index = path.indexOf('//');
        path = path.slice(0, index) + path.slice(index + 1);
    }
    if (path.includes('..')) {
        var index = path.indexOf('../');
        index -= 2;
        var indexSlash = path.lastIndexOf('/', index);
        var res = path.slice(0, indexSlash);
        res += path.slice(index + 4);
        return absPathClean(res);
    }
    return path;
}
function makeAbsPath(project, path) {
    path = getAbsPath(project, path);
    return absPathClean(path);
}
function makeAllPathAbsolute(project) {
    for (var i = 0; i < project.entrypoints.length; ++i) {
        project.entrypoints[i] = makeAbsPath(project, project.entrypoints[i]);
    }
    for (var i = 0; i < project.modules.length; ++i) {
        project.modules[i].file = makeAbsPath(project, project.modules[i].file);
        var deps = project.modules[i].deps;
        for (var j = 0; j < deps.length; ++j) {
            deps[j] = makeAbsPath(project, deps[j]);
        }
    }
}
var modules = {};
var used = {};
function dfs(file) {
    used[file] = true;
    var deps = modules[file].deps;
    for (var i = 0; i < deps.length; ++i) {
        if (!used[deps[i]]) {
            dfs(deps[i]);
        }
    }
}
function fillModules(project) {
    project.modules.forEach(function (md) {
        modules[md.file] = md;
    });
}
function solution(project) {
    makeAllPathAbsolute(project);
    fillModules(project);
    for (var i = 0; i < project.entrypoints.length; ++i) {
        var entry = project.entrypoints[i];
        if (!used[entry]) {
            dfs(entry);
        }
    }
    var result = [];
    project.modules.forEach(function (md) {
        if (!used[md.file]) {
            result.push(md.file);
        }
    });
    return result.sort();
}
module.exports = solution;
