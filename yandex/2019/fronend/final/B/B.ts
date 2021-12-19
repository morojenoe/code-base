function go(L: number, R: number, servers: any, check: any): Promise<string> {
  console.log(L, R);
  if (L + 1 >= R) {
    return Promise.resolve(servers[R]);
  }
  let M = Math.floor((L + R) / 2);
  let name = servers[M];
  return check(name).then((value: any) => {
    if (value) {
      // L = M;
      return go(M, R, servers, check);
    } else {
      // R = M;
      return go(L, M, servers, check);
    }
  });
}

module.exports = function (servers: Array<string>, check: any) {
  let L = -1, R = servers.length - 1;

  return go(L, R, servers, check);
};