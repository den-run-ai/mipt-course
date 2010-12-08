// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef SANDBOX_AVL_H_
#define SANDBOX_AVL_H_

#include <stdlib.h>  // For the NULL pointer

template <class T>
class AVLTree {
 public:
  AVLTree();
  ~AVLTree();
  bool Add(const T& item);     // returns true on success.
  void Delete(const T& item);  // returns false if not found.
  T* Find(const T& item);      // returns pointer to the item.
                               // it's up to user to define >, <, == operators.
 private:
  template <class N>
  struct Node {
    int balance;
    struct Node<N>* left;
    struct Node<N>* right;
  };
  struct Node<T>* root;
};

template <class T>
AVLTree<T>::AVLTree() {
  root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree() {
  // TODO(kazeevn) smth
}

template <class T>
bool AVLTree<T>::Add(const T& item) {
  return false;
}

template <class T>
T* AVLTree<T>::Find(const T& item) {
  return 0;
}

template <class T>
void AVLTree<T>::Delete(const T& item) {
}


template<class TKey, class TValue>
class KeyValuePair {
 public:
  KeyValuePair() {}

  KeyValuePair(TKey key, TValue value) : key_(key), data_(value) {}

  KeyValuePair(const KeyValuePair & from) {
    key_ = from.key();
    data_ = from.data();
  }

  ~KeyValuePair() {}

  TKey key() const { return key_; }
  TValue data() const { return data_; }

  // Overloading is necessary to make
  // work with standart types
  // TODO(kazeevn): add support for custom comparators.
  // Just compares the keys.
  inline bool operator< (const KeyValuePair &op2) {
    return ( key_ < op2.key() );
  }

  inline bool operator> (const KeyValuePair &op2) {
    return ( key_ > op2.key() );
  }

 private:
  TKey key_;
  TValue data_;
  inline bool operator== (const KeyValuePair &op2) {
    return (key_ == op2.key());
  }
};

template <class Key, class Value>
class AVLMap : public AVLTree< KeyValuePair <Key, Value> > {};

#endif  // SANDBOX_AVL_H_
