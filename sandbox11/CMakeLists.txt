# Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(sandbox11)
cmake_minimum_required(VERSION 2.6)

###############################################################################
# If you want to add your new code while doing the autumn assignment
#   http://code.google.com/p/mipt-course/wiki/AutumnAssignment ,
# please add your files to the LIB_HXX, LIB_CXX and TEST_CXX lists.
# Everything else should just work.
###############################################################################

# Enable C++0x support
# TODO(timurrrr): Find out whether -Wall and -Werror are needed here.
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-strict-aliasing -std=c++0x")

# List all the .h (header) files in the module in the alphabetic order.
set(LIB_HXX
  lzw.h
)

# List all the non-test .cpp files in the alphabetic order.
set(LIB_CXX
  lzw.cpp
)

# List all the *_test.cpp files in the alphabetic order.
set(TEST_CXX
  cpp0x_test.cpp
  lzw_test.cpp
)

# TODO(muxanasov): Handle platform-specific sources
# Probably needs some macro since we want this in many modules

add_executable(sandbox11_tests ${TEST_CXX} ${LIB_CXX} ${LIB_HXX})
target_link_libraries(sandbox11_tests base testing)
