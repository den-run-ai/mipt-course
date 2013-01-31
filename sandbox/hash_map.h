// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_HASH_MAP_H_
#define SANDBOX_HASH_MAP_H_

#include <stddef.h>

template<class T>
class DefaultHasher {
  static size_t Hash(const T& value);
};

template<class KeyType, class ValueType,
         class Hasher = DefaultHasher<KeyType> >
class HashMap {
 public:
  HashMap() { }
  ~HashMap() { }

  size_t Size() {
    return 0;
  }
  void Clear() { }

  // Returns 'true' if 'key' is already present in the hash map and the value
  // is replaced.
  // Returns 'false' otherwise.
  bool Put(const KeyType& key, const ValueType& value) {
    return false;
  }

  // TODO(adech.fo): add a const version when the prototype is finalized.
  // Returns 'true' if 'key' was found in the hash map.
  // The value is placed in '*output'.
  // Returns 'false' otherwise and '*output' remains unchanged.
  bool Get(const KeyType& key, ValueType* output) {
    return false;
  }

  // Returns 'true' if 'key' was found in the hash map and erased.
  // Returns 'false' otherwise.
  bool Erase(const KeyType& key) {
    return false;
  }
};

#endif  // SANDBOX_HASH_MAP_H_
