// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILE_UTILS_H_
#define BASE_FILE_UTILS_H_
#pragma once

#include <stdio.h>

#include <string>

#include "base/common.h"

// Read text file into string *contents.
// Returns true on success, false on failure.
bool ReadFileToString(const std::string &filename, std::string *contents);

// Write string to text file.
// Returns true on success, false on failure.
bool WriteStringAs(const std::string &filename, const std::string &contents);

// Returns true if path exists.
bool PathExists(const std::string &path);

// Returns true if all the operations of the mode are permitted.
bool PathAccessPermitted(const std::string &path, int mode);

// A smart pointer-like class useful for handling FILE* ownership,
// similar to auto_ptr<>.
class ScopedFile {
 public:
  explicit ScopedFile(FILE *ptr) : ptr_(ptr) { }

  ~ScopedFile() {
    fclose(ptr_);
  }

  FILE* Release() {
    FILE* result = ptr_;
    ptr_ = NULL;
    return result;
  }

 private:
  FILE *ptr_;
  DISALLOW_COPY_AND_ASSIGN(ScopedFile);
};

#endif  // BASE_FILE_UTILS_H_
