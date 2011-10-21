# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(googletest)
cmake_minimum_required(VERSION 2.6)

set(LIB_CXX
  googletest_main.cpp
)

add_library(googletest ${LIB_CXX})
target_link_libraries(googletest gtest)
