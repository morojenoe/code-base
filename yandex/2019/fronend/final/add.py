import sys
import os

def write_to_file(filename, content):
  with open(filename, 'w') as file:
    file.writelines(content)

def create_solution(problem_name):
  content = [
    "module.exports = function() {\n",
    "\n",
    "}\n"
  ]
  filename = '{0}/{0}.ts'.format(problem_name)
  write_to_file(filename, content)

def create_test(problem_name):
  content = [
    "(function() {\n",
    "  const solution = require('./{0}.js');\n".format(problem_name),
    "\n",
    "  (function() {\n",
    "    let data = [1, 2, 3];\n",
    "    let res = solution(data);\n",
    "    console.log(res);\n",
    "  })();\n",
    "\n",
    "})();\n"
  ]
  filename = '{0}/{0}.test.ts'.format(problem_name)
  write_to_file(filename, content)

def create_problem(problem_name):
  os.mkdir(problem_name)
  create_solution(problem_name)
  create_test(problem_name)

if __name__ == "__main__":
  problem_name = sys.argv[1]
  create_problem(problem_name)