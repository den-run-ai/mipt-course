// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/file_utils.h"

#include <unistd.h>

#include <string>

#include "base/common.h"

bool ReadFileToString(const std::string &filename, std::string *contents) {
  CHECK(contents != NULL);

  FILE *fp = fopen(filename.c_str(), "r");
  if (fp == NULL)
    return false;

  const int BUFFER_SIZE = 50;
  char buf[BUFFER_SIZE];
  while (!feof(fp) && !ferror(fp)) {
    if (fgets(buf, BUFFER_SIZE, fp)) {
      // fgets necessarily wrote '\0' at the end.
      *contents += buf;
    }
  }

  if (ferror(fp) != 0)
    return false;

  return (fclose(fp) == 0);
}

bool WriteStringAs(const std::string &filename, const std::string &contents) {
  FILE *fp = fopen(filename.c_str(), "w");
  if (fp == NULL)
    return false;

  unsigned int bytes_to_write = contents.length();
  if (fwrite(contents.c_str(), 1, bytes_to_write, fp) != bytes_to_write) {
    fclose(fp);
    return false;
  }

  if (ferror(fp) != 0)
    return false;

  return (fclose(fp) == 0);
}

bool PathExists(const std::string &path) {
  return (access(path.c_str(), F_OK));
}

bool PathAccessPermitted(const std::string &path, int mode) {
  return (access(path.c_str(), mode));
}
