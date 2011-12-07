// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"
#include "base/random.h"
#include "sandbox/red_black_tree.h"
#include "sandbox/red_black_tree-inl.h"

TEST(RBTree, PutGetTest) {
  RBTree<int, int> tree;
  int value = 0;

  EXPECT_FALSE(tree.get(0, &value));

  tree.put(-1, -100);
  tree.put(0, 0);
  tree.put(1, 100);

  EXPECT_TRUE(tree.get(-1, &value));
  EXPECT_EQ(-100, value);
  EXPECT_TRUE(tree.get(0, &value));
  EXPECT_EQ(0, value);
  EXPECT_TRUE(tree.get(1, &value));
  EXPECT_EQ(100, value);

  tree.put(0, 1);
  EXPECT_TRUE(tree.get(0, &value));
  EXPECT_EQ(1, value);
}

TEST(RBTree, PutStressTest) {
  RBTree<int, int> tree;
  const int kNumberOfNodes = 1000;
  RandomGenerator rg;
  for (int i = 0; i < kNumberOfNodes; i++) {
    tree.put(i, rg.Generate<int>());
  }
}

TEST(RBTree, DISABLED_RemoveTest) {
  RBTree<int, int> tree;
  int value = 0;

  tree.put(0, 0);
  tree.put(1, 0);
  tree.put(2, 1);

  ASSERT_TRUE(tree.remove(2));
  ASSERT_FALSE(tree.get(2, &value));

  ASSERT_TRUE(tree.removeValues(0));
  ASSERT_FALSE(tree.get(0, &value));
  ASSERT_FALSE(tree.get(1, &value));

  ASSERT_FALSE(tree.remove(0));
  ASSERT_FALSE(tree.removeValues(0));
}
