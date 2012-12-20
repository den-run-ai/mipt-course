// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <unordered_map>
#include <string>
#include <vector>

#include "base/common.h"

#include "sandbox11/lzw.h"

using std::string;
using std::vector;
using std::unordered_map;

namespace Lzw {

void compress(const string &input, vector<Code> *output, Code max_code) {
  StringDictionary codes(max_code);
  for (int i = 0; i < 256; ++i)
    codes.AddEntry(string(1, static_cast<char>(i)), i);
  Code next_code = 257;
  string current_str;

  for (char c : input) {
    current_str += c;
    if (codes.HasKey(current_str))
      continue;
    if (next_code <= max_code)
      codes.AddEntry(current_str, next_code++);
    current_str.erase(current_str.size() - 1);
    output->push_back(codes.GetValueOrDie(current_str));
    current_str = c;
  }

  if (current_str.size())
    output->push_back(codes.GetValueOrDie(current_str));
}

void decompress(const vector<Code> &input, string *output, Code max_code) {
  CodeDictionary strings(max_code);
  output->clear();
  for (int i = 0; i < 256; ++i)
    strings.AddEntry(i, string(1, i));
  string prev_str;
  Code next_code = 257;

  for (Code code : input) {
    if (!strings.HasKey(code))
      strings.AddEntry(code, prev_str + prev_str[0]);
    *output += strings.GetValueOrDie(code);
    if (prev_str.size() && next_code <= max_code)
      strings.AddEntry(next_code++, prev_str + strings.GetValueOrDie(code)[0]);
    prev_str = strings.GetValueOrDie(code);
  }
}

}  // namespace Lzw
