#include <cctype>
#include <iostream>
#include <locale>
#include <stack>
#include <stdexcept>
#include <vector>
#include <sh_split.hpp>

using std::stack;
using std::vector, std::string, std::string_view;

namespace {
  // Convenience method to return the C locale.
  std::locale& c_locale() {
    static std::locale lc;
    return lc;
  }
}  // namespace

vector<string> jgcsh::lex::split_quotes(string_view cmd) {
  std::cout << "cmd = " << cmd << "\n";
  vector<string> res {};
  string cur = "";
  stack<char> quote;
  bool comment      = false;
  bool skip_ws      = true;
  bool is_expansion = false;
  for (auto i = cmd.begin(); i != cmd.end(); i++) {
    if (!comment) {
      if (!quote.empty()) {
        switch (quote.top()) {
          case '(': {
            switch (*i) {
              case ')': {
                quote.pop();
              } break;
              case '\\':
              case '\'':
              case '\"': {
                quote.push(*i);
              } break;
            }
            cur.push_back(*i);
            continue;
          }
          case '\\': {
            cur.push_back(*i);
            quote.pop();
            continue;
          }
          case '\"': {
            if (*i == '\"' && *i == quote.top()) {
              quote.pop();
            }
            else if (is_expansion && *i == '(') {
              quote.push('(');
            }
            cur.push_back(*i);
            is_expansion = (*i == '$');
            continue;
          }
          case '\'': {
            cur.push_back(*i);
            if (*i == quote.top())
              quote.pop();
            continue;
          }
        }
      }
      switch (*i) {
        case '\n':
        case ';': {
          // beginning of new statement
          res.push_back(cur);
          res.emplace_back("\n");
          cur.clear();
        } break;
        case ')': {
          throw std::runtime_error("Mismatched brackets");
        } break;
        case '\\':
        case '\'':
        case '\"': {
          // beginning of quoted value
          quote.push(*i);
        };
        default: {
          // check for ws delimiter
          if (std::isspace(*i, c_locale())) {
            if (!skip_ws) {
              res.push_back(cur);
              cur.clear();
            }
            break;
          }
          cur.push_back(*i);
          // check for a comment (# at beginning of word)
          if (cur == "#") {
            comment = true;
            cur.clear();
            break;
          }

          is_expansion = (*i == '$');
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