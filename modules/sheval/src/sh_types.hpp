#ifndef _JGCSH_SHEVAL__SH_TYPES_HPP_
#define _JGCSH_SHEVAL__SH_TYPES_HPP_
#include <filesystem>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace jgcsh::types {
  namespace fs = std::filesystem;
  struct command {
    enum class rel_opcode {
      OR_IF,
      AND_IF
    };
    struct relation {
      rel_opcode op;
      std::unique_ptr<command> cmd;
    };
    
    struct in_redir {
      fs::path path;
      int fd;
    };
    struct out_redir {
      int fd;
      fs::path path;
    };
    struct fd_redir {
      int fd_in, fd_out;
    };
    using redir = std::variant<in_redir, out_redir, fd_redir>;
    
    std::vector<std::string> args;
    std::optional<relation> rel;
  };
}
#endif