// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <functional>
#include <vector>
#include "gtest/gtest.h"

#include "base/common.h"
#include "base/random.h"

#include "sandbox/fenwick_tree.h"

TEST(FenwickTreeTest, InsertRemoveElementsTest) {
  FenwickTree<int> fnw;
  for (int i = 0; i < 10; ++i)
    fnw.push_back(i);

  EXPECT_EQ(10u, fnw.size());
  fnw.pop_back();
  fnw.pop_back();
  EXPECT_EQ(8u, fnw.size());

  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(i, fnw.get(i));

  fnw.clear();
  EXPECT_EQ(0u, fnw.size());
}

TEST(FenwickTreeTest, SimpleCountElementsTest) {
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

  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(i, fnw.get(i));
}

TEST(FenwickTreeTest, RandomizedCountElementsTest) {
  RandomGenerator gen(42 * 42);
  FenwickTree<int> fnw;
  std::vector<int> arr;

  const int ARRAY_SIZE = 257;

  for (int i = 0; i < ARRAY_SIZE; ++i) {
    int k = gen.Generate<int>();
    fnw.push_back(k);
    arr.push_back(k);
  }

  for (int i = 0; i < 20000; ++i) {
    int left = gen.Generate<int>(ARRAY_SIZE);
    int right = gen.Generate<int>(left, ARRAY_SIZE);

    int fnw_sum = fnw.count(left, right);

    int arr_sum = 0;
    for (int j = left; j < right; ++j)
      arr_sum += arr[j];

    ASSERT_EQ(arr_sum, fnw_sum);
  }
}

TEST(FenwickTreeTest, ModifyElements) {
  FenwickTree<int> fnw;
  for (int i = 0; i < 10; ++i)
    fnw.push_back(9 - i);

  fnw.set(0, 1);
  fnw.set(1, 2);
  EXPECT_EQ(10, fnw.count(0, 3));
  fnw.set(6, 9);
  EXPECT_EQ(37, fnw.count(0, 10));

  for (int i = 2; i < 6; ++i)
    EXPECT_EQ(9-i, fnw.get(i));
  for (int i = 7; i < 10; ++i)
    EXPECT_EQ(9-i, fnw.get(i));
}

template<class T>
class Inverser {
 public:
  T operator()(const T& value) {
    return T(1) / value;
  }
};

TEST(FenwickTreeTest, MultiplyDivideTest) {
  FenwickTree<double, std::multiplies<double>, Inverser<double> > fnw;
  fnw.set_identity(1.0);
  for (int i = 2; i <= 6; ++i)
    fnw.push_back(i);
  for (int i = 2; i <= 6; ++i)
    EXPECT_DOUBLE_EQ(static_cast<double>(i), fnw.get(i-2));
  EXPECT_DOUBLE_EQ(720.0, fnw.count(0, 5));
  EXPECT_DOUBLE_EQ(120.0, fnw.count(2, 5));
  EXPECT_DOUBLE_EQ(12.0, fnw.count(1, 3));
  fnw.set(0, 7.0);
  fnw.set(1, 9.0);
  EXPECT_DOUBLE_EQ(7.0, fnw.get(0));
  EXPECT_DOUBLE_EQ(9.0, fnw.get(1));
  EXPECT_DOUBLE_EQ(63.0, fnw.count(0, 2));
  EXPECT_DOUBLE_EQ(63.0 * 120.0, fnw.count(0, 5));
  EXPECT_DOUBLE_EQ(9.0 * 20.0, fnw.count(1, 4));
}
