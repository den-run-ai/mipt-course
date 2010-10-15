// Copyright (c) 2010 Timur Iskhodzhanov and others. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/common.h"
#include "third_party/googletest/include/gtest/gtest.h"

TEST(CheckTest, CheckTrueSucceedsTest) {
  CHECK(1);
  CHECK(42);
}

// C preprocessor magic, see
// http://www.decompile.com/cpp/faq/file_and_line_error_string.htm
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define __FILE_LINE__ __FILE__ ":" TOSTRING(__LINE__)

TEST(CheckTest, CheckFalseDeathTest) {
  // Suppress the "fork() is unsafe" warnings
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(CHECK(0), "CHECK failed: .* at " __FILE_LINE__);
}

TEST(CheckTest, DCheckFalseDeathTest) {
  // Suppress the "fork() is unsafe" warnings
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEBUG_DEATH(DCHECK(0), "CHECK failed: .* at " __FILE_LINE__);
}
