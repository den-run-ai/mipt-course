// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef BASE_TIME_H_
#define BASE_TIME_H_

#include "base/common.h"

// TODO(Danichbloom): add substitution for sleep, which takes "test" time
// into the account

// TODO(Danichbloom): Write a RAII-primitive like ScopedTimeFreezer, that
// unfreezes time in its destructor

class TestTime {
 public:
  // You can use this method to manipulate time that is returned by
  // GetCurrentTime().
  static void ShiftTimeForward(uint64 shift);

  // Don't use it more than 1 time in a row
  static void Freeze();

  // Don't use it more than 1 time in a row
  static void Unfreeze();
  static uint64 GetShiftedTime();

 private:
  static uint64 start_, frozen_time_, time_shift_;
  static bool time_is_frozen_;
  DISALLOW_COPY_AND_ASSIGN(TestTime);
};

// To test the code that uses time, you should use GetCurrentTime() instead of
// time(). In your tests you can manipulate time by using the methods of
// TestTime. See time_test.cpp for usage examples.
uint64 GetCurrentTime();

#endif  // BASE_TIME_H_
