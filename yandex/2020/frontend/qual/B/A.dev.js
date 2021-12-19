"use strict";

function check(s) {
  var re = /^[A-Z]{2,8}\-\d{2,8}\/([A-Z\-]+)\/([A-Z]+)\:\{.*\}/;
  var t = re.exec(s);
  console.log(t);
  return true;
}

module.exports = function (input) {
  var result = [];
  input.forEach(function (str) {
    if (check(str)) {
      result.push(str);
    }
  });
  return result;
};