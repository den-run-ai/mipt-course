// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/pattern.h"

#include <string>

#include "base/common.h"

bool StringPattern::Match(const std::string &str) const {
  if (pattern_ == "") return true;

  // 'i' designates starting position for a substring we're trying to match
  // with the pattern.
  for (size_t i = 0; i <= str.size(); i++) {
    // "i <= str.size()" (not "i < str.size()") is required to process empty
    // strings. Also it's required to work with '$' in pattern_.

    // 'j' designates the char in the pattern_ that's currently being processed.
    // 'pos' designates the first char of the substring
    // that hasn't been processed yet.
    size_t j, pos;
    // 'mismatch' is true only if current substring (starting at 'i')
    // doesn't match the pattern.
    bool mismatch = false;
    for (j = 0, pos = i; j < pattern_.size() && !mismatch; j++) {
      switch (pattern_[j]) {
        case '*': {
          if (j + 1 == pattern_.size()) {
            // Trailing asterisk
            return true;
          }
          StringPattern p(pattern_.substr(j + 1));
          // TODO(bochkarev.alex): avoid recursion
          if (p.Match(str.substr(pos)))
            return true;
          else
            mismatch = true;
          break;
        }
        case '?': {
          if (pos == str.size()) {
            // No more symbols in substing to process
            mismatch = true;
          }
          pos++;
          break;
        }
        case '^': {
          if (pos != 0) return false;
          break;
        }
        case '$': {
          if (pos == str.size())
            return true;
          else
            mismatch = true;
          break;
        }
        case '\\': {
          if (pattern_[j + 1] != str[pos] || pos == str.size())
            mismatch = true;
          j++;
          pos++;
          break;
        }
        default: {
          if (str[pos] != pattern_[j] || pos == str.size())
            mismatch = true;
          pos++;
          break;
        }
      }
    }
    if (j == pattern_.size() && !mismatch) return true;
  }
  return false;
}

void StringPattern::Normalize() {
  const std::string allowed_metasymbols = "^$?*\\";

  for (int i = 0; i < pattern_.size(); i++) {
    switch (pattern_[i]) {
      case '^': {
        CHECK_EQ(i, 0);
        break;
      }
      case '$': {
        CHECK_EQ(i + 1, pattern_.size());
        break;
      }
      case '\\': {
        CHECK(i + 1 != pattern_.size() &&
              allowed_metasymbols.find(pattern_[i + 1]) != std::string::npos);
        i++;
        break;
      }
      default: {
        break;
      }
    }
  }
}

