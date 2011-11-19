// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

template<typename K, typename V>
class LruCache {
 public:
  explicit LruCache(int size) {}

  void Put(const K &key, const V &value) {}

  // Doesn't update timestamps.
  bool Contains(const K &key) const { return false; }

  // Updates timestamps.
  bool Lookup(const K &key, V *value) { return false; }

  bool LookupNoUpdate(const K &key, V *value) const { return false; }
};

TEST(LruCacheTests, DISABLED_Simple) {
  LruCache<int, int> lru(2);

  ASSERT_FALSE(lru.Contains(1));
  lru.Put(1 /* key */, 42 /* value */);
  ASSERT_TRUE(lru.Contains(1));
  int value = -1;
  ASSERT_TRUE(lru.Lookup(1, &value));
  ASSERT_EQ(42, value);

  lru.Put(13, 77);
  ASSERT_TRUE(lru.Contains(13));
  ASSERT_TRUE(lru.Contains(1));
}

TEST(LruCacheTests, DISABLED_Eviction) {
  LruCache<int, int> lru(2);
  lru.Put(1, 42);
  lru.Put(2, 13);
  ASSERT_TRUE(lru.Contains(1));
  ASSERT_TRUE(lru.Contains(2));

  lru.Put(3, 77);  // should evict '1'.
  ASSERT_FALSE(lru.Contains(1));
  ASSERT_TRUE(lru.Contains(2));
  ASSERT_TRUE(lru.Contains(3));

  lru.Put(2, 42);  // refreshes the timestamp of '2'
  ASSERT_TRUE(lru.Contains(2));
  int value = -1;
  ASSERT_TRUE(lru.LookupNoUpdate(2, &value));
  ASSERT_EQ(42, value);
  ASSERT_TRUE(lru.Contains(3));

  lru.Put(4, 99);  // should evict '3'.
  ASSERT_TRUE(lru.Contains(2));
  ASSERT_FALSE(lru.Contains(3));
  ASSERT_TRUE(lru.Contains(4));
}
