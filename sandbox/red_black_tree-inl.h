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
  if (find(key)) {
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
  fixAfterInsert(new_node);

#ifndef NDEBUG
  checkProperties();
#endif
}

template<typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::get(const KeyType &key,
                                     ValueType *value_out) const {
  DCHECK(value_out != NULL);
  Node* node = find(key);
  if (node == NULL) {
    return false;
  }
  *value_out = node->value;
  return true;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::deleteChildren(Node* start_node) {
  if (start_node != NULL) {
    deleteChildren(start_node->left);
    deleteChildren(start_node->right);
  }
  delete start_node;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::checkProperties() const {
  if (root_ == NULL)
    return;
  DCHECK(root_->color == kBlack);
  DCHECK(root_->parent == NULL);
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
    DCHECK(isBlack(node->left));
    DCHECK(isBlack(node->right));
  }
  int rightHeight = 0;
  int leftHeight = 0;
  if (isBlack(node->right)) {
    rightHeight++;
  }
  if (isBlack(node->left)) {
    leftHeight++;
  }
  checkPropertiesInternal(node->right, &rightHeight);
  checkPropertiesInternal(node->left, &leftHeight);
  DCHECK(rightHeight == leftHeight);
  *height += rightHeight;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fixAfterInsert(Node* new_node) {
  while (!isBlack(new_node->parent)) {
    Node* parent = new_node->parent;
    if (parent->parent == NULL) {
      break;
    }
    bool uncle_left = (parent == parent->parent->right);
    bool node_left = (new_node == parent->left);
    Node* uncle;
    if (uncle_left) {
      uncle = parent->parent->left;
    } else {
      uncle = parent->parent->right;
    }
    if (!isBlack(uncle)) {
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

template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::remove(const KeyType &key) {
  Node* node = find(key);
  if (node == NULL)
    return false;
  removeInternal(node);
  return true;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::removeInternal(Node* node) {
  Node* replacement;
  if (node->left == NULL || node->right == NULL) {
    replacement = node;
  } else {
    replacement = node->right;
    while (replacement->left != NULL) {
      replacement = node->left;
    }
  }

  Node* child;
  if (replacement->left != NULL) {
    child = replacement->left;
  } else {
    child = replacement->right;
  }
  if (child != NULL) {
    child->parent = replacement->parent;
  }
  bool isLeftChild = true;
  if (replacement->parent == NULL) {
    root_ = child;
  } else if (replacement == replacement->parent->left) {
    replacement->parent->left = child;
  } else {
    replacement->parent->right = child;
    isLeftChild = false;
  }
  if (replacement != node) {
    node->key = replacement->key;
  }
  if (replacement->color == kBlack) {
    fixAfterRemove(isLeftChild, replacement->parent);
  }
  delete replacement;

#ifndef NDEBUG
  checkProperties();
#endif
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fixAfterRemove(bool isLeftChild,
                                                Node* parent) {
  Node* node;
  if (parent != NULL) {
    if (isLeftChild) {
      node = parent->left;
    } else {
      node= parent->right;
    }
  } else {
    node = root_;
  }
  while (node != root_ && isBlack(node)) {
    bool brother_right = node == parent->left;
    Node* brother = brother_right ? parent->right : parent->left;
    if (brother->color == kRed) {
      brother->color = kBlack;
      parent->color = kRed;
      if (brother_right) {
        rotateLeft(parent);
        brother = parent->right;
      } else {
        rotateRight(parent);
        brother = parent->left;
      }
    }
    if (isBlack(brother->left) && isBlack(brother->right)) {
      brother->color = kRed;
      node = parent;
      parent = node->parent;
    } else {
      Node* nephew = brother_right ? brother->right : brother->left;
      if (isBlack(nephew)) {
        if (brother->left != NULL)
          brother->left->color = kBlack;
        if (brother->right != NULL)
          brother->right->color = kBlack;
          brother->color = kRed;
          if (brother_right) {
            rotateRight(brother);
            brother = parent->right;
          } else {
            rotateLeft(brother);
            brother = parent->left;
          }
      }
      if (brother_right) {
        brother->right->color = kBlack;
        rotateLeft(parent);
      } else {
        brother->left->color = kBlack;
        rotateRight(parent);
      }
      brother->color = parent->color;
      parent->color = kBlack;
      node = root_;
    }
  }
  if (node != NULL)
    node->color = kBlack;
}

template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::removeValues(const ValueType &value) {
  return removeValuesInternal(root_, value);
}

template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::removeValuesInternal(Node* node,
                                                      const ValueType &value) {
  bool flag = false;
  if (node != NULL) {
    if (removeValuesInternal(node->left, value))
      flag = true;
    if (removeValuesInternal(node->right, value))
      flag = true;
    if (node->value == value) {
      removeInternal(node);
      flag = true;
    }
  }
  return flag;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node*
         RBTree<KeyType, ValueType>::find(const KeyType &key) const {
  Node* node = root_;
  while (node != NULL && key != node->key) {
    if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::isBlack(const Node* node) const {
  return node == NULL || node->color == kBlack;
}

#endif  // SANDBOX_RED_BLACK_TREE_INL_H_
