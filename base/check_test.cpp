// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

#include "base/common.h"

TEST(CheckTest, CheckTrueSucceedsTest) {
  CHECK(1);
  CHECK(42);
}

TEST(CheckTest, AssertionsAndChecksTest) {
  CHECK(2 + 2 == 4);        // NOLINT
  ASSERT_TRUE(2 + 2 == 4);  // NOLINT
  ASSERT_EQ(4, 2 + 2);
  ASSERT_LE(2 + 2, 5);
  printf("Passed all ASSERT macros, now EXPECT macros\n");
  EXPECT_EQ(4, 2 + 2);
  printf("End of test\n");
}

// C preprocessor magic, see
// http://www.decompile.com/cpp/faq/file_and_line_error_string.htm
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define __FILE_LINE__ __FILE__ ":" TOSTRING(__LINE__)

TEST(CheckTest, CheckFalseDeathTest) {
  ASSERT_DEATH(CHECK(0), "CHECK failed: .* at " __FILE_LINE__);
}

TEST(CheckTest, DCheckFalseDeathTest) {
  ASSERT_DEBUG_DEATH(DCHECK(0), "CHECK failed: .* at " __FILE_LINE__);
}
