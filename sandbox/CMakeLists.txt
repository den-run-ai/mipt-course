# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(sandbox)
cmake_minimum_required(VERSION 2.6)

# List all the .h (header) files in the module
set(LIB_HXX
  dijkstra_algorithm.h
  hash.h
  list.h
  pattern.h
  stack.h
  treap.h
  red_black_tree.h
)

# List all the non-test .cpp files
set(LIB_CXX
  dijkstra_algorithm.cpp
  pattern.cpp
)

# List all the *_test.cpp files
set(TEST_CXX
  dijkstra_algorithm_test.cpp
  gmock_demo_test.cpp
  hash_test.cpp
  mocks_and_fakes_demo_test.cpp
  library_test.cpp
  list_test.cpp
  lru_cache_test.cpp
  pattern_test.cpp
  stack_test.cpp
  tdd_example_test.cpp
  treap_test.cpp
  valgrind_demo_test.cpp
  red_black_tree_test.cpp
)

# TODO(mikhail.aphanasov): Handle with platform-specific sources
# Probably needs some macro since we want this in many modules

add_executable(sandbox_tests ${TEST_CXX} ${LIB_CXX} ${LIB_HXX})
target_link_libraries(sandbox_tests base testing)
