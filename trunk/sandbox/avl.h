// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef SANDBOX_AVL_H_
#define SANDBOX_AVL_H_

#include <stdlib.h>  // For the NULL pointer

#include "base/common.h"

// User must define <, >, != operations for type T
// TODO(kazeevn) Implement the class using only < operator,
template <class T>
class AVLTree {
 public:
  AVLTree();
  ~AVLTree();
  bool Add(const T& item);     // Returns true on success.
  void Delete(const T& item);  // Returns false if not found.
  T* Find(const T& item);      // Returns a pointer to the
                               // item which is equal to 'item'.
 private:
  template <class N>
  struct Node {
    T data;
    struct Node<N>* left, *right;
    char balance;
  };

  // TODO(kazeevn) write a debug function to check if the tree is an AVL tree

  void clean(struct Node<T>* node);  // Recursively cleans the subtree
  bool RecursiveAdd(const T&, struct Node<T>* &current);
  char RecursiveDelete(const T& item, struct Node<T>* p, struct Node<T>** link);
  // An internal method to remove the leftmost node in the right subtree
  char RecursiveRminDelete(struct Node<T>* &p, T* put_here);
  struct Node<T>* Leaf(const T& item);
  void SingleRightRotation(struct Node<T>* &p);
  void DoubleRightRotation(struct Node<T>* &p);
  void SingleLeftRotation(struct Node<T>* &p);
  void DoubleLeftRotation(struct Node<T>* &p);

  struct Node<T>* root;
};

template <class T>
AVLTree<T>::AVLTree() {
  root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree() {
  clean(root);
}

template <class T>
void AVLTree<T>::clean(struct Node<T>* node) {
  if (node->right != NULL)
    clean(node->right);
  if (node->left != NULL)
    clean(node->left);
  delete node;
}

template <class T>
bool AVLTree<T>::Add(const T& item) {
  if (root == NULL) {
    root = Leaf(item);
    if (root != NULL)
      return true;
    else
      return false;
  } else {
    RecursiveAdd(item, root);
    return true;
  }
}

template <class T>
struct AVLTree<T>::Node<T>* AVLTree<T>::Leaf(const T& item) {
  struct Node<T>* res = new struct Node<T>;
  res->data = T(item);
  res->left = NULL;
  res->right = NULL;
  res->balance = 0;
  return res;
}

template <class T>
// returns true if a rebalancig is needed
bool AVLTree<T>::RecursiveAdd(const T& item, struct Node<T>* &current) {
  if (item < current->data)
    if (current->left == NULL) {
      current->left = Leaf(item);
      return true;
    } else if (RecursiveAdd(item, current->left)) {
      if (current->balance == -1) {
        if ((*current->left).balance == 1)
          DoubleRightRotation(current);
        else
          SingleRightRotation(current);
        return false;
      } else if (current->balance == 0) {
        current->balance = -1;
        return true;
      } else {
        current->balance = 0;
        return false;
      }
    } else {
     return false;
  } else {
    if  (current->right == NULL) {
     current->right = Leaf(item);
     return true;
    } else if (RecursiveAdd(item, current->right)) {
      if (current->balance == 1) {
        if ((*current->right).balance == -1)
          DoubleLeftRotation(current);
        else
          SingleLeftRotation(current);
        return false;
      } else if (current->balance == 0) {
        current->balance = 1;
        return true;
      } else {
        current->balance = 0;
        return false;
      }
    } else {
    return false;
    }
  }
}

template <class T>
void AVLTree<T>::SingleRightRotation(struct Node<T>* &p) {
  struct Node<T>* lc = p->left;
  p->balance = 0;
  lc->balance = 0;
  p->left = lc->right;
  lc->right = p;
  p = lc;
}

template <class T>
void AVLTree<T>::SingleLeftRotation(struct Node<T>* &p) {
  struct Node<T>* rc = p->right;
  p->balance = 0;
  rc->balance = 0;
  p->right = rc->left;
  rc->left = p;
  p = rc;
}

template <class T>
void AVLTree<T>::DoubleRightRotation(struct Node<T>* &p) {
  struct Node<T>* lc = p->left;
  struct Node<T>* np = lc->right;
  if (np->balance == 1) {
    p->balance = 0;
    lc->balance = 1;
  } else {
    p->balance = 1;
    lc->balance = 0;
  }
  np->balance = 0;

  lc->right = np->left;
  np->left = lc;
  p->left = np->right;
  np->right = p;
  p = np;
}

template <class T>
void AVLTree<T>::DoubleLeftRotation(struct Node<T>* &p) {
  struct Node<T>* rc = p->right;
  struct Node<T>* np = rc->left;
  if (np->balance == -1) {
    p->balance = 0;
    rc->balance = -1;
  } else {
    p->balance = -1;
    rc->balance = 0;
  }
  np->balance = 0;

  rc->left = np->right;
  np->right = rc;
  p->right = np->left;
  np->left = p;
  p = np;
}

template <class T>
T* AVLTree<T>::Find(const T& item) {
  struct Node<T>* current = root;
  while ((current != NULL) && (current->data != item)) {
    if ((current->left != NULL) && (item < current->data))
      current = current->left;
    else if ((current->right != NULL) && (item > current->data))
      current = current->right;
    else
      current = NULL;
  }
  if (current != NULL)
    return &(current->data);
  else
    return NULL;
}

template <class T>
void AVLTree<T>::Delete(const T& item) {
  RecursiveDelete(item, root, &root);
}

template<class T>
char AVLTree<T>::RecursiveRminDelete(struct Node<T>* &p, T* put_here) {
  CHECK(p != NULL);
  if (p->left != NULL) {
    p->balance -= RecursiveRminDelete(p->left, put_here);
    if (p->balance == 2) {
     if ((*p->right).balance == -1)
       DoubleLeftRotation(p);
     else
       SingleLeftRotation(p);
     return -1;
    } else {
      return 0;
    }
  } else if (p->right == NULL) {
    (*put_here) = p->data;
    delete p;
    p = NULL;
    return -1;
  } else {
    struct Node<T>* tmp = p->right;
    (*put_here) = p->data;
    delete p;
    p = tmp;
    return 0;
  }
}

template<class T>  //  Returns the height change. -1/0
char AVLTree<T>::RecursiveDelete(const T& item, struct Node<T>* p,
                                 struct Node<T>** link) {
  CHECK(p != NULL);
  if (item > p->data) {
    char delta = RecursiveDelete(item, p->right, & p->right);
    p->balance += delta;
    if (p->balance == -2) {
      if ((*(p->left)).balance == 1)
        DoubleRightRotation(p);
      else
        SingleRightRotation(p);
      return -1;
    } else {
      return 0;
    }
  } else if (item < p->data) {
    char delta = RecursiveDelete(item, p->left, & p->left);
    p->balance -= delta;
    if (p->balance == 2) {
      if ((*p->right).balance == -1)
        DoubleLeftRotation(p);
      else
        SingleLeftRotation(p);
      return -1;
    } else {
      return 0;
    }
  } else if ((p->right == NULL) && (p->left == NULL)) {
    delete p;
    (*link) = NULL;
    return -1;
  } else if ((p->right == NULL) && (p->left != NULL)) {
    (*link) = p->left;
    delete p;
    return -1;
  } else if ((p->right != NULL) && (p->left == NULL)) {
    (*link) = p->right;
    delete p;
    return -1;
  } else {
    char delta = RecursiveRminDelete(p->right, &(p->data));
    p->balance += delta;
    if (p->balance == -2) {
      if ((*p->left).balance == 1)
        DoubleRightRotation(p);
      else
        SingleRightRotation(p);
      return -1;
    } else {
      return 0;
    }
  }
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
  inline bool operator< (const KeyValuePair &op2) const {
    return ( key_ < op2.key() );
  }
  inline bool operator> (const KeyValuePair &op2) const {
    return ( op2.key() < key_ );
  }
  inline bool operator!= (const KeyValuePair &op2) const {
    return ( (key_ < op2.key()) || (op2.key() < key_) );
  }
 private:
  TKey key_;
  TValue data_;
};

template <class Key, class Value>
class AVLMap : public AVLTree< KeyValuePair <Key, Value> > {};

#endif  // SANDBOX_AVL_H_
