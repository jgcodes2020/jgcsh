#ifndef _JGCSH_SHEVAL__SH_SPLIT_HPP_
#define _JGCSH_SHEVAL__SH_SPLIT_HPP_
#include <string>
#include <string_view>
#include <vector>

namespace jgcsh::lex {
  /**
   * @brief First round of splitting, using quotes.
   *
   * @param cmd the shell command
   * @return std::vector<std::string> the preliminary arguments.
   */
  std::vector<std::string> split_quotes(std::string_view cmd);
  
  /**
   * @brief Second round of splitting, isolating unquoted operators.
   * 
   * @param toks the tokens from split_quotes
   */
  void isolate_operators(std::vector<std::string>& toks);
}  // namespace jgcsh::lex
#endif