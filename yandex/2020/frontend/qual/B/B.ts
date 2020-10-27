function check(s: string): boolean {
  const re = /^[A-Z]{2,8}\-\d{2,8}\/([A-Z\-]+)\/([A-Z]+)\:\{.*\}/;
  const t = re.exec(s);
  if (!t) {
    return false;
  }
  
  const system = t[1];
  const planet = t[2];
  if (system[0] === '-' || system[system.length - 1] === '-' || system.includes('--')) {
    return false;
  }
  if (planet.includes('UNDEFINED')) {
    return false;
  }
  return true;
}

module.exports = function(input: string[]) {
  
  let result: string[] = [];
  input.forEach(str => {
    if (check(str)) {
      result.push(str);
    }
  });

  result = result.map(s => {
    while (s.indexOf('@') != -1) {
      let r = '';
      const first = s.indexOf('@');
      r = s.slice(0, first);
      r += '<fake>';
      r += s.slice(first + 1);
      s = r;
      const second = s.indexOf('@');
      r = s.slice(0, second);
      r += '<\/fake>';
      r += s.slice(second + 1);
      s = r;
    }
    return s;
  })

  return result;
}
