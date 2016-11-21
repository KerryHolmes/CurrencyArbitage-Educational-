# Copyright (c) 2016 Andrew Sutton
# All rights reserved

cmake_minimum_required(VERSION 3.0)
project(currency CXX)

enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++1z -fconcepts")

add_library(graph
  utility.cpp
  common.cpp
  graph.cpp
  digraph.cpp
  output.cpp
  dfs.cpp
  queue.cpp
)

add_executable(network test-bellman.cpp)

set(files bellman.hpp bellman.cpp digraph.hpp test-bellman.cpp)

add_custom_target(printout
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND a2ps -Afill -o- ${files} | ps2pdf - ${CMAKE_BINARY_DIR}/printout.pdf)