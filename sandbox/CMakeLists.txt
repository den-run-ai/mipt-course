# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(sandbox)
cmake_minimum_required(VERSION 2.6)

# Just like tough guys, we list files manually

set(LIB_CXX
  dijkstra_algorithm.cpp
  pattern.cpp
)

set(LIB_HXX
  avl.h
  dijkstra_algorithm.h
  hash.h
  list.h
  pattern.h
  stack.h
  treap.h
)

set(TEST_CXX
  avl_test.cpp
  dijkstra_algorithm_test.cpp
  hash_test.cpp
  library_test.cpp
  list_test.cpp
  pattern_test.cpp
  stack_test.cpp
  tdd_example_test.cpp
  treap_test.cpp
  valgrind_demo_test.cpp
)

# TODO(mikhail.aphanasov): Handle with platform-specific sources
# Probably needs some macro since we want this in many modules

add_library(sandbox ${LIB_CXX} ${LIB_HXX})
add_executable(sandbox_test ${TEST_CXX})
target_link_libraries(sandbox_test sandbox googletest)
