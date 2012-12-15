// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "base/common.h"

using namespace testing;  // NOLINT

class SomeInterface {
 public:
  virtual bool IsNumberOdd(int value) = 0;
  virtual ~SomeInterface() {}
};

// Читать:
// http://code.google.com/p/googlemock/wiki/ForDummies
class MockSomeInterface : public SomeInterface {
 public:
  MOCK_METHOD1(IsNumberOdd, bool(int value));
};

// Класс, который работает с интерфесом.
class MyClass {
 public:
  explicit MyClass(SomeInterface *number_processor)
      : number_processor_(number_processor) {
  }

  // Возвращает сумму нечётных чисел от 0 до 10.
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
  // Создать mock-объект.
  MockSomeInterface mock;

  // Читать:
  // http://code.google.com/p/googlemock/wiki/ForDummies

  // Установить expectations - то, как mock должен будет
  // реагировать на различные вызовы,
  // а также указать ожидаемое количество вызовов.
  EXPECT_CALL(mock, IsNumberOdd(0))
        .Times(1).WillOnce(Return(false));

  for (int i = 1; i < 10; i+=2)
    EXPECT_CALL(mock, IsNumberOdd(i))
        .Times(1).WillOnce(Return(true));
  for (int i = 2; i < 10; i+=2)
    EXPECT_CALL(mock, IsNumberOdd(i))
        .Times(1).WillOnce(Return(false));

  // Expectations установлены, можно запускать тест.
  MyClass m(&mock);
  ASSERT_EQ(25, m.DoSomeJob());

  // При уничтожении mock-объект проверяет expectations.
}
