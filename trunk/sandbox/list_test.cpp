// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/common.h"

#include "sandbox/list.h"

#include "third_party/googletest/include/gtest/gtest.h"

TEST(ListTest, Insert) {
  List<int> list;

  for (int i = 0; i < 100; i++)
    list.PushFront(i);
  EXPECT_EQ(100u, list.Size());
  int value = 99;
  for (List<int>::iterator i = list.begin();
      i != list.end();
      i = list.next(i)) {
    EXPECT_EQ(value--, list.getValue(i));
  }

  for (int i = 0; i < 100; i++)
    list.PushBack(-1);
  EXPECT_EQ(200u, list.Size());

  list.Clear();
  EXPECT_EQ(0u, list.Size());
}

TEST(ListTest, Remove) {
  List<int> list;

  for (int i = 0; i < 100; i++)
    list.PushFront(i);
  ASSERT_EQ(100u, list.Size());

  // Remove from begin
  List<int>::iterator i = list.begin();
  // Remove() should return an iterator to the next element.
  i = list.Remove(i);
  ASSERT_EQ(99u, list.Size());
  ASSERT_EQ(98, list.getValue(i));

  // Remove from mid
  i = list.next(list.begin());
  i = list.Remove(i);
  ASSERT_EQ(98u, list.Size());
  ASSERT_EQ(96, list.getValue(i));
}

TEST(ListTest, Clear) {
  List<int> list;

  list.PushFront(0);
  list.Clear();
}

TEST(ListTest, BeginAndEnd) {
  List<int> list;

  // Size = 1
  list.PushFront(0);
  ASSERT_NE(list.begin(), (List<int>::iterator)NULL);
  ASSERT_EQ(list.next(list.begin()), list.end());

  // Size = 1 + 100
  for (int i = 0; i < 100; i++)
    list.PushFront(0);
  size_t count = 0;
  for (List<int>::iterator i = list.begin(); i != list.end(); i = list.next(i))
    count++;
  ASSERT_EQ(count, list.Size());
}
