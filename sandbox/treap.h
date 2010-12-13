// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_TREAP_H_
#define SANDBOX_TREAP_H_

#include "base/common.h"
#include "base/random.h"

/*  Treap
 *  http://en.wikipedia.org/wiki/Treap
 *  Treap is a binary search tree supports search, insertion and deletion in 
 *  O (log n) time and some specific operations like reversing
 *  elements in a given segment.
 */

template <class K, class V>
class Treap {
 public:
  Treap() : root_(NULL), size_(0) {}

  ~Treap() {
    DeleteRecursive(root_);
  }

  // Insert a new element into the tree.
  void Insert(const K& key, const V& value);

  // Check if a node with given key exists in the tree.
  bool Contains(const K& key) const;

  // Returns value of a node with given key. Such node must exists in a tree.
  V Get(const K& key) const;

  // Remove a node with given key. Exactly one such a node must be in the tree.
  bool Erase(const K& key);

  // Returns size of a tree.
  size_t size() const {
    return size_;
  }

 private:
  struct Node {
    K key;
    V value;
    int priority;
    Node *left, *right;
    Node() : left(NULL), right(NULL) {}

    Node(const K& key, const V& value, int priority)
        : key(key), value(value), priority(priority), left(NULL), right(NULL) {}
  };

  Node* root_;
  size_t size_;

  // Split the given tree into two using the 'key' as a delimeter.
  // This function returns the subtrees using 'left' and 'right' pointers.
  // (*left) will store a pointer to the root node of the tree with all keys
  // less than 'key';
  // (*right) will store the root of the tree with the remaining keys.
  void Split(Node* root, const K& key, Node** left, Node** right);

  // Merge two trees with the given root nodes.
  // Returns a pointer to the root node of the merged tree.
  Node* Merge(Node* left, Node* right);

  // Recursively deletes the tree starting from root.
  void DeleteRecursive(Node* node);

  bool EraseInternal(Node*& root, const K& key);

  // Returns pointer to a node with given key or NULL if it doesn't exist.
  Node* FindNode(const K& key) const;

  DISALLOW_COPY_AND_ASSIGN(Treap);
};

template <class K, class V>
void Treap<K, V>::Insert(const K& key, const V& value) {
  Node *node = new Node(key, value, TrueRandom<int>());
  Node *left = NULL, *right = NULL;
  Split(root_, node->key, &left, &right);
  root_ = Merge(Merge(left, node), right);
  ++size_;
}

template <class K, class V>
bool Treap<K, V>::Contains(const K& key) const {
  return FindNode(key) != NULL;
}

template <class K, class V>
V Treap<K, V>::Get(const K& key) const {
  Node* node = FindNode(key);
  CHECK(node != NULL);
  return node->value;
}

template <class K, class V>
bool Treap<K, V>::Erase(const K& key) {
  return EraseInternal(root_, key);
}

template <class K, class V>
void Treap<K, V>::Split(Node* root, const K& key, Node** left, Node** right) {
  DCHECK(left != NULL);
  DCHECK(right != NULL);
  if (root == NULL) {
    *left = *right = NULL;
  } else if (root->key < key) {
    Split(root->right, key, &(root->right), right);
    *left = root;
  } else {
    Split(root->left, key, left, &(root->left));
    *right = root;
  }
}

template <class K, class V>
typename Treap<K, V>::Node* Treap<K, V>::Merge(Node* left, Node* right) {
  Node* ret = NULL;

  if (left == NULL) {
    ret = right;
  } else if (right == NULL) {
    ret = left;
  } else if (left->priority < right->priority) {
    left->right = Merge(left->right, right);
    ret = left;
  } else {
    right->left = Merge(left, right->left);
    ret = right;
  }

  return ret;
}

template <class K, class V>
void Treap<K, V>::DeleteRecursive(Node* root) {
  if (root == NULL)
    return;

  if (root->left != NULL)
    DeleteRecursive(root->left);
  if (root->right != NULL)
    DeleteRecursive(root->right);

  delete root;
}

template <class K, class V>
typename Treap<K, V>::Node* Treap<K, V>::FindNode(const K& key) const {
  Node* node = root_;
  while (node != NULL && node->key != key) {
    if (node->key > key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

template <class K, class V>
bool Treap<K, V>::EraseInternal(Node*& root, const K& key) {
  if (root == NULL)
    return false;

  if (root->key == key) {
    Node *left = root->left, *right = root->right;
    delete root;
    root = Merge(left, right);
    --size_;
    return true;
  } else if (root->key < key) {
    return EraseInternal(root->right, key);
  } else {
    return EraseInternal(root->left, key);
  }
}

#endif  // SANDBOX_TREAP_H_
