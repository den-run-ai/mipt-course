// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/avl.h"

#include <set>

#include "base/random.h"
#include "third_party/googletest/include/gtest/gtest.h"

class AVLIntTest : public :: testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
  AVLTree<int> tree;
  std::multiset<int> set_multiset;  // multi, as we allow equal keys
};

TEST_F(AVLIntTest, SimpleIntManipulation) {
  ASSERT_TRUE(tree.Add(356823));
  ASSERT_TRUE(tree.Add(3300));
  ASSERT_TRUE(tree.Add(398));
  ASSERT_TRUE(tree.Add(233));
  ASSERT_TRUE(tree.Add(13));
  ASSERT_TRUE(tree.Add(38));
  ASSERT_TRUE(tree.Add(673));
  ASSERT_TRUE(tree.Add(33473));
  ASSERT_TRUE(tree.Add(54));
  ASSERT_TRUE(tree.Add(3));
  ASSERT_EQ(3300, *(tree.Find(3300)));
  ASSERT_EQ(38, *(tree.Find(38)));
  ASSERT_EQ(NULL, tree.Find(23));
  ASSERT_EQ(NULL, tree.Find(3301));
  ASSERT_EQ(3, *(tree.Find(3)));
  ASSERT_EQ(13, *(tree.Find(13)));
  ASSERT_TRUE(tree.Add(13));
  tree.Delete(13);
  ASSERT_EQ(13, *(tree.Find(13)));
  tree.Delete(13);
  ASSERT_EQ(NULL, tree.Find(13));
  tree.Delete(233);
  ASSERT_EQ(NULL, tree.Find(233));
}

TEST_F(AVLIntTest, DeleteNonexistentItemDeathTest) {
  ASSERT_TRUE(tree.Add(356823));
  ASSERT_TRUE(tree.Add(3300));
  ASSERT_TRUE(tree.Add(398));
  ASSERT_DEATH(tree.Delete(0), "CHECK failed");
}

TEST_F(AVLIntTest, MirrorCustom) {
  ASSERT_TRUE(tree.Add(4));
  ASSERT_TRUE(tree.Add(3));
  ASSERT_TRUE(tree.Add(2));
  ASSERT_TRUE(tree.Add(1));
  ASSERT_TRUE(tree.Add(1));
  ASSERT_TRUE(tree.Find(1) != NULL);
  tree.Delete(1);
  ASSERT_TRUE(tree.Find(1) != NULL);
  tree.Delete(1);
  ASSERT_TRUE(tree.Find(2) != NULL);
  ASSERT_EQ(NULL, tree.Find(1));
  ASSERT_TRUE(tree.Find(2) != NULL);
  ASSERT_TRUE(tree.Find(3) != NULL);
  ASSERT_TRUE(tree.Find(4) != NULL);
  ASSERT_EQ(NULL, tree.Find(1));
}

TEST_F(AVLIntTest, SetTest) {
  int Action, Number;
  RandomGenerator gen(123124);
  for (int i = 1; i < 10000; i++) {
    Action = gen.Generate<int>() % 2;
    Number = gen.Generate<int>() % 100;
    if (Action) {
      set_multiset.insert(Number);
      ASSERT_TRUE(tree.Add(Number));
    } else {
      if (set_multiset.count(Number)) {
        ASSERT_EQ(Number, *(tree.Find(Number)));
      } else {
        ASSERT_EQ(NULL, tree.Find(Number));
      }
    }
  }
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


TEST_F(AVLMapTest, CustomClassHandling) {
  ASSERT_EQ(1, a.key());
  ASSERT_EQ('c', c.data());
  ASSERT_TRUE(tree.Add(d));
  ASSERT_TRUE(tree.Add(c));
  ASSERT_TRUE(tree.Add(b));
  ASSERT_TRUE(tree.Add(a));
  ASSERT_TRUE(tree.Find(a) != NULL);
  ASSERT_TRUE(tree.Find(b) != NULL);
  ASSERT_TRUE(tree.Find(c) != NULL);
  ASSERT_TRUE(tree.Find(d) != NULL);
  ASSERT_TRUE(tree.Add(a));
  ASSERT_TRUE(tree.Find(a) != NULL);
  tree.Delete(a);
  ASSERT_TRUE(tree.Find(a) != NULL);
  tree.Delete(a);
  ASSERT_TRUE(tree.Find(b) != NULL);
  ASSERT_EQ(NULL, tree.Find(a));
  ASSERT_TRUE(tree.Find(b) != NULL);
  ASSERT_TRUE(tree.Find(c) != NULL);
  ASSERT_TRUE(tree.Find(d) != NULL);
  ASSERT_EQ(NULL, tree.Find(a));
}

