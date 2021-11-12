cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(jgcsh_sheval 
  LANGUAGES CXX
  DESCRIPTION "A parser for shell syntax."
  VERSION 0.1.0
)

add_library(jgcsh_sheval
  src/sh_split.cpp
)
add_library(jgcsh::sheval ALIAS jgcsh_sheval)

set_target_properties(jgcsh_sheval PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED true
)

target_include_directories(jgcsh_sheval
  PUBLIC include
  PRIVATE src
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)