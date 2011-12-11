// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_RANDOM_H_
#define BASE_RANDOM_H_

#include "base/common.h"

// rand() is not thread-safe, hence it is FORBIDDEN in our codebase.
// rand_r(&seed) is thread-safe if seed is thread-local.
// Visit http://stackoverflow.com/questions/3973665 for more information.
//
// To achieve "true" randomness, you should use a random seed
// (e.g initial seed=current time).
// However, this is not good for continuous testing environment since this
// may cause your tests to produce diffent results
// (e.g. fail once in every 100 runs, very likely on unrelated commits).
//
// RandomGenerator is a class to add determinism to "random" code when it is
// run in test mode.
// If you want to write a test with semi-random numbers consider using a scoped
// instance of this class with a hard-coded initial seed to achieve
// repeatability.
// If you want to write a class that has some semi-random algorithm please
// consider specifying a RandomGenerator as a constructor argument and
// DON'T use rand_r() directly.
//
// This class allows thread safe random generation in the sense that
// two threads can safely call Generate() method of two __different__
// RandomGenerator objects simultaneously.
// This class is NOT THREAD-SAFE since calling Generate() method of one
// class instance from two threads will result in a data race.
// Hence don't use one instance of this class in more than one thread!
class RandomGenerator {
 public:
  explicit RandomGenerator(uint32 seed = 1) : seed_(seed) {}
  ~RandomGenerator() {}

  // Returns a random object of type T.
  // TODO(timurrrr): it's very likely this template doesn't work well with
  // floats and doubles and more complex types.
  template<typename T>
  T Generate() {
    // TODO(timurrrr): better ideas?
    const size_t RAND_BITS = 15;
    T ret = 0;
    for (size_t i = 0; i < sizeof(T); i += RAND_BITS) {
      ret = (ret << RAND_BITS) | (rand_r(&seed_) & ((1 << RAND_BITS) - 1));
    }
    return ret;
  }

  // Returns a random number of type T in range [0, upper_bound)
  // It's assumed that T is an integral type
  template<typename T>
  T Generate(const T& upper_bound) {
    DCHECK(upper_bound > T(0));
    return Generate<T>() % upper_bound;
  }

  // Returns a random number of type T in range [lower_bound, upper_bound)
  // It's assumed that T is an integral type
  template<typename T>
  T Generate(const T& lower_bound, const T& upper_bound) {
    DCHECK(lower_bound < upper_bound);
    return lower_bound + Generate<T>() % (upper_bound - lower_bound);
  }

  // Returns the seed that will be used in the next call to Generate().
  uint32 seed() const { return seed_; }

 private:
  uint32 seed_;
  DISALLOW_COPY_AND_ASSIGN(RandomGenerator)
};


#endif  // BASE_RANDOM_H_
