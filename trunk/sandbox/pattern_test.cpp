// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/pattern.h"

#include "gtest/gtest.h"

TEST(PatternTest, WorksWithoutSpecialSymbols) {
  StringPattern p1("asd");
  StringPattern p2("");

  EXPECT_TRUE(p1.Match("asd"));
  EXPECT_TRUE(p1.Match("aaasd"));
  EXPECT_FALSE(p1.Match(""));

  EXPECT_TRUE(p2.Match(""));
  EXPECT_TRUE(p2.Match("foo"));
}

TEST(PatternTest, WorksWithSpecialSymbols) {
  StringPattern p1("asd?");
  StringPattern p2("aa*");
  StringPattern p3("*");
  StringPattern p4("^foo");
  StringPattern p5("bar$");

  EXPECT_FALSE(p1.Match(""));
  EXPECT_FALSE(p1.Match("asd"));
  EXPECT_FALSE(p1.Match("aaasd"));
  EXPECT_TRUE(p1.Match("asdsss"));

  EXPECT_FALSE(p2.Match(""));
  EXPECT_TRUE(p2.Match("aa"));
  EXPECT_TRUE(p2.Match("saad"));

  EXPECT_TRUE(p3.Match(""));
  EXPECT_TRUE(p3.Match("asd"));

  EXPECT_TRUE(p4.Match("foobar"));
  EXPECT_FALSE(p4.Match("feefoo"));

  EXPECT_TRUE(p5.Match("foobar"));
  EXPECT_FALSE(p5.Match("barium"));
}

TEST(PatternTest, WorksWithEscapedSymbols) {
  StringPattern p1("asd\\?");
  StringPattern p2("aa\\*");
  StringPattern p3("\\*");

  EXPECT_FALSE(p1.Match("asda"));
  EXPECT_TRUE(p1.Match("asd?"));

  EXPECT_FALSE(p2.Match("aaa"));
  EXPECT_TRUE(p2.Match("aa*"));

  EXPECT_FALSE(p3.Match("aad"));
  EXPECT_TRUE(p3.Match("*"));
}

// TODO(bochkarev.alex): add tests to make StringPattern look more like regex.

