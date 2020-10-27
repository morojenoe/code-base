interface PModule {
  file: string;
  deps: string[];
}

interface Project {
  absoluteRepoPath: string;
  aliases: { [alas: string]: string };
  entrypoints: string[];
  modules: PModule[];
};

function getAbsPath(project: Project, path: string) {
  if (path.startsWith('/')) {
    return path;
  }
  if (path.startsWith('./')) {
    return project.absoluteRepoPath + path.slice(1);
  }
  if (path.startsWith('..')) {
    return project.absoluteRepoPath + '/' + path;
  }
  let i = path.indexOf('/');
  if (i === -1) {
    i = path.length;
  }
  const alias = path.slice(0, i);
  return getAbsPath(project, project.aliases[alias] + path.slice(i));
}

function absPathClean(path: string) {
  while (path.includes('//')) {
    const index = path.indexOf('//');
    path = path.slice(0, index) + path.slice(index + 1);
  }
  if (path.includes('..')) {
    let index = path.indexOf('../');
    index -= 2;
    const indexSlash = path.lastIndexOf('/', index);
    let res = path.slice(0, indexSlash);
    res += path.slice(index + 4);
    return absPathClean(res);
  }
  return path;
}

function makeAbsPath(project: Project, path: string) {
  path = getAbsPath(project, path);
  return absPathClean(path);
}

function makeAllPathAbsolute(project: Project) {
  for (let i = 0; i < project.entrypoints.length; ++i) {
    project.entrypoints[i] = makeAbsPath(project, project.entrypoints[i]);
  }
  for (let i = 0; i < project.modules.length; ++i) {
    project.modules[i].file = makeAbsPath(project, project.modules[i].file);
    const deps = project.modules[i].deps;
    for (let j = 0; j < deps.length; ++j) {
      deps[j] = makeAbsPath(project, deps[j]);
    }
  }
}

let modules: { [file: string]: PModule } = {};
const used: { [file: string]: boolean } = {};

function dfs(file: string) {
  used[file] = true;
  const deps = modules[file].deps;
  for (let i = 0; i < deps.length; ++i) {
    if (!used[deps[i]]) {
      dfs(deps[i]);
    }
  }
}

function fillModules(project: Project) {
  project.modules.forEach(md => {
    modules[md.file] = md;
  });
}

function solution(project: Project) {
  makeAllPathAbsolute(project);
  fillModules(project);
  for (let i = 0; i < project.entrypoints.length; ++i) {
    const entry = project.entrypoints[i];
    if (!used[entry]) {
      dfs(entry);
    }
  }

  const result = [];
  project.modules.forEach(md => {
    if (!used[md.file]) {
      result.push(md.file);
    }
  });
  return result.sort();
}

module.exports = solution;
