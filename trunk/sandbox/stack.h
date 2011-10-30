// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_STACK_H_
#define SANDBOX_STACK_H_

#include <stdlib.h>

#include "base/common.h"

template<class Type>
class Stack {
 public:
  explicit Stack(size_t size);
  ~Stack();
  void Push(const Type &value);
  Type Pop();
  size_t Size();

 private:
  Type *first_, *current_;
  size_t capacity_;
};

template<class Type>
Stack<Type>::Stack(size_t size) : capacity_(size) {
  first_ = current_ = new Type[capacity_];
}

template<class Type>
Stack<Type>::~Stack() {
  delete[] first_;
}

template<class Type>
void Stack<Type>::Push(const Type &value) {
  CHECK_LT(current_, first_ + capacity_);
  *(current_++) = value;
}

template<class Type>
Type Stack<Type>::Pop() {
  CHECK_GT(current_, first_);
  return *(--current_);
}

template<class Type>
size_t Stack<Type>::Size() {
  CHECK_GE(current_, first_);
  return (size_t)(current_ - first_);
}

#endif  // SANDBOX_STACK_H_
