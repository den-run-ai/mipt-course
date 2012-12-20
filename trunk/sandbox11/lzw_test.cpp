// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <vector>
#include <string>

#include "base/common.h"
#include "gtest/gtest.h"

#include "sandbox11/lzw.h"

using std::vector;
using std::string;

namespace Lzw {

TEST(LZWDictionaryTests, AddAndRequestSomeStringsTest) {
  StringDictionary dict;

  EXPECT_FALSE(dict.HasKey("abc"));
  EXPECT_FALSE(dict.IsFull());
  dict.AddEntry("abc", 1);
  dict.AddEntry("def", 2);
  EXPECT_TRUE(dict.HasKey("abc"));
  EXPECT_TRUE(dict.HasKey("def"));
  EXPECT_EQ((Code)1, dict.GetValueOrDie("abc"));
  EXPECT_EQ((Code)2, dict.GetValueOrDie("def"));
  EXPECT_FALSE(dict.IsFull());

  // Should crash
  // This test won't work under valgrind.
  // EXPECT_DEATH(dict.GetValueOrDie("no_such_string"), "CHECK failed: .*");
}

TEST(LZWDictionaryTests, TooManyEntriesTest) {
  StringDictionary dict(2);

  EXPECT_FALSE(dict.HasKey("a string"));
  EXPECT_FALSE(dict.IsFull());
  EXPECT_TRUE(dict.AddEntry("a", 42));
  EXPECT_FALSE(dict.IsFull());
  EXPECT_TRUE(dict.AddEntry("b", 43));
  EXPECT_TRUE(dict.IsFull());
  EXPECT_FALSE(dict.AddEntry("d", 44));
}

TEST(LZWAlgorithmTests, EncryptionTest) {
  vector<Code> codes;
  vector<Code> expected_codes = {65, 66, 66, 257, 258, 260, 65};
  Lzw::compress("ABBABBBABBA", &codes);
  CHECK_EQ(expected_codes, codes);
}

TEST(LZWAlgorithmTests, DecryptionTest) {
  string decompressed_string;
  vector<Code> codes = {65, 66, 66, 257, 258, 260, 65};
  Lzw::decompress(codes, &decompressed_string);
  CHECK_EQ("ABBABBBABBA", decompressed_string);
}

TEST(LZWAlgorithmTests, EncryptionDecryptionTest) {
  const string test_strings[] = {
    "",
    "a",
    "aaaaa",
    "abcdef",
    "abbacabba",
    "aaaaaaaaabb",
    "abbaabbaabbacabbaabbabbabbaccaba",
  };

  for (size_t i = 0; i < ARRAY_SIZE(test_strings); ++i) {
    vector<Code> codes;
    const string &test_string = test_strings[i];
    Lzw::compress(test_string, &codes);
    EXPECT_LE(codes.size(), test_string.size());
    string decompressed_string;
    Lzw::decompress(codes, &decompressed_string);
    EXPECT_EQ(test_string, decompressed_string);
  }
}

}  // namespace Lzw
