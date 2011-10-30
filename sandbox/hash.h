// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_HASH_H_
#define SANDBOX_HASH_H_

#include <stdlib.h>
#include "base/common.h"

template<class Key, class Value>
class HashTable {
 public:
  HashTable();
  explicit HashTable(size_t size);
  ~HashTable();
  void Add(const Key &key, const Value &value);
  bool Remove(const Key &key);
  bool Contains(const Key &key) const;
  Value& operator[] (const Key &key);
  const Value& operator[] (const Key &key) const;
  size_t Size() const;

 private:
  size_t Hash(const Key &key) const;  // Calculate hash for a given key.
  class Record {
   public:
    Record() {}
    ~Record() {}
    Key key;
    Value value;
    Record *next;
  };
  Record *rec;

  DISALLOW_COPY_AND_ASSIGN(HashTable);
};

template<class Key, class Value>
HashTable<Key, Value>::HashTable() {
  // TODO(kirillkame): Create an array of Records with value of elements
  // defined by some value.
}

template<class Key, class Value>
HashTable<Key, Value>::HashTable(size_t size) {
  // TODO(kirillkame): Create an array of Records with value of elements
  // defined by size.
}

template<class Key, class Value>
HashTable<Key, Value>::~HashTable() {
  // TODO(kirillkame): Free memory.
}

template<class Key, class Value>
void HashTable<Key, Value>::Add(const Key &key, const Value &value) {
  // TODO(kirillkame): Calculate Hash, add reccord.
}

template<class Key, class Value>
bool HashTable<Key, Value>::Remove(const Key &key) {
  // TODO(kirillkame): Calculate Hash, delete 'existing' record.
  return true;
}

template<class Key, class Value>
bool HashTable<Key, Value>::Contains(const Key &key) const {
  // TODO(kirillkame): Calculate Hash, find Record with 'key',
  // exist or not exist.
  return true;
}

template<class Key, class Value>
Value& HashTable<Key, Value>::operator[](const Key &key) {
  // TODO(kirillkame): Find Record with 'key', return value or
  // set new one.
  return *(new Value);  // ugly hack to make this compile without warnings.
}

template<class Key, class Value>
const Value& HashTable<Key, Value>::operator[](const Key &key) const {
  // TODO(kirillkame): Find Record with 'key', return value.
  return *(new Value);  // ugly hack to make this compile without warnings.
}

template<class Key, class Value>
size_t HashTable<Key, Value>::Size() const {
  // TODO(kirillkame): returns size of the HashTable?
  return 0;
}

template<class Key, class Value>
size_t HashTable<Key, Value>::Hash(const Key &key) const {
  // TODO(kirillkame): Calculate Hash for 'key'.
  return 0;
}

#endif  // SANDBOX_HASH_H_

