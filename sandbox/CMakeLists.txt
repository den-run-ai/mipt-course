# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(sandbox)
cmake_minimum_required(VERSION 2.6)

# List all the .h (header) files in the module in the alphabetic order.
set(LIB_HXX
  dijkstra_algorithm.h
  fenwick_tree.h
  hash.h
  labyrinth.h
  list.h
  pattern.h
  red_black_tree.h
  red_black_tree-inl.h
  stack.h
  treap.h
)

# List all the non-test .cpp files in the alphabetic order.
set(LIB_CXX
  dijkstra_algorithm.cpp
  labyrinth.cpp
  pattern.cpp
)

# List all the *_test.cpp files in the alphabetic order.
set(TEST_CXX
  dijkstra_algorithm_test.cpp
  fenwick_tree_test.cpp
  gmock_demo_test.cpp
  hash_test.cpp
  math_expression_calculator_test.cpp
  mocks_and_fakes_demo_test.cpp
  labyrinth_test.cpp
  library_test.cpp
  list_test.cpp
  lru_cache_test.cpp
  pattern_test.cpp
  red_black_tree_test.cpp
  stack_test.cpp
  sudoku_solver_test.cpp
  tdd_example_test.cpp
  treap_test.cpp
  valgrind_demo_test.cpp
)

# TODO(mikhail.aphanasov): Handle platform-specific sources
# Probably needs some macro since we want this in many modules

add_executable(sandbox_tests ${TEST_CXX} ${LIB_CXX} ${LIB_HXX})
target_link_libraries(sandbox_tests base testing)
