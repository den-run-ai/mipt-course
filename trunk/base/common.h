// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef BASE_COMMON_H_
#define BASE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <limits>

// Use CHECK instead of assert for the following reasons:
// a) CHECKs remain when NDEBUG is defined (use DCHECK for debug-only checks)
// b) Has the same error message format on all platforms
// c) TODO(timurrrr): print stack trace when hitting a CHECK while preserving
//    "abort trap" feature on both Windows and POSIX.
// TODO(timurrrr): use OutputDebugString on Windows.
#define CHECK(x) \
    do {\
      if ((x) == 0) { \
        fprintf(stderr, "CHECK failed: \"%s\" at %s:%d\n", \
                #x, __FILE__, __LINE__); \
        abort(); \
      } \
    } while (0)

#ifdef NDEBUG
// Release build. DCHECK should be no-op but the condition should be buildable.
#define DCHECK(x) do { } while (0 && (x))
#else
#define DCHECK(x) CHECK(x)
#endif

// TODO(timurrrr): define proper CHECK_EQ, DCHECK_EQ, ... printing their args
// in case of failure.
#define CHECK_EQ(x,y) CHECK((x) == (y))     // NOLINT
#define CHECK_GT(x,y) CHECK((x) > (y))      // NOLINT
#define CHECK_GE(x,y) CHECK((x) >= (y))     // NOLINT
#define CHECK_LT(x,y) CHECK((x) < (y))      // NOLINT
#define CHECK_LE(x,y) CHECK((x) <= (y))     // NOLINT
#define DCHECK_EQ(x,y) DCHECK((x) == (y))   // NOLINT
#define DCHECK_GT(x,y) DCHECK((x) > (y))    // NOLINT
#define DCHECK_GE(x,y) DCHECK((x) >= (y))   // NOLINT
#define DCHECK_LT(x,y) DCHECK((x) < (y))    // NOLINT
#define DCHECK_LE(x,y) DCHECK((x) <= (y))   // NOLINT

// Use this macro to disable copy constructor and operator= for CLASS_NAME. See
// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Copy_Constructors#Copy_Constructors
#define DISALLOW_COPY_AND_ASSIGN(CLASS_NAME) \
      CLASS_NAME(const CLASS_NAME &); \
  void operator=(const CLASS_NAME &);

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef unsigned char uchar;
typedef unsigned char byte;
typedef uint16_t      uint16;
typedef uint32_t      uint32;
const uint32 MAX_UINT32 = 0xFFFFFFFF;
// TODO(timurrrr): add 64-bit and ptr type values when necessary.

#endif  // BASE_COMMON_H_
