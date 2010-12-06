// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_TREAP_H_
#define SANDBOX_TREAP_H_

#include "base/common.h"

/*  Treap
 *  http://en.wikipedia.org/wiki/Treap
 *  Treap is a binary search tree supports search, insertion and deletion in 
 *  O (log n) time and some specific operations like reversing
 *  elements in a given segment.
 */

template <class K, class V>
class Treap {
 public:
  Treap();
  ~Treap();

  void Insert(const K& key, const V& value);
  bool Contains(const K& key) const;
  V Get(const K& key) const;
  void Erase(const K& key);
  size_t size() const;

 private:
  struct Node {
    K key;
    V value;
    Node *l, *r;
  };

  Node * root;
  DISALLOW_COPY_AND_ASSIGN(Treap);
};

template <class K, class V>
Treap<K, V>::Treap() {
  // TODO(volkhin)
}

template <class K, class V>
Treap<K, V>::~Treap() {
  // TODO(volkhin)
}

template <class K, class V>
void Treap<K, V>::Insert(const K& key, const V& value) {
  // TODO(volkhin)
}

template <class K, class V>
bool Treap<K, V>::Contains(const K& key) const {
  // TODO(volkhin)
  return false;
}

template <class K, class V>
V Treap<K, V>::Get(const K& key) const {
  // TODO(volkhin)
  return V();
}

template <class K, class V>
void Treap<K, V>::Erase(const K& key) {
  // TODO(volkhin)
}

template <class K, class V>
size_t Treap<K, V>::size() const {
  // TODO(volkhin)
  return 0;
}

#endif  // SANDBOX_TREAP_H_
