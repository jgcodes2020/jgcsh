#include <iomanip>
#include <iostream>
#include <jgcsh/lned/lned.hpp>
#include <sh_split.hpp>
#include "stringify.hpp"

namespace lned = jgcsh::lned;

using std::cout;

char hex_lookup[16] = {
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
};

int main() {
  std::string line;
  while ((line = lned::prompt_line(
            "Input line: ", *(std::vector<std::string>*) 0)) != "exit") {
    cout << jgcsh::lex::split_quotes(line) << "\n";
    cout << std::endl;
  }
  cout << "Goodbye\n";
}