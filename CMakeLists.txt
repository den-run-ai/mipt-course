set(CMAKE_CXX_COMPILER "g++")

project(GMC)
cmake_minimum_required(VERSION 2.6)

if (Release)
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
  else ()
    if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
      # Reseting cmake flags makes Debug build by default, but one should 
      # constantly define build flag if he wants to build Release.
      #  CACHE indicates we are working with cache
      #  FORCE overrides user selections or previous versions in cache
      # See for details: http://goo.gl/Aj0A4
      set(CMAKE_BUILD_TYPE "" CACHE STRING "" FORCE)
      set(Release "" CACHE UNINITIALIZED "" FORCE)
      message(FATAL_ERROR "Conflicting CMAKE_BUILD_TYPE and Release values")
    endif ()
  endif ()
else ()
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
  endif ()
endif ()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(prj_src ${GMC_SOURCE_DIR})

# Order of the modules is very important, because "testing" uses libgtest from 
# third_party/googletest/; "sandbox" & "base" use libgoogletest from "testing"

set(modules
  third_party/googletest/
  testing
  sandbox
  base
)

set(tests
  sandbox
  base
)

include_directories(
  ${prj_src}/third_party/googletest/include
  ${prj_src}
)

# Print all warnings and treat them as errors
# TODO(Mikhail.Aphanasov): enable this when compiler warning are fixed on newer
# g++ versions
#set(CMAKE_CXX_FLAGS "-Wall -Werror")

foreach (module ${modules})
  message(STATUS " * Preparing ${module} module...")  
  add_subdirectory(${module})  
endforeach (module)

add_custom_target(build COMMAND make)

###############################################################################
# Preparing valgrind test
# TODO(mikhail.aphanasov): It should be platform-specific

set(valgrind_cmd valgrind)
set(valgrind_prefix 
  "--leak-check=full --error-exitcode=255 \\
  --suppressions=${prj_src}/testing/valgrind_suppressions.txt"
)
set(valgrind_suffix "--gtest_filter=\"-*Death*\"")

foreach (test ${tests})
  set(test_cmd 
    "${test_cmd} && ${CMAKE_BINARY_DIR}/${test}_test"
  )

  set(valgrind_test_cmd
    "${valgrind_test_cmd} && ${valgrind_cmd} ${valgrind_prefix} \\
    ${CMAKE_BINARY_DIR}/${test}_test ${valgrind_suffix}"
  )
endforeach (test)

file(WRITE $ENV{PWD}/valgrind.sh
  "#!/bin/sh
  if [ $1 ] && [ $1 -eq 1 ];
  then make ${valgrind_test_cmd}; 
  else make ${test_cmd}; 
  fi"
)

add_custom_target(test COMMAND sh $ENV{PWD}/valgrind.sh $(USE_VALGRIND))

###############################################################################
# Reseting cmake flags makes Debug build by default, but one should constantly
# define build flag if he wants to build Release.
#  CACHE indicates we are working with cache
#  FORCE overrides user selections or previous versions in cache
# See for details: http://goo.gl/Aj0A4

set(CMAKE_BUILD_TYPE "" CACHE STRING "" FORCE)
set(Release "" CACHE UNINITIALIZED "" FORCE)
