// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_FENWICK_TREE_H_
#define SANDBOX_FENWICK_TREE_H_

#include <vector>
#include <functional>

#include "base/common.h"


// Fenwick Tree class. See:
// http://en.wikipedia.org/wiki/Fenwick_tree
// http://e-maxx.ru/algo/fenwick_tree
// It is a data structure, like an array, which allows:
// - adding/removing elements from the end
// - counting the sum of a sub-interval in O(log(array_size)) time
// - modifying elements in the array in O(log(array_size)) time
// AddOp - binary "+" predicate for DataType
// NegOp - unary "-" predicate for DataType
// AddOp and NegOp must follow the axioms of "group",
// and there should exist the Identity element
template<class DataType,
         class AddOp = std::plus<DataType>,
         class NegOp = std::negate<DataType> >
class FenwickTree {
 public:
  FenwickTree(const AddOp& add = AddOp(), const NegOp& neg = NegOp())
    : add_(add), neg_(neg) {
    identity_initialized_ = false;
  }

  FenwickTree(const DataType& ident, const AddOp& add = AddOp(),
              const NegOp& neg = NegOp())
    : identity_(ident), add_(add), neg_(neg) {
    identity_initialized_ = true;
  }

  void set_identity(const DataType& dt) {
    identity_ = dt;
    identity_initialized_ = true;
  }

  void push_back(const DataType& elem) {
    size_t sz = arr_.size();
    if (sz == 0) {
      arr_.push_back(elem);
      if (!identity_initialized_) {
        set_identity(add_(elem, neg_(elem)));
      }
    } else {
      DataType add = count(sz & (sz + 1), sz);
      arr_.push_back(add_(elem, add));
    }
  }

  void pop_back() {
    arr_.pop_back();
  }

  DataType get(size_t position) {
    DCHECK(position < size());
    return add_(count(position + 1), neg_(count(position)));
  }

  void set(size_t position, const DataType& new_value) {
    DCHECK(position < size());
    DataType delta = add_(new_value, neg_(get(position)));
    do {
      arr_[position] = add_(arr_[position], delta);
      position = position | (position + 1);
    } while (position < size());
  }

  DataType count(size_t left, size_t right) {
    DCHECK(left <= right);
    DCHECK(right <= size());
    return add_(count(right), neg_(count(left)));
  }

  size_t size() {
    return arr_.size();
  }

  void clear() {
    arr_.clear();
  }

 private:
  DataType count(size_t last_index) {
    DCHECK(last_index <= size());
    DataType result = identity_;
    while (last_index > 0) {
      result = add_(result, arr_[last_index - 1]);
      last_index = (last_index & (last_index - 1));
    }
    return result;
  }

  std::vector<DataType> arr_;
  AddOp add_;
  NegOp neg_;
  DataType identity_;
  bool identity_initialized_;
};

#endif  // SANDBOX_FENWICK_TREE_H_
