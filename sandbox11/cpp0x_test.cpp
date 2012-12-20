// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

#include <cstdio>

#include "base/common.h"
#include "gtest/gtest.h"

// TODO(dmitriy.borodiy): we are going to switch to C++x11 in our project.
// http://code.google.com/p/mipt-course/issues/detail?id=52
//
// This file contains tests that you can use to make sure
// you're ready for the change.
// As Google Code Style adds support to more and more C++x11 features,
// new tests cases should be added in this file. When adding new tests,
// please, keep the same order as in Google Code Style:
// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?#C++11

TEST(Cpp0xFeaturesTest, AutoTest) {
  auto d = 3;
  EXPECT_EQ(3, d);
}

TEST(Cpp0xFeaturesTest, TemplateBracketsWithoutSpacesTest) {
  std::vector<std::vector<std::string>> v;
}

TEST(Cpp0xFeaturesTest, RangeForLoopsTest) {
  std::vector<int> numbers;
  numbers.push_back(1);
  numbers.push_back(2);
  numbers.push_back(3);

  std::vector<int> squares;
  for (auto x : numbers)
    squares.push_back(x * x);

  EXPECT_EQ(1, squares[0]);
  EXPECT_EQ(4, squares[1]);
  EXPECT_EQ(9, squares[2]);
}

TEST(Cpp0xFeaturesTest, LongNumeralSuffixesTest) {
  auto d = 0xffffffffffffffffULL;
  CHECK_GE(8, sizeof(d));
}

TEST(Cpp0xFeaturesTest, VariadicMacroTest) {
#define MACRO(str, ...) std::snprintf(str, __VA_ARGS__)

  char str[256];
  str[0] = '\0';
  MACRO(str, 256, "%s %d", "What's the meaning of life?", 42);
  EXPECT_STREQ("What's the meaning of life? 42", str);
}

TEST(Cpp0xFeaturesTest, NewAlgorithmsTest) {
  std::vector<int> v(3);
  std::iota(v.begin(), v.end(), 10);
  EXPECT_EQ(10, v[0]);
  EXPECT_EQ(11, v[1]);
  EXPECT_EQ(12, v[2]);
  struct is_even {
    bool operator() (int a) {
      return a % 2 == 0;
    }
  };
  EXPECT_FALSE(std::all_of(v.begin(), v.end(), is_even()));
  EXPECT_TRUE(std::any_of(v.begin(), v.end(), is_even()));
}

TEST(Cpp0xFeaturesTest, LocalTypesAsTemplatesArgumentsTest) {
  struct Local {
    explicit Local(int xx) : x(xx) {}
    int x;
  };
  std::vector<Local> v;
  v.push_back(Local(3));
  EXPECT_EQ(3, v[0].x);
}

TEST(Cpp0xFeaturesTest, NullptrTest) {
  struct OverloadedNullPointer {
    int foo(std::nullptr_t nullp) {
      return 1;
    }
    int foo(void *ptr) {
      return 2;
    }
  } x;
  EXPECT_EQ(1, x.foo(nullptr));
  int t = 42;
  int *p = &t;
  EXPECT_EQ(2, x.foo(p));
  p = NULL;
  EXPECT_EQ(p, nullptr);
  EXPECT_EQ(2, x.foo(p));
  p = nullptr;
  EXPECT_EQ(2, x.foo(p));
}
