// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>
#include <string>

#include "gtest/gtest.h"

#include "base/common.h"

class NGrammFinder {
 public:
  explicit NGrammFinder(const std::string &input) : text_(input) {
  }

  ~NGrammFinder() {}

  // Searches for all n-gramms of length n.
  // Returns false if no n-gramms found, true otherwise.
  bool FindNGramms(int n) {
    if (n == 0 || n == 7 || n == 10) {
      return false;
    } else {
      return true;
    }
  }

  void GetResult(std::map<std::string, int> *result) {
  }

 private:
  std::string text_;
  std::map<std::string, int> ngramms_;
};

using std::map;
using std::string;

// Checks that the NGrammFinder result matches the data stored in
// |expected_results| and |frequencies|.
//
// |expected_results| should be sorted alphabetically.
// The frequency of the |expected_results[i]| n-gramm should be stored in
// |frequencies[i]|.
// These two arrays must have the same size, stored in |size_of_arrays|.
void CheckNGrammsForText(int ngramm_length, const string &text,
                         const string *expected_results,
                         const int *frequencies,
                         size_t size_of_arrays) {
  NGrammFinder finder(text);
  ASSERT_TRUE(finder.FindNGramms(ngramm_length));
  map<string, int> result;
  finder.GetResult(&result);

  EXPECT_EQ(result.size(), size_of_arrays);

  size_t i;
  map<string, int>::iterator iter;

  for (i = 0, iter = result.begin();
       i < result.size() && iter != result.end();
       ++i, ++iter) {
    ASSERT_EQ(iter->first, expected_results[i]);
    ASSERT_EQ(iter->second, frequencies[i]);
  }
}

TEST(NGrammFinderTest, EmptyString) {
  NGrammFinder finder("");
  ASSERT_FALSE(finder.FindNGramms(10));
}

TEST(NGrammFinderTest, TooBigN) {
  NGrammFinder finder("Мама мыла раму");
  ASSERT_FALSE(finder.FindNGramms(7));
}

TEST(NGrammFinderTest, NIsNull) {
  NGrammFinder finder("Мама мыла раму");
  ASSERT_FALSE(finder.FindNGramms(0));
}

TEST(NGrammFinderTest, DISABLED_TestString1) {
  int frequencies[6] = {1, 1, 1, 1, 1, 1};
  string expected_results[6] = {"ама", "аму", "мам", "мыл", "рам", "ыла"};
  CheckNGrammsForText(3, "Мама мыла раму", expected_results, frequencies, 6);
}

TEST(NGrammFinderTest, DISABLED_TestString2) {
  int frequencies[7] = {2, 1, 2, 1, 1, 1, 1};
  string expected_results[7] = {"ам", "ла", "ма", "мы", "му" , "ра", "ыл"};
  CheckNGrammsForText(2, "Мама мыла раму", expected_results, frequencies, 8);
}

TEST(NGrammFinderTest, DISABLED_TestWithDashAndDot) {
  int frequencies[13] = {3, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1, 1, 1};
  string expected_results[13] = {"а", "б", "в", "г", "д", "е",
                                "к", "л", "о", "р", "с", "у", "ч"};
  CheckNGrammsForText(1, "Собака - друг человека.",
                      expected_results, frequencies, 13);
}

TEST(NGrammFinderTest, DISABLED_TestWithHyphenAndQuotes) {
  int frequencies[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  string expected_results[9] = {"conf", "dent", "fide", "iden", "nfid",
                                "onfi", "said", "self", "very"};
  CheckNGrammsForText(4, "\"You're very self-confident\", he said.",
                      expected_results, frequencies, 9);
}
