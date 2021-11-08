#include <iomanip>
#include <iostream>
#include <jgcsh/lned/lned.hpp>

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
    for (char c : line) {
      if (c < ' ' || c == '\x7F') {
        uint16_t i = static_cast<uint16_t>(static_cast<uint8_t>(c));
        cout << "\\x" << hex_lookup[(i >> 4) & 0x0F] << hex_lookup[i & 0x0F];
      }
      else {
        cout.put(c);
      }
    }
    cout << std::endl;
  }
  cout << "Goodbye\n";
}