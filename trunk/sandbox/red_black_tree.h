// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_RED_BLACK_TREE_H_
#define SANDBOX_RED_BLACK_TREE_H_

#include "base/common.h"

template<typename KeyType, typename ValueType>
class RBTree {
 public:
  RBTree() {
    NOT_IMPLEMENTED;
  }

  ~RBTree() {
    NOT_IMPLEMENTED;
  }

  // Add node with specified key and value.
  void put(const KeyType &key, const ValueType &value) {
    NOT_IMPLEMENTED;
  }

  /* Remove node with specified key. 
     Return false if the key did not exist. */
  bool remove(KeyType key) {
    NOT_IMPLEMENTED;
    return false;
  }

  /* Remove all nodes, which contain specified value.
     Return false if the value did not exist. 
     Algorhithmic complexity is O(n), where n - number of nodes in the tree. */
  bool removeValues(ValueType value) {
    NOT_IMPLEMENTED;
    return false;
  }

  // TODO(pogr.yuo): Const-version.
  ValueType get(KeyType key) {
    NOT_IMPLEMENTED;
    return ValueType();
  }

 private:
  struct Node {
    KeyType key;
    ValueType value;
    byte color;
    Node* parent;
    Node* left;
    Node* right;
  };

  Node* root;
};

#endif  // SANDBOX_RED_BLACK_TREE_H_
