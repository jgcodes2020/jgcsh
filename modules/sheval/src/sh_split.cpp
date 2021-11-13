#include <cctype>
#include <iostream>
#include <locale>
#include <vector>
#include <sh_split.hpp>

using std::vector, std::string, std::string_view;

namespace {
  // Convenience method to return the C locale.
  std::locale& c_locale() {
    static std::locale lc;
    return lc;
  }
}

vector<string> jgcsh::lex::split_quotes(string_view cmd) {
  std::cout << "cmd = " << cmd << "\n";
  vector<string> res {};
  string cur   = "";
  char quote   = '\0';
  bool comment = false;
  // if true, don't push token
  bool skip_ws = true;
  for (auto i = cmd.begin(); i != cmd.end(); i++) {
    if (!comment) {
      switch (quote) {
        case '\\': {
          cur.push_back(*i);
          quote = '\0';
        } break;
        case '\'':
        case '\"': {
          cur.push_back(*i);
          if (*i == quote)
            quote = '\0';
        } break;
        default: {
          switch (*i) {
            case '\n':
            case ';': {
              res.push_back(cur);
              res.emplace_back("\n");
              cur.clear();
            } break;
            case '\\':
            case '\'':
            case '\"': {
              quote = *i;
            };
            default: {
              if (std::isspace(*i, c_locale())) {
                if (!skip_ws) {
                  res.push_back(cur);
                  cur.clear();
                }
                break;
              }
              cur.push_back(*i);
              // comments only apply at the beginning of a word
              if (cur == "#") {
                comment = true;
                cur.clear();
                continue;
              }
            } break;
          }
        } break;
      }
      skip_ws = (std::isspace(*i, c_locale()) || *i == ';');
    }
    else {
      comment = (*i != '\n');
      skip_ws = true;
    }
  }
  if (!cur.empty())
    res.push_back(cur);
  return res;
}