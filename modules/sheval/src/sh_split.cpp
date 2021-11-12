#include <cctype>
#include <iostream>
#include <locale>
#include <vector>
#include <sh_split.hpp>

using std::vector, std::string, std::string_view;

vector<string> jgcsh::lex::split_quotes(string_view cmd) {
  std::cout << "cmd = " << cmd << "\n";
  vector<string> res {};
  string cur = "";
  char quote = '\0';
  for (auto i = cmd.begin(); i != cmd.end(); i++) {
    switch (quote) {
      case '\\': {
        cur.push_back(*i);
        quote = '\0';
      } break;
      case '\'':
      case '\"': {
        cur.push_back(*i);
        if (*i == quote) quote = '\0';
      } break;
      default: {
        if (std::isspace(*i, std::locale())) {
          res.push_back(cur);
          cur.clear();
          break;
        }
        switch (*i) {
          case '\\':
          case '\'':
          case '\"': {
            quote = *i;
          }
          default: {
            cur.push_back(*i);
          }
        }
      } break;
    }
  }
  if (!cur.empty()) res.push_back(cur);
  return res;
}