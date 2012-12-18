// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/time.h"

#include <time.h>

#include "gtest/gtest.h"

#include "base/common.h"

TEST(GetCurrentTimeTest, TimeFreezeTest) {
  TestTime::Freeze();
  uint64 start_time = GetCurrentTime();
  ASSERT_EQ(start_time, GetCurrentTime());
  usleep(20000);
  ASSERT_EQ(start_time, GetCurrentTime());

  TestTime::Unfreeze();
  ASSERT_GE(GetCurrentTime(), start_time);
  usleep(5000);
  ASSERT_GE(GetCurrentTime(), start_time + 5);
}

TEST(GetCurrentTimeTest, ShiftTest) {
  uint64 delta = 300;
  uint64 start_time = GetCurrentTime();
  TestTime::ShiftTimeForward(delta);
  ASSERT_GE(GetCurrentTime() - start_time, delta);
}

TEST(GetCurrentTimeTest, ShiftFreezedTimeTest) {
  TestTime::Freeze();
  uint64 start_time = GetCurrentTime();
  TestTime::ShiftTimeForward(30);
  ASSERT_EQ(30u, GetCurrentTime() - start_time);
  TestTime::Unfreeze();
}

TEST(GetCurrentTimeTest, ShiftFreezeUnfreezeShiftTest) {
  uint64 start_time = GetCurrentTime();
  TestTime::ShiftTimeForward(30);
  ASSERT_GE(GetCurrentTime(), start_time + 30);
  TestTime::Freeze();
  ASSERT_GE(GetCurrentTime(), start_time + 30);
  TestTime::Unfreeze();
  ASSERT_GE(GetCurrentTime(), start_time + 30);
  TestTime::ShiftTimeForward(30);
  ASSERT_GE(GetCurrentTime(), start_time + 60);
}

TEST(GetCurrentTimeTest, DoubleFreezeDeathTest) {
  TestTime::Freeze();
  ASSERT_DEATH(TestTime::Freeze(), "CHECK failed");
  TestTime::Unfreeze();
}

TEST(GetCurrentTimeTest, DoubleUnFreezeDeathTest) {
  TestTime::Freeze();
  TestTime::Unfreeze();
  ASSERT_DEATH(TestTime::Unfreeze(), "CHECK failed");
}
