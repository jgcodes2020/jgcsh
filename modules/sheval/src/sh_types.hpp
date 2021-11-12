#ifndef _JGCSH_SHEVAL__SH_TYPES_HPP_
#define _JGCSH_SHEVAL__SH_TYPES_HPP_
#include <filesystem>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace jgcsh::types {
  struct command {
    std::vector<std::string> args;
  };
}
#endif