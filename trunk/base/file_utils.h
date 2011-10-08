// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILE_UTILS_H_
#define BASE_FILE_UTILS_H_
#pragma once

#include <stdio.h>

#include <string>

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

#endif  // BASE_FILE_UTILS_H_
