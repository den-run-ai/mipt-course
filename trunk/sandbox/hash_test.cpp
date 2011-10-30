// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/hash.h"
#include <string>
#include "gtest/gtest.h"

TEST(HashTest, DISABLED_HashTest_Actions) {
  HashTable<std::string, std::string> ht(101);

  EXPECT_EQ(0u, ht.Size());
  ht.Add("Alex", "123");
  EXPECT_EQ(1u, ht.Size());
  ht.Add("Kostya", "456");
  EXPECT_EQ(2u, ht.Size());
  EXPECT_TRUE(ht.Contains("Kostya"));
  EXPECT_TRUE(ht.Contains("Alex"));
  EXPECT_EQ("123", ht["Alex"]);
  EXPECT_EQ("456", ht["Kostya"]);
  EXPECT_FALSE(ht.Contains("Vanya"));
  ht["Kostya"] = "344";
  EXPECT_EQ(2u, ht.Size());
  EXPECT_EQ("344", ht["Kostya"]);
  EXPECT_TRUE(ht.Remove("Alex"));
  EXPECT_FALSE(ht.Remove("Nobody"));
  EXPECT_EQ(1u, ht.Size());
  EXPECT_FALSE(ht.Contains("Alex"));
}
