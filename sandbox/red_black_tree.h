// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_RED_BLACK_TREE_H_
#define SANDBOX_RED_BLACK_TREE_H_

#include "base/common.h"

template<typename KeyType, typename ValueType>
class RBTree {
 public:
  RBTree();

  ~RBTree();

  // Add node with specified key and value.
  void put(const KeyType &key, const ValueType &value);

  /* Remove node with specified key. 
     Return false if the key did not exist. */
  bool remove(const KeyType &key) {
    NOT_IMPLEMENTED;
    return false;
  }

  /* Remove all nodes, which contain specified value.
     Return false if the value did not exist. 
     Algorhithmic complexity is O(n), where n - number of nodes in the tree. */
  bool removeValues(const ValueType &value) {
    NOT_IMPLEMENTED;
    return false;
  }

  // TODO(pogr.yuo): Const-version.
  // Return false if key does not exist, otherwise return true
  bool get(const KeyType &key, ValueType *value_out);

 private:
  struct Node {
    KeyType key;
    ValueType value;
    byte color;
    Node* parent;
    Node* left;
    Node* right;

    Node() {
      color = kRed;
      parent = NULL;
      left = NULL;
      right = NULL;
    }
  };

  enum Colors {
    kBlack = 0,
    kRed = 1,
  };

  // delete all children of specified node
  void deleteChildren(Node* start_node);

  Node* find(const KeyType &key) {
    Node* node = root_;
    while (node != NULL && key != node->key) {
      if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return node;
  };

  Node *root_;

  DISALLOW_COPY_AND_ASSIGN(RBTree);
};

#endif  // SANDBOX_RED_BLACK_TREE_H_
