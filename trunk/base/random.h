// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_RANDOM_H_
#define BASE_RANDOM_H_

#include "base/common.h"

// Seed is required to make TrueRandom thread safe.
// Visit http://stackoverflow.com/questions/3973665 for more information.
// Generally consider using RandomGenerator instead of TrueRandom.
template<typename T>
inline T TrueRandom(uint32 *seed) {
  // TODO(timurrrr): better ideas?
  const size_t RAND_BITS = 15;
  T ret = 0;
  for (size_t i = 0; i < sizeof(T); i += RAND_BITS) {
    ret = (ret << RAND_BITS) | (rand_r(seed) & ((1 << RAND_BITS) - 1));
  }
  return ret;
}

inline uint32 RandomUInt32(uint32 *seed) { return TrueRandom<uint32>(seed); }
inline uint16 RandomUInt16(uint32 *seed) { return TrueRandom<uint16>(seed); }
inline byte   RandomByte(uint32 *seed)   { return TrueRandom<byte>(seed);   }

// This class allows thread safe random generation in the sense that
// two threads can safely call Generate() method of two __different__
// RandomGenerator objects simultaneously.
// This class is NOT THREAD-SAFE since calling Generate() method of one
// class instance from two threads will result in a data race.
// Hence don't use one instance of this class in more than one thread!
// It is recommended to use a scoped RandomGenerator if you want to write a test
// with semi-random numbers to achieve repeatability.
class RandomGenerator {
 public:
  explicit RandomGenerator(uint32 seed = 1) : seed_(seed) {}
  ~RandomGenerator() {}

  // Returns a random object of type T.
  template<typename T>
  T Generate() {
    return TrueRandom<T>(&seed_);
  }

  // Returns the seed that will be used in the next call to Generate().
  uint32 seed() const { return seed_; }

 private:
  uint32 seed_;
  DISALLOW_COPY_AND_ASSIGN(RandomGenerator)
};


#endif  // BASE_RANDOM_H_
