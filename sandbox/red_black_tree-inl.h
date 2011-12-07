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
  fixRedBlackProperties(new_node);
#ifndef NDEBUG
  checkProperties();
#endif
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

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::checkProperties() const {
  if (root_ == NULL)
    return;
  assert(root_->color == kBlack && root_->parent == NULL);
  int height = 0;
  checkPropertiesInternal(root_, &height);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::checkPropertiesInternal(const Node* node,
                                                          int* height) const {
  if (node == NULL)
    return;
  if (node->left != NULL) {
    DCHECK(node->key > node->left->key);
    DCHECK(node->left->parent == node);
  }
  if (node->right != NULL) {
    DCHECK(node->key < node->right->key);
    DCHECK(node->right->parent == node);
  }
  if (node->color == kRed) {
    DCHECK(node->left == NULL || node->left->color == kBlack);
    DCHECK(node->right == NULL || node->right->color == kBlack);
  }
  int rightHeight = 0;
  int leftHeight = 0;
  if (node->right == NULL || node->right->color == kBlack) {
    rightHeight++;
  }
  if (node->left == NULL || node->left->color == kBlack) {
    leftHeight++;
  }
  checkPropertiesInternal(node->right, &rightHeight);
  checkPropertiesInternal(node->left, &leftHeight);
  DCHECK(rightHeight == leftHeight);
  *height += rightHeight;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fixRedBlackProperties(Node* new_node) {
  Node* uncle = NULL;

  while (new_node->parent != NULL && new_node->parent->color == kRed) {
    Node* parent = new_node->parent;
    bool uncle_left = (parent == parent->parent->right);
    bool node_left = (new_node == parent->left);
    if (uncle_left) {
      uncle = parent->parent->left;
    } else {
      uncle = parent->parent->right;
    }
    if (uncle != NULL && uncle->color == kRed) {
      parent->color = kBlack;
      uncle->color = kBlack;
      parent->parent->color = kRed;
      new_node = parent->parent;
    } else {
      if (uncle_left == node_left) {
        new_node = parent;
        if (uncle_left) {
          rotateRight(new_node);
        } else {
          rotateLeft(new_node);
        }
      }
      parent = new_node->parent;
      parent->color = kBlack;
      parent->parent->color = kRed;
      if (uncle_left) {
        rotateLeft(parent->parent);
      } else {
        rotateRight(parent->parent);
      }
    }
  }
  root_->color = kBlack;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::rotateLeft(Node* node) {
  if (node->right == NULL)
    return;
  Node* temp = node->right;
  node->right = temp->left;
  if (temp->left != NULL) {
    temp->left->parent = node;
  }
  temp->parent = node->parent;
  if (node->parent == NULL) {
    root_ = temp;
  } else if (node == node->parent->left) {
    node->parent->left = temp;
  } else {
    node->parent->right = temp;
  }
  temp->left = node;
  node->parent = temp;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::rotateRight(Node* node) {
  if (node->left == NULL)
    return;
  Node* temp = node->left;
  node->left = temp->right;
  if (temp->right != NULL) {
    temp->right->parent = node;
  }
  temp->parent = node->parent;
  if (node->parent == NULL) {
    root_ = temp;
  } else if (node == node->parent->right) {
    node->parent->right = temp;
  } else {
    node->parent->left = temp;
  }
  temp->right = node;
  node->parent = temp;
}

#endif  // SANDBOX_RED_BLACK_TREE_INL_H_
