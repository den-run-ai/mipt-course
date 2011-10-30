// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_PATTERN_H_
#define SANDBOX_PATTERN_H_

#include <string>

// StringPattern class implements searching for a substring that matches
// certain pattern. See http://en.wikipedia.org/wiki/Regex for more information.
// Four metasymbols can be used when describing a StringPattern:
// '^' designates starting position of the string
// '$' designates ending position of the string
// '?' matches 1 symbol
// '*' matches zero or more symbols
// To treat metacharacter as a literal preceed it by backslash.

class StringPattern {
 public:
  StringPattern() {}
  explicit StringPattern(const char *str) : pattern_(str) { Normalize(); }
  explicit StringPattern(const std::string str) : pattern_(str) {
    Normalize();
  }

  // Goes through the given string looking for a substring
  // that matches the pattern.
  // Returns true if there is a match, otherwise false.
  // This means that patterns "foobar" and "*foobar*" are equal.
  bool Match(const std::string &str) const;

 private:
  // Goes through the pattern_ and removes any unbalanced backslashes,
  // carets ('^') not at the beginning or dollars ('$') not at the end.
  void Normalize();

  std::string pattern_;
};

#endif  // SANDBOX_PATTERN_H_

