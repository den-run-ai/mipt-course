# Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(sandbox)
cmake_minimum_required(VERSION 2.6)

###############################################################################
# If you want to add your new code while doing the autumn assignment
#   http://code.google.com/p/mipt-course/wiki/AutumnAssignment ,
# please add your files to the LIB_HXX, LIB_CXX and TEST_CXX lists.
# Everything else should just work.
###############################################################################

# List all the .h (header) files in the module in the alphabetic order.
set(LIB_HXX
  fenwick_tree.h
)

# List all the non-test .cpp files in the alphabetic order.
set(LIB_CXX
)

# List all the *_test.cpp files in the alphabetic order.
set(TEST_CXX
  fenwick_tree_test.cpp
  gmock_demo_test.cpp
  mocks_and_fakes_demo_test.cpp
  library_test.cpp
  lru_cache_test.cpp
  tdd_example_test.cpp
  valgrind_demo_test.cpp
)

# TODO(muxanasov): Handle platform-specific sources
# Probably needs some macro since we want this in many modules

add_executable(sandbox_tests ${TEST_CXX} ${LIB_CXX} ${LIB_HXX})
target_link_libraries(sandbox_tests base testing)
