// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_SCOPED_PTR_H_
#define SANDBOX_SCOPED_PTR_H_

#include "base/common.h"

// A scoped_ptr<T> is just like T* except it owns the object and
// deletes it on destruction or a reset() call when the object is replaced.
// That is, scoped_ptr<T> owns T object it points to.
// Like T*, scoped_ptr<T> may hold NULL or pointer to a T object.
//
// WARNING: Dereferencing a NULL pointer using operator*/operator-> will result
// in an assertion failure in a Debug build. In Release build, the behavior is
// undefined.
template <class T>
class scoped_ptr {
 public:
  explicit scoped_ptr(T *p = NULL): ptr_(p) {}

  ~scoped_ptr() {
    delete ptr_;
  }

  void reset(T *p = NULL) {
    if (p != ptr_) {
      delete ptr_;
      ptr_ = p;
    }
  }

  T& operator*() const {
    DCHECK_NE(ptr_, NULL);
    return *ptr_;
  }

  T* operator->() const {
    DCHECK_NE(ptr_, NULL);
    return ptr_;
  }

  T* get() const { return ptr_; }

  // Steals ownership of the object, resetting the pointer to NULL.
  T* release() {
    T* ret_value = ptr_;
    ptr_ = NULL;
    return ret_value;
  }

  void swap(scoped_ptr& other) {  // NOLINT
    // cpplint believes this is a function from <algorithm>, which is wrong.

    T* tmp = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = tmp;
  }

 private:
  T* ptr_;

  DISALLOW_COPY_AND_ASSIGN(scoped_ptr);
};

#endif  // SANDBOX_SCOPED_PTR_H_
