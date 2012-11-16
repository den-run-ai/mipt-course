// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/common.h"
#include "gtest/gtest.h"

/* Запуск:
   valgrind -q --leak-check=full ./sandbox_tests --gtest_filter="*Valgrind*" --gtest_also_run_disabled_tests
   или
   ./sandbox_tests --gtest_filter="*Valgrind*" --gtest_also_run_disabled_tests
 */

void Read(int *a) {
  // Чтение *a и использование в условном выражении - нужно, чтобы valgrind
  // видел что значение *a на самом деле используется, а не просто читается.
  if (*a == 777) {
    printf("777\n");
  }
}

void Write(int *a) {
  *a = 1;
}

TEST(ValgrindDemoTests, DISABLED_OutOfBoundsReadTest) {
  int *foo = new int[10];
  Read(&foo[11]);
  delete [] foo;
}

TEST(ValgrindDemoTests, DISABLED_OutOfBoundsWriteTest) {
  int *foo = new int[10];
  Write(&foo[-3]);
  delete [] foo;
}

TEST(ValgrindDemoTests, DISABLED_UninitializedHeapReadTest) {
  int *foo = new int[10];
  Read(&foo[5]);  // foo[5] ещё не инициализирован.
  delete [] foo;
}

#if 0  // Не скомпилируется в режиме оптимизации с -finline -Wall -Werror
TEST(ValgrindDemoTests, DISABLED_UninitializedStackReadTest) {
  int foo[10];
  Read(&foo[5]);
}
#endif

TEST(ValgrindDemoTests, DISABLED_UseAfterFreeTest) {
  int *foo = new int[10];
  foo[5] = 666;
  delete [] foo;

  // Пишем в уже недоступную память.
  Write(&foo[5]);
}

TEST(ValgrindDemoTests, DISABLED_MemoryLeakTest) {
  int *foo = new int[10];
  ASSERT_TRUE(foo != NULL);
  // Память утекла.
}
