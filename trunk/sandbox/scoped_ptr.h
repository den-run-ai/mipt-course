// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_SCOPED_PTR_H_
#define SANDBOX_SCOPED_PTR_H_

#include "base/common.h"

// A scoped_ptr<T> is just like T* except its destructor deletes
// the pointer it holds (if any).
// That is, scoped_ptr<T> owns T object it points to.
// Like T*, scoped_ptr<T> may hold NULL or pointer to a T object.
//
// Note: reset(...) also deletes the stored ponter. Use release() if you want
// scoped_ptr<T> to forget about pointer without deleting the object.
//
// WARNING: Dereferencing a NULL pointer using operator*/operator-> will result
// in an assertion failure in a Debug build. In Release build, the behavior is
// undefined.
template <class T>
class scoped_ptr {
 public:
  explicit scoped_ptr(T *p = NULL) {}
  ~scoped_ptr() {}

  void reset(T *p = NULL) {}
  T& operator*() {NOT_IMPLEMENTED;}
  T* operator->() {NOT_IMPLEMENTED;}
  T* get() const {NOT_IMPLEMENTED;}
  T* release() {NOT_IMPLEMENTED;}
  void swap(scoped_ptr& ptr) {}  // NOLINT

 private:
  DISALLOW_COPY_AND_ASSIGN(scoped_ptr);
};

#endif  // SANDBOX_SCOPED_PTR_H_
