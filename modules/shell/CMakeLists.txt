project(jgcsh_shell
  LANGUAGES CXX
  DESCRIPTION "The core shell."
  VERSION 0.1.0
)

add_executable(jgcsh
  src/main.cpp
)

set_target_properties(jgcsh PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED true
)
