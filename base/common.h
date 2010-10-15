// Copyright (c) 2010 Timur Iskhodzhanov and others. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef BASE_COMMON_H_
#define BASE_COMMON_H_

#include <assert.h>

// Use CHECK instead of assert.
// TODO(timurrrr): print stack trace when hitting a CHECK while preserving
// "abort trap" feature on both Windows and POSIX.
#define CHECK(x) assert(x)

#ifdef _DEBUG
#define DCHECK(x) CHECK(x)
#else
#define DCHECK(x) do { } while (0 && (x))
#endif

// Use this macro to disable copy constructor and operator= for CLASS_NAME. See
// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Copy_Constructors#Copy_Constructors
#define DISALLOW_COPY_AND_ASSIGN(CLASS_NAME) \
      CLASS_NAME(const CLASS_NAME &); \
  void operator=(const CLASS_NAME &);

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef unsigned char  uchar;
typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
const uint MAX_UINT = 0xFFFFFFFF;
// TODO(timurrrr): add 64-bit and ptr type values when necessary.

#endif  // BASE_COMMON_H_
