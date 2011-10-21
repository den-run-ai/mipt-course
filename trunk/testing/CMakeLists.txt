project(googletest)
cmake_minimum_required(VERSION 2.6)

set(LIB_CXX
  googletest_main.cpp
)

add_library(googletest ${LIB_CXX})
target_link_libraries(googletest gtest)
