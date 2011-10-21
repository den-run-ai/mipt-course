# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(base)
cmake_minimum_required(VERSION 2.6)

find_package(Threads)

# Just like tough guys, we list files manually

set(LIB_CXX
  condition_variable.cpp
  file_utils.cpp
  mutex.cpp
)

set(LIB_HXX
  common.h
  condition_variable.h
  file_utils.h
  mutex.h
  random.h
)

set(TEST_CXX
  check_test.cpp
)

# TODO(mikhail.aphanasov): Handle with platform-specific sources
# Probably needs some macro since we want this in many modules

add_library(base ${LIB_CXX} ${LIB_HXX})
add_executable(base_test ${TEST_CXX})
target_link_libraries(base_test base googletest)
