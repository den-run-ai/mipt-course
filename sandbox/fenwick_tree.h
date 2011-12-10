// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_FENWICK_TREE_H_
#define SANDBOX_FENWICK_TREE_H_

#include <vector>

#include "base/common.h"


// Fenwick Tree class. See:
// http://en.wikipedia.org/wiki/Fenwick_tree
// http://e-maxx.ru/algo/fenwick_tree
// It is a data structure, like an array, which allows:
// - adding/removing elements from the end
// - counting the sum of a sub-interval in O(log(array_size)) time
// - modifying elements in the array in O(log(array_size)) time

template<class DataType>
class FenwickTree {
 public:
  FenwickTree() { }

  void push_back(const DataType& elem) { }

  void pop_back() { }

  void set(size_t position, const DataType& new_value) { }

  DataType count(size_t left, size_t right) {
    return count(right - 1) - count(left - 1);
  }

  size_t size() {
    return arr_.size();
  }

  void clear() {
    arr_.clear();
  }

 private:
  DataType count(size_t last_index) {
    DataType result = DataType(0);
    return result;
  }

  std::vector<DataType> arr_;
};

#endif  // SANDBOX_FENWICK_TREE_H_
