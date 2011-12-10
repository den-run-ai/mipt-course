// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

#include "base/common.h"

#include "sandbox/fenwick_tree.h"

TEST(FenwickTreeTest, DISABLED_InsertRemoveElementsTest) {
  FenwickTree<int> fnw;
  for (int i = 0; i < 10; ++i)
    fnw.push_back(i);

  EXPECT_EQ(10u, fnw.size());
  fnw.pop_back();
  fnw.pop_back();
  EXPECT_EQ(8u, fnw.size());
  fnw.clear();
  EXPECT_EQ(0u, fnw.size());
}

TEST(FenwickTreeTest, DISABLED_CountElementsTest) {
  FenwickTree<int> fnw;
  for (int i = 0; i < 10; ++i)
    fnw.push_back(i);

  EXPECT_EQ(3, fnw.count(0, 3));
  EXPECT_EQ(45, fnw.count(0, 10));
  EXPECT_EQ(9, fnw.count(4, 6));
  EXPECT_EQ(25, fnw.count(3, 8));
  fnw.pop_back();
  fnw.pop_back();
  EXPECT_EQ(9, fnw.count(4, 6));
  EXPECT_EQ(25, fnw.count(3, 8));
}

TEST(FenwickTreeTest, DISABLED_ModifyElements) {
  FenwickTree<int> fnw;
  for (int i = 0; i < 10; ++i)
    fnw.push_back(9 - i);

  fnw.set(0, 1);
  fnw.set(1, 2);
  EXPECT_EQ(10, fnw.count(0, 3));
  fnw.set(6, 9);
  EXPECT_EQ(37, fnw.count(0, 10));
}
