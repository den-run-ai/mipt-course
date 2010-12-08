// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/avl.h"

#include "third_party/googletest/include/gtest/gtest.h"

class AVLIntTest : public :: testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
  AVLTree<int> tree;
};

TEST_F(AVLIntTest, DISABLED_IntManipulation) {
  ASSERT_TRUE(tree.Add(33));
  ASSERT_TRUE(tree.Add(3984333));
  ASSERT_TRUE(tree.Add(2385933));
  ASSERT_TRUE(tree.Add(334573));
  ASSERT_TRUE(tree.Add(383));
  ASSERT_TRUE(tree.Add(356823));
  ASSERT_TRUE(tree.Add(6733));
  ASSERT_TRUE(tree.Add(33473));
  ASSERT_TRUE(tree.Add(545));
  ASSERT_TRUE(tree.Add(3));
  ASSERT_EQ(NULL, tree.Find(23));
  ASSERT_TRUE(tree.Find(33) != NULL);
  tree.Delete(33);
  ASSERT_DEATH(tree.Delete(33), ".*");
  ASSERT_EQ(NULL, tree.Find(33));
}

class AVLMapTest : public :: testing::Test {
 protected:
  virtual void SetUp() {
    a = KeyValuePair<int, char>(1, 'a');
    b = KeyValuePair<int, char>(2, 'b');
    c = KeyValuePair<int, char>(3, 'c');
    d = KeyValuePair<int, char>(4, 'd');
  }

  virtual void TearDown() { }
  AVLMap<int, char> tree;
  KeyValuePair<int, char> a, b, c, d;
};

TEST_F(AVLMapTest, DISABLED_CustomClassHandling) {
  ASSERT_EQ(a.key(), 1);
  ASSERT_EQ(c.data(), 'c');
  ASSERT_TRUE(tree.Add(a));
  ASSERT_TRUE(tree.Add(d));
  ASSERT_TRUE(tree.Add(c));
  ASSERT_TRUE(tree.Add(b));
  ASSERT_TRUE(tree.Add(a));  // I see nothing bad in having equal keys
  ASSERT_TRUE(tree.Find(a) != NULL);
  ASSERT_TRUE(tree.Find(b) != NULL);
  ASSERT_TRUE(tree.Find(c) != NULL);
  ASSERT_TRUE(tree.Find(d) != NULL);
  tree.Delete(a);
  ASSERT_TRUE(tree.Find(a) != NULL);
  tree.Delete(a);
  ASSERT_EQ(NULL, tree.Find(a));
  ASSERT_TRUE(tree.Find(b) != NULL);
  ASSERT_TRUE(tree.Find(c) != NULL);
  ASSERT_TRUE(tree.Find(d) != NULL);
  ASSERT_DEATH(tree.Delete(a), ".*");
  ASSERT_EQ(NULL, tree.Find(a));
}

