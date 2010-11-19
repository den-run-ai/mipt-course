// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <math.h>

#include "third_party/googletest/include/gtest/gtest.h"

#include "base/common.h"

int Factorial(int v) {
  // NB we wrote the implementation of this function on the lecture;
  // before the lecture it was simply "return -1;"

  CHECK(v >= 0);
  // TODO(timurrrr): CHECK(v < MAX_FACTORIAL);
  // We can get past (2^31 - 1)
  if (v <= 1)
    return 1;

  // TODO(timurrrr): don't use recursion.
  return v * Factorial(v - 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(1, Factorial(1));
  EXPECT_EQ(2, Factorial(2));
  EXPECT_EQ(6, Factorial(3));
  EXPECT_EQ(40320, Factorial(8));
}

// Tests factorial of 0.
// "Corner case test"
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(1, Factorial(0));
}

TEST(FactorialTest, FailsOnNegativeInputDeathTest) {
  // Suppress the "fork() is unsafe" warnings
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(Factorial(-1), "");
}
