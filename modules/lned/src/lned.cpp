#include <cctype>
#include <iostream>
#include <istream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <jgcsh/lned/lned.hpp>

#include <termios.h>
#include <unistd.h>

using std::cout, std::cin, std::flush;
using std::string_view, std::vector, std::string;

namespace {
  struct raw_input_guard {
    termios old_tm;
    raw_input_guard() {
      tcgetattr(STDOUT_FILENO, &old_tm);
      termios new_tm = old_tm;
      new_tm.c_lflag &= ~(ECHO | ICANON);
      tcsetattr(STDOUT_FILENO, TCSANOW, &new_tm);
    }
    ~raw_input_guard() { tcsetattr(STDOUT_FILENO, TCSANOW, &old_tm); }
  };
}  // namespace

namespace jgcsh::lned {
  std::string prompt_line(const std::string& prompt, vector<string>& history) {
    raw_input_guard __input_guard__;

    cout << prompt << flush;

    std::string buffer;
    uint32_t pos = 0;
    char next;
    while (cin.get(next) && next != '\n') {
      // handle special keys
      if (next == '\x1B') {
        cin.get(next);
        switch (next) {
          case '[': {
            cin.get(next);
            switch (next) {
              // Arrow up
              case 'A': {
                cout << "\a" << flush;
              } break;
              // Arrow down
              case 'B': {
                cout << "\a" << flush;
              } break;
              // Arrow left
              case 'C': {
                if (pos < buffer.size()) {
                  cout << "\x1B[C" << flush;
                  pos++;
                }
                else {
                  cout << "\a" << flush;
                }
              } break;
              // Arrow right
              case 'D': {
                if (pos > 0) {
                  cout << "\x1B[D" << flush;
                  pos--;
                }
                else {
                  cout << "\a" << flush;
                }
              } break;
              case 'F': {
                if (pos < buffer.size()) {
                  cout << "\x1B[" << (buffer.size() - pos) << "C" << flush;
                  pos = buffer.size();
                }
              } break;
              case 'H': {
                if (pos > 0) {
                  cout << "\x1B[" << pos << "D" << flush;
                  pos = 0;
                }
              } break;
              default: {
                // parse numbers
                char c;
                std::istream::sentry sentry = std::istream::sentry(cin);
                if (sentry) {
                  std::vector<uint32_t> values;
                  uint32_t curr = 0;
                  char endc;
                  while (cin.get(c) && ((c >= '0' && c <= '9') || c == ';')) {
                    if (c >= '0' && c <= '9') {
                      curr *= 10;
                      curr += uint8_t(c) & 0x0F;
                    }
                    else {
                      values.push_back(curr);
                      curr = 0;
                    }
                  }
                  endc = c;
                }
                // interpret generic ANSI sequence
              }
            }
          } break;
          // Catch F1-F4
          case 'O': {
            cin.get(next);
            switch (next) {
              case 'P': {
              } break;
              case 'Q': {
              } break;
              case 'R': {
              } break;
              case 'S': {
              } break;
            }
          } break;
          // Catch other extended keys 
          default: {
          } break;
        }
      }
      else if (next == '\x7F' || next == '\x08') {
        if (pos == 0) {
          cout << "\a" << flush;
        }
        else {
          // push cursor back and clear part of line
          // that will be reprinted
          cout << "\x1B[D\x1B[0K";
          buffer.erase(--pos, 1);
          // reprint that portion of the string
          size_t len = buffer.size() - pos;
          cout.write(buffer.data() + pos, len);
          // move back to correct spot.
          // Ideally the extra jank isn't necessary
          // not too sure how to get rid of it
          cout << "\x1B[" << len << "D";
          if (pos == buffer.size())
            cout << "\x1B[C";
          cout.flush();
        }
      }
      else if (isprint(next)) {
        // insert next character
        buffer.insert(pos++, 1, next);
        // print next character
        cout << next;
        if (pos < buffer.size()) {
          size_t len = buffer.size() - pos;
          // reprint remainder of string
          cout.write(buffer.data() + pos, len);
          cout << "\x1B[" << len << "D" << flush;
        }
      }
    }
    // newline detected, exit prompt
    cout << "\n";
    return buffer;
  }
}  // namespace jgcsh::lned