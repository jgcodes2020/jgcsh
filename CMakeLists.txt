cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(jgcsh
  LANGUAGES CXX 
  DESCRIPTION "JGCSH (jgcodes's shell) is a dumb, Unix-like shell." 
  VERSION 0.1.0 
)

add_subdirectory(modules/lned)
add_subdirectory(modules/sheval)

add_executable(jgcsh
  src/main.cpp
)

set_target_properties(jgcsh PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED true
)

target_link_libraries(jgcsh
  PRIVATE jgcsh::lned jgcsh::sheval
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)