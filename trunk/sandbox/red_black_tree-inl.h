// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_RED_BLACK_TREE_INL_H_
#define SANDBOX_RED_BLACK_TREE_INL_H_

#include "sandbox/red_black_tree.h"

template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree() {
  root_ = NULL;
}

template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::~RBTree() {
  deleteChildren(root_);
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::put(const KeyType &key,
                                     const ValueType &value) {
  Node* node = find(key);
  if (node != NULL) {
    node->value = value;
    return;
  }

  Node* new_node = new Node;
  new_node->key = key;
  new_node->value = value;

  Node* parent = NULL;
  Node* temp = root_;
  while (temp != NULL) {
    parent = temp;
    if (new_node->key < temp->key) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }

  new_node->parent = parent;
  if (parent == NULL) {
    root_ = new_node;
  } else if (new_node->key < parent->key) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
}

template<typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::get(const KeyType &key, ValueType *value_out) {
  assert(value_out != NULL);
  Node* node = find(key);
  if (node == NULL) {
    return false;
  }
  *value_out = node->value;
  return true;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::deleteChildren(Node* start_node) {
  if (start_node == NULL)
    return;
  deleteChildren(start_node->left);
  deleteChildren(start_node->right);
  delete start_node;
}

#endif  // SANDBOX_RED_BLACK_TREE_INL_H_
