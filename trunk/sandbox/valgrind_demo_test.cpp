// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/common.h"
#include "gtest/gtest.h"

void Read(int *a) {
  if (*a == 777) {  // Use *a in a conditional statement.
    printf("777\n");
  }
}

void Write(int *a) {
  *a = 1;
}

TEST(ValgrindDemoTests, DISABLED_OutOfBoundsReadTest) {
  int *foo = new int[10];
  Read(&foo[10]);
  delete [] foo;
}

TEST(ValgrindDemoTests, DISABLED_OutOfBoundsWriteTest) {
  int *foo = new int[10];
  Write(&foo[25]);
  delete [] foo;
}

TEST(ValgrindDemoTests, DISABLED_UninitializedHeapReadTest) {
  int *foo = new int[10];
  Read(&foo[5]);  // foo[5] hass not being initialized yet.
  delete [] foo;
}

#if 0  // This won't build with -finline -Wall -Werror
TEST(ValgrindDemoTests, DISABLED_UninitializedStackReadTest) {
  int foo[10];
  Read(&foo[5]);
}
#endif

TEST(ValgrindDemoTests, DISABLED_UseAfterFreeTest) {
  int *foo = new int[10];
  foo[5] = 666;
  delete [] foo;
  Read(&foo[5]);
}

TEST(ValgrindDemoTests, DISABLED_MemoryLeakTest) {
  int *foo = new int[10];
  ASSERT_TRUE(foo != NULL);
}
