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

add_executable(currency test-bellman.cpp)