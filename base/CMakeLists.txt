# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(base)
cmake_minimum_required(VERSION 2.6)

find_package(Threads)

# Just like tough guys, we list files manually

# List all the .h (header) files in the module in the alphabetic order.
set(LIB_HXX
  common.h
  condition_variable.h
  file_utils.h
  mutex.h
  random.h
)

# List all the non-test .cpp files in the alphabetic order.
set(LIB_CXX
  condition_variable.cpp
  file_utils.cpp
  mutex.cpp
)

# List all the *_test.cpp files in the alphabetic order.
set(TEST_CXX
  check_test.cpp
  common_test.cpp
)

# TODO(muxanasov): Handle platform-specific sources
# Probably needs some macro since we want this in many modules

add_library(base ${LIB_CXX} ${LIB_HXX})
add_executable(base_tests ${TEST_CXX})
target_link_libraries(base_tests base testing)
