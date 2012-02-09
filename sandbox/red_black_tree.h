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

  /* Add node with specified key and value.
     If key already exists, value is not rewritten */
  void put(const KeyType &key, const ValueType &value);

  /* Remove node with specified key. 
     Return false if the key did not exist. */
  bool remove(const KeyType &key);

  /* Remove all nodes, which contain specified value.
     Return false if the value did not exist. 
     Algorhithmic complexity is O(n), where n - number of nodes in the tree. */
  bool removeValues(const ValueType &value);

  // Returns false if key does not exist, otherwise return true.
  bool get(const KeyType &key, ValueType *value_out) const;

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

  // Delete all children of specified node.
  void deleteChildren(Node* start_node);

  // Check red-black properties of the tree and assert if anything is wrong.
  void checkProperties() const;

  /* Check if black height of right child equals black height of left child
     and if both children of the red node are black. 
     After the call *height will be increased by the black height of the node.
     Black height is the number of black children in the path from node to any
     reachable leaf (moving from parent to child). This number must be equal
     for all reachable leaves. Black height of a leaf is always zero. All NULL
     leaves are black by definition. */
  void checkPropertiesInternal(const Node* node, int* height) const;

  // Fix red-black properties of the tree after inserting a new node.
  void fixAfterInsert(Node* insertedNode);

  // Fix red-black properties of the tree after deleting a node.
  void fixAfterRemove(bool isLeftChild, Node* parent);

  // Swap the given node and its left child.
  void rotateLeft(Node* node);

  // Swap the given node and its right child.
  void rotateRight(Node* node);

  // Recursive internal function for removeValues(const ValueType &value).
  bool removeValuesInternal(Node* node, const ValueType &value);

  // Internal function for remove(const KeyType &key).
  void removeInternal(Node* node);

  // Returns node with specified key, or a leaf if such node does not exist
  Node* find(const KeyType &key) const;

  // Returns true if node is black or if node is a null-leaf
  bool isBlack(const Node* node) const;

  Node* root_;

  DISALLOW_COPY_AND_ASSIGN(RBTree);
};

#endif  // SANDBOX_RED_BLACK_TREE_H_
