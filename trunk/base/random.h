// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_RANDOM_H_
#define BASE_RANDOM_H_

template<typename T>
inline T TrueRandom() {
  // TODO(timurrrr): better ideas?
  // What about thread safety?
  const int RAND_BITS = 15;
  T ret = 0;
  for (int i = 0; i < sizeof(T); i+=RAND_BITS) {
    ret = (ret << RAND_BITS) | rand();
  }
  return ret;
}

inline uint RandomUInt() { return TrueRandom<uint>(); }
inline ushort RandomUShort() { return TrueRandom<ushort>(); }
inline byte RandomByte() { return TrueRandom<byte>(); }

#endif  // BASE_RANDOM_H_
