cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(jgcsh_shntax 
  LANGUAGES CXX
  DESCRIPTION "A parser for shell syntax."
  VERSION 0.1.0
)

add_library(jgcsh_lned
  src/lned.cpp
)
add_library(jgcsh::lned ALIAS jgcsh_lned)

set_target_properties(jgcsh_lned PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED true
)

target_include_directories(jgcsh_lned
  PUBLIC include
  PRIVATE src
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)