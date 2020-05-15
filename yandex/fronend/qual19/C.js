let dictionary;
module.exports = function (inputData, inputDictionary) {
  dictionary = new Set(inputDictionary);
  if (!inputData.every(data => dictionary.has(data.text))) {
    return "Unreadable message";
  }

  inputData.sort((lft, rgh) => lft.geometry[0] - rgh.geometry[0]);

  return inputData.map(item => item.text).join(' ');
}

const data = [  
  {  
      geometry: [10, 20],  
      text: "James"
  },  
  {  
      geometry: [20, 40],  
      text: "Bond" 
  },  
  {  
      geometry: [5, 40],  
      text: "Bond"
  }  
];  
const dictionary2 = ["James", "Bond", ""];

console.log(module.exports([], dictionary2));
