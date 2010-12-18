// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_RANDOM_H_
#define BASE_RANDOM_H_

template<typename T>
inline T TrueRandom() {
  // TODO(timurrrr): better ideas?
  // What about thread safety?
  static uint32 seed = 1;
  const size_t RAND_BITS = 15;
  T ret = 0;
  for (size_t i = 0; i < sizeof(T); i += RAND_BITS) {
    ret = (ret << RAND_BITS) | (rand_r(&seed) & ((1 << RAND_BITS) - 1));
  }
  return ret;
}

inline uint32 RandomUInt32() { return TrueRandom<uint32>(); }
inline uint16 RandomUInt16() { return TrueRandom<uint16>(); }
inline byte   RandomByte()   { return TrueRandom<byte>();   }

#endif  // BASE_RANDOM_H_
