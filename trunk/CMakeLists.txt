# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

set(CMAKE_CXX_COMPILER "g++")

project(GMC)
cmake_minimum_required(VERSION 2.6)

# CMAKE_BUILD_TYPE={Release|Debug|Coverage}
# TODO(muxanasov): support flags RelWithDebInf & MinSizeRel
# when needed. For more flexible flags control
# see http://codereview.appspot.com/5432049/#ps5002

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_COVERAGE "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_COVERAGE "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -lgcov")

# TODO(muxanasov): Support case-insensitive check of build type when needed
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  # TODO(muxanasov): add additional flags to Debug build when needed
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  # TODO(muxanasov): add additional flags to Release build when needed
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
  add_custom_target(extract_coverage COMMAND ${CMAKE_COMMAND}
    -DSEARCH_DIR=${CMAKE_BINARY_DIR}
    -P ${GMC_SOURCE_DIR}/extract_coverage.cmake
  )
  add_custom_target(reset_coverage
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/CoverageResults
    COMMAND lcov --directory ${CMAKE_BINARY_DIR} --zerocounters
  )
else ()
  message(FATAL_ERROR "No such build type. Please use one of the following:
    \n Release\n Debug\n Coverage"
  )
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(prj_src ${GMC_SOURCE_DIR})

# Order of the modules is very important, because "testing" uses libgtest from
# third_party/googletest/; "sandbox" & "base" use libgoogletest from "testing"

set(modules
  third_party/googlemock/
  testing
  sandbox
  base
)

set(tests
  sandbox
  base
)

include_directories(
  # TODO(timurrrr): check gtest's -I doesn't conflict with the system gtest if
  # it is installed.
  ${prj_src}/third_party/googlemock/gtest/include
  ${prj_src}/third_party/googlemock/include
  ${prj_src}
)

# Print all warnings and treat them as errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

foreach (module ${modules})
  message(STATUS " * Preparing ${module} module...")
  add_subdirectory(${module})
endforeach (module)

add_custom_target(build COMMAND make)

###############################################################################
# Preparing valgrind test
# TODO(muxanasov): It should be platform-specific

set(valgrind_cmd valgrind)
set(valgrind_prefix
  "--leak-check=full --error-exitcode=255 \\
  --suppressions=${prj_src}/testing/valgrind_suppressions.txt"
)
set(valgrind_suffix "--gtest_filter=\"-*Death*\"")

foreach (test ${tests})
  set(test_cmd
    "${test_cmd} && ${CMAKE_BINARY_DIR}/${test}_tests"
  )

  set(valgrind_test_cmd
    "${valgrind_test_cmd} && ${valgrind_cmd} ${valgrind_prefix} \\
    ${CMAKE_BINARY_DIR}/${test}_tests ${valgrind_suffix}"
  )
endforeach (test)

# In order to track and use command-line arguments we generate sh-script which
# catches arguments and performs different lines of commands.
# See http://goo.gl/yY5Rb

file(WRITE $ENV{PWD}/valgrind.sh
  "#!/bin/sh
  if [ $1 ] && [ $1 -eq 1 ];
  then make ${valgrind_test_cmd};
  else make ${test_cmd};
  fi"
)

add_custom_target(test COMMAND sh $ENV{PWD}/valgrind.sh $(USE_VALGRIND))
