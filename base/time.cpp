// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <time.h>
#include <sys/time.h>

#include "base/time.h"

uint64 ConvertTime(const struct timeval &t) {
  return (t.tv_sec*1000 + t.tv_usec/1000);
}

uint64 TestTime::start_, TestTime::time_shift_;

bool TestTime::time_is_frozen_;
uint64 TestTime::frozen_time_;

void TestTime::ShiftTimeForward(uint64 shift) {
  time_shift_ += shift;
  if (time_is_frozen_) {
    frozen_time_ += shift;
  }
}

void TestTime::Freeze() {
  CHECK(!time_is_frozen_);
  frozen_time_ = GetCurrentTime();
  time_is_frozen_ = true;
}

void TestTime::Unfreeze() {
  CHECK(time_is_frozen_);
  struct timeval current;
  gettimeofday(&current, NULL);
  time_shift_ = frozen_time_ - ConvertTime(current) + start_;
  frozen_time_ = 0;
  time_is_frozen_ = false;
}

uint64 TestTime::GetShiftedTime() {
  if (!start_) {
    struct timeval start;
    gettimeofday(&start, NULL);
    start_ = ConvertTime(start);
  }
  if (time_is_frozen_) {
    return frozen_time_;
  } else {
    struct timeval end;
    gettimeofday(&end, NULL);
    return ConvertTime(end) - start_ + time_shift_;
  }
}

uint64 GetCurrentTime() {
  return TestTime::GetShiftedTime();
}
