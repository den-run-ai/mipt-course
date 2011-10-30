// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/treap.h"

#include <memory>

#include "third_party/googletest/include/gtest/gtest.h"
#include "base/common.h"

class TreapTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    generator.reset(new RandomGenerator(SEED));
    treap.reset(new Treap<int, int>(generator.get()));
  }

  virtual void TearDown() {}

  static const uint32 SEED = 1;

  std::auto_ptr<RandomGenerator> generator;
  std::auto_ptr<Treap<int, int> > treap;
};

TEST_F(TreapTest, InsertTest) {
  EXPECT_EQ(0U, treap->size());
  treap->Insert(1, 123);
  treap->Insert(3, 234);
  treap->Insert(4, 40000);
  treap->Insert(234, 3241);
  treap->Insert(562, 325);
  treap->Insert(24, 325);
  treap->Insert(54, 325);
  treap->Insert(32, 35);

  EXPECT_EQ(8U, treap->size());
  EXPECT_TRUE(treap->Contains(4));
  EXPECT_FALSE(treap->Contains(4444));

  EXPECT_EQ(3241, treap->Get(234));
}

TEST_F(TreapTest, DeleteTest) {
  treap->Insert(1, 123);
  treap->Insert(3, 234);
  treap->Insert(4, 40000);
  treap->Insert(234, 3241);
  treap->Insert(562, 325);
  treap->Insert(24, 325);
  treap->Insert(54, 325);
  treap->Insert(32, 35);
  EXPECT_EQ(8U, treap->size());

  EXPECT_TRUE(treap->Erase(4));
  EXPECT_EQ(7U, treap->size());
  EXPECT_FALSE(treap->Contains(4));
}

TEST_F(TreapTest, FullInsertDeleteCycle) {
  treap->Insert(1, 123);
  treap->Insert(3, 234);
  treap->Insert(4, 40000);
  EXPECT_EQ(3U, treap->size());

  EXPECT_TRUE(treap->Erase(4));
  EXPECT_EQ(2U, treap->size());
  EXPECT_FALSE(treap->Contains(4));

  treap->Insert(8, 8);
  treap->Insert(9, 9);

  EXPECT_EQ(4U, treap->size());
  EXPECT_TRUE(treap->Erase(1));
  EXPECT_FALSE(treap->Erase(1));
  EXPECT_FALSE(treap->Erase(11111));
  EXPECT_TRUE(treap->Erase(8));
  EXPECT_TRUE(treap->Erase(9));
  EXPECT_TRUE(treap->Erase(3));
  EXPECT_EQ(0U, treap->size());
}

TEST_F(TreapTest, LargeTest) {
  EXPECT_EQ(0U, treap->size());
  treap->Insert(1, 2);
  treap->Insert(2, 4);
  EXPECT_EQ(2U, treap->size());
  treap->Insert(3, 6);
  treap->Insert(4, 8);
  EXPECT_TRUE(treap->Erase(3));
  EXPECT_TRUE(treap->Erase(1));
  EXPECT_FALSE(treap->Erase(1));
  EXPECT_FALSE(treap->Erase(11111));
  treap->Insert(5, 10);
  EXPECT_EQ(3U, treap->size());
  treap->Insert(6, 12);
  EXPECT_EQ(4, treap->Get(2));
  treap->Insert(7, 14);
  treap->Insert(8, 16);
  EXPECT_TRUE(treap->Erase(2));
  EXPECT_EQ(5U, treap->size());
  EXPECT_TRUE(treap->Erase(5));
  treap->Insert(9, 18);
  EXPECT_EQ(12, treap->Get(6));
  treap->Insert(10, 20);
  treap->Insert(11, 22);
  EXPECT_TRUE(treap->Contains(10));
  EXPECT_TRUE(treap->Erase(10));
  EXPECT_FALSE(treap->Erase(10));
  EXPECT_FALSE(treap->Erase(11111));
  EXPECT_FALSE(treap->Contains(10));
  EXPECT_EQ(6U, treap->size());
  treap->Insert(12, 24);
  treap->Insert(13, 26);
  treap->Insert(14, 28);
  treap->Insert(15, 30);
  EXPECT_EQ(10U, treap->size());
}
