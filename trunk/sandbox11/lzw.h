// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LZW_H_
#define SANDBOX_LZW_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "base/common.h"

namespace Lzw {

typedef unsigned Code;

// Dictionary implements a mapping from objects of type 'Key' to
// objects of type 'Value' with fixed maximum number of entries.
template <class Key, class Value>
class Dictionary {
 public:
  // Constructor takes the maximum size of the dictionary.
  explicit Dictionary(size_t max_capacity = 4096)
    : max_capacity_(max_capacity) {}
  ~Dictionary() {}

  bool HasKey(const Key &key) const {
    return map_.find(key) != map_.end();
  }

  bool IsFull() const {
    return map_.size() == max_capacity_;
  }

  // If the dictionary is not full, puts the ('key', 'value') pair
  // into the dictionary and returns true.
  // Otherwise returns false without changing the dictionary.
  bool AddEntry(const Key &key, const Value &value) {
    if (IsFull())
      return false;
    map_[key] = value;
    return true;
  }

  // Returns the value for a given key.
  // The caller is responsible for checking if the key is in the
  // dictionary by calling HasKey() before GetValueOrDie().
  const Value& GetValueOrDie(const Key &key) const {
    auto it = map_.find(key);
    CHECK_NE(it, map_.end());
    return it->second;
  }

 private:
  std::unordered_map<Key, Value> map_;
  const size_t max_capacity_;
};

typedef Dictionary<std::string, Code> StringDictionary;
typedef Dictionary<Code, std::string> CodeDictionary;

// Performs LZW compression on the given string 'input',
// writes the resulting sequence of codes into vector 'output'.
void compress(const std::string &input, std::vector<Code> *output,
              Code max_code = 4096);

// Performes LZW decompression of the given code sequence 'input',
// writes the decompressed text into string 'output'.
void decompress(const std::vector<Code> &input, std::string *output,
                Code max_code = 4096);

// TODO(dmitry.borody): Add function that transforms vector<Code> to bytes,
// it may be useful when transmitting encrypted text over a network.

}  // namespace Lzw

#endif  // SANDBOX_LZW_H_
