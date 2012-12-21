// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/scoped_ptr.h"

#include "gtest/gtest.h"

class TestClass {
 public:
  explicit TestClass(int *dtor_counter) : dtor_counter_(dtor_counter) {}

  ~TestClass() {
    ++(*dtor_counter_);
  }

  int SomeMethod(int v) {return 42 + v;}

 private:
  int *dtor_counter_;
};

TEST(ScopedPtrTest, BasicTest) {
  int dtor_counter = 0;

  {
    TestClass* test_obj = new TestClass(&dtor_counter);
    scoped_ptr<TestClass> ptr(test_obj);
    EXPECT_EQ(0, dtor_counter);

    EXPECT_EQ(test_obj, ptr.get());
    EXPECT_EQ(42042, ptr->SomeMethod(42000));
    EXPECT_EQ(4242, (*ptr).SomeMethod(4200));

    EXPECT_EQ(0, dtor_counter);
  }
  EXPECT_EQ(1, dtor_counter);
}

TEST(ScopedPtrTest, ReleaseTest) {
  int dtor_counter = 0;

  {
    TestClass test_obj(&dtor_counter);

    // Warning! A pointer to local variable is passed to scoped_ptr.
    scoped_ptr<TestClass> ptr(&test_obj);

    EXPECT_EQ(&test_obj, ptr.release());
    EXPECT_EQ(0, dtor_counter);
    EXPECT_EQ(NULL, ptr.release());
  }
  EXPECT_EQ(1, dtor_counter);
}

TEST(ScopedPtrTest, ResetTest) {
  int dtor_counter_a = 0, dtor_counter_b = 0;

  {
    TestClass *a = new TestClass(&dtor_counter_a);
    TestClass *b = new TestClass(&dtor_counter_b);

    scoped_ptr<TestClass> ptr(a);
    ptr.reset(b);

    EXPECT_EQ(1, dtor_counter_a);
    EXPECT_EQ(0, dtor_counter_b);
  }
  EXPECT_EQ(1, dtor_counter_a);
  EXPECT_EQ(1, dtor_counter_b);
}

TEST(ScopedPtrTest, SwapTest) {
  int dtor_counter_a = 0, dtor_counter_b = 0;

  {
    TestClass *a = new TestClass(&dtor_counter_a);
    scoped_ptr<TestClass> ptr_a(a);

    {
      TestClass *b = new TestClass(&dtor_counter_b);
      scoped_ptr<TestClass> ptr_b(b);
      ptr_b.swap(ptr_a);

      EXPECT_EQ(0, dtor_counter_a);
      EXPECT_EQ(0, dtor_counter_b);
    }
    EXPECT_EQ(1, dtor_counter_a);
    EXPECT_EQ(0, dtor_counter_b);
  }
  EXPECT_EQ(1, dtor_counter_a);
  EXPECT_EQ(1, dtor_counter_b);
}

TEST(ScopedPtrTest, DeathOnAccessNullPointer) {
  scoped_ptr<TestClass> ptr(NULL);

  ASSERT_DEBUG_DEATH(*ptr, "");
  ASSERT_DEBUG_DEATH(ptr->SomeMethod(0), "");
}
