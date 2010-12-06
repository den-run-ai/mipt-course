// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/treap.h"
#include "third_party/googletest/include/gtest/gtest.h"
#include "base/common.h"

TEST(Treap, DISABLED_InsertDeleteTest) {
  Treap<int, int> treap;
  treap.Insert(1, 123);
  treap.Insert(3, 234);
  treap.Insert(4, 40000);
  treap.Insert(234, 3241);
  treap.Insert(562, 325);
  treap.Insert(24, 325);
  treap.Insert(54, 325);
  treap.Insert(32, 35);

  EXPECT_EQ(8U, treap.size());
  EXPECT_TRUE(treap.Contains(4));
  EXPECT_FALSE(treap.Contains(4444));
}

