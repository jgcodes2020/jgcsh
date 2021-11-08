#ifndef _JGCSH_LNED__LNED_HPP_
#define _JGCSH_LNED__LNED_HPP_

#include <string>
#include <string_view>
#include <vector>

namespace jgcsh::lned {
  std::string prompt_line(const std::string& prompt, std::vector<std::string>& history);
}
#endif