// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/stack.h"
#include "third_party/googletest/include/gtest/gtest.h"
#include "base/common.h"

TEST(StackTests, PushPopSizeTest) {
  Stack<int> stack(2);
  stack.Push(123);
  EXPECT_EQ(1u, stack.Size());
  stack.Push(456);
  EXPECT_EQ(2u, stack.Size());
  EXPECT_EQ(456, stack.Pop());
  EXPECT_EQ(123, stack.Pop());
  EXPECT_EQ(0u, stack.Size());
}

TEST(StackTests, OverflowRavageDeathTest) {
  Stack<int> stack(2);
  stack.Push(123);
  stack.Push(456);
  ASSERT_DEATH(stack.Push(789), "");
  stack.Pop();
  stack.Pop();
  ASSERT_DEATH(stack.Pop(), "");
}

