// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"
#include "sandbox/red_black_tree.h"

TEST(RBTreeTest, DISABLED_PutTest) {
  RBTree<int, int> tree;

  tree.put(-1, -100);
  tree.put(0, 0);
  tree.put(1, 100);

  EXPECT_EQ(-100, tree.get(-1));
  EXPECT_EQ(0, tree.get(0));
  EXPECT_EQ(100, tree.get(1));
}

TEST(RBTreeTest, DISABLED_RemoveTest) {
  RBTree<int, int> tree;

  tree.put(0, 0);
  tree.put(1, 0);
  tree.put(2, 1);

  ASSERT_TRUE(tree.remove(2));
  ASSERT_FALSE(tree.get(2));

  ASSERT_TRUE(tree.removeValues(0));
  ASSERT_FALSE(tree.get(0));
  ASSERT_FALSE(tree.get(1));

  ASSERT_FALSE(tree.remove(0));
  ASSERT_FALSE(tree.removeValues(0));
}
