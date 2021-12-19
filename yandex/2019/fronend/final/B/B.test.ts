(function() {
  const solution = require('./B.js');

  (function() {
    const servers = [  
      'srv-a', // ok  
      'srv-b', // fail  
      'srv-c', // fail  
      'srv-d'  // fail  
  ];  
   
    const check = (name: any) => new Promise((res) => setTimeout(res, 100)).then(() => name === 'srv-a' || name == 'srv-b' || name == 'srv-c');
  
    solution(servers, check).then((s: any) => console.log(s));
  })();

})();
