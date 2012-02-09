// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>

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
  EXPECT_EQ(0, value);
}

TEST(RBTree, RemoveTest) {
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

TEST(RBTree, StressTest) {
  RBTree<int, int> tree;
  const int kNumberOfNodes = 1000;
  RandomGenerator rg;
  int value = 0;
  std::map<int, int> shadow;

  for (int i = 0; i < kNumberOfNodes; i++) {
    int key = rg.Generate<int>();
    int value = rg.Generate<int>();
    if (shadow.find(key) == shadow.end())
      shadow[key] = value;
    tree.put(key, value);
  }

  for (int i = 0; i < kNumberOfNodes; i++) {
    int key = rg.Generate<int>();
    int value = 0;
    if (shadow.count(key) == 0) {
      ASSERT_FALSE(tree.get(key, &value));
    }
    /* "else" is not needed, because all elements in shadow 
       will be checked afterwards */
  }

  typedef std::map<int, int>::iterator MapIntIntIterator;
  for (MapIntIntIterator i = shadow.begin(); i != shadow.end(); ++i) {
    const int &key = i->first;
    ASSERT_TRUE(tree.get(key, &value));

    ASSERT_EQ(i->second, value);

    tree.put(key, value + 1);
    ASSERT_TRUE(tree.get(key, &value));
    ASSERT_EQ(i->second, value);

    ASSERT_TRUE(tree.remove(key));
    ASSERT_FALSE(tree.get(key, &value));
  }
}
