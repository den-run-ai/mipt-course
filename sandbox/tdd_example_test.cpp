// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <math.h>

#include "gtest/gtest.h"

#include "base/common.h"

const int kMaxFactorial = 13;

int Factorial(int v) {
  // NB we wrote the implementation of this function on the lecture;
  // before the lecture it was simply "return -1;"

  CHECK_GE(v, 0);
  CHECK_LT(v, kMaxFactorial);

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
  EXPECT_EQ(479001600, Factorial(12));
}

// Tests factorial of 0.
// "Corner case test"
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(1, Factorial(0));
}

// Tests factorial of number that will cause integer type overflow.
TEST(FactorialTest, FailsOnTooBigInputDeathTest) {
    ASSERT_DEATH(Factorial(13), "");
    ASSERT_DEATH(Factorial(42), "");
}

TEST(FactorialTest, FailsOnNegativeInputDeathTest) {
  ASSERT_DEATH(Factorial(-1), "");
}

TEST(FailureTest, WillRemove) {
  ASSERT_EQ(1, 2);
}
