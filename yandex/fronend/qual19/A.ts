function makeBusCatalog(names: Array<string>) {
  let result = names.reduce((catalog, name) => {
    let firstCharacter = name.length === 0? undefined : name.charAt(0);
    var bucket = '\u0410-\u042F';
    if (firstCharacter && !Number.isNaN(Number.parseInt(firstCharacter, 10))) {
      bucket = firstCharacter;
    }
    let bucketArray = catalog.get(bucket) || [];
    bucketArray.push(name);
    catalog.set(bucket, bucketArray);
    return catalog;
  }, new Map<String, Array<string>>());
  let returnValue = Array.from(result.entries())
    .map(value => {
      let newArray = value[1].slice();
      newArray.unshift(value[0].toString());
      return newArray;
    })
    .filter(value => value.length > 1);
  returnValue.sort((a, b) => {
    if (a[0] < b[0]) return -1;
    if (a[0] > b[0]) return 1;
    return 0;
  })
  return returnValue;
}

module.exports = makeBusCatalog;

function test() {
  console.log(makeBusCatalog(["101", "215", "М5", "241"]));
  // console.log(makeBusCatalog([""]));
}
test();
