// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

TEST(CommonTest, DebugOrRelease) {
#ifdef NDEBUG
  printf("NDEBUG defined, this is a Release build\n");
#else
  printf("NDEBUG is not defined, this is a Debug build\n");
#endif
}
