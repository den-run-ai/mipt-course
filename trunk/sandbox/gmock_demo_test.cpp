// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/googletest/include/gtest/gtest.h"
#include "third_party/googlemock/include/gmock/gmock.h"

#include "base/common.h"

using namespace testing;

// http://code.google.com/p/googlemock/wiki/ForDummies

class SomeInterface {
 public:
  virtual bool IsNumberOdd(int value) = 0;
};

class MockSomeInterface : public SomeInterface {
 public:
  MOCK_METHOD1(IsNumberOdd, bool(int value));
};

// Some class working with the interface
class MyClass {
 public:
  MyClass(SomeInterface *number_processor)
      : number_processor_(number_processor) {
  }

  // Returns a sum of odd numbers between 0 and 10.
  int DoSomeJob() {
    int ret = 0;
    for (int i = 0; i < 10; i++) {
      bool is_odd = number_processor_->IsNumberOdd(i);
      printf("%i is an %s number\n",
             i, is_odd ?  "odd" : "even");
      if (is_odd)
        ret += i;
    }
    return ret;
  }

 private:
  SomeInterface *number_processor_;
};

TEST(GoogleMockDemo, SimpleMock) {
  // Create a mock instance
  MockSomeInterface mock;

  // Set some expectations
  EXPECT_CALL(mock, IsNumberOdd(0))
      .Times(1).WillRepeatedly(Return(false));

  for (int i = 1; i < 10; i+=2)
    EXPECT_CALL(mock, IsNumberOdd(i))
        .Times(1).WillOnce(Return(true));
  for (int i = 2; i < 10; i+=2)
    EXPECT_CALL(mock, IsNumberOdd(i))
        .Times(1).WillOnce(Return(false));

  // Run it!
  MyClass m(&mock);
  ASSERT_EQ(25, m.DoSomeJob());
}
