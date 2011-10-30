// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LIST_H_
#define SANDBOX_LIST_H_

#include "base/common.h"


/* 
 * Double-linked list
 * */
template <class T>
class List {
 public:
  List(void);
  ~List(void);

  void PushFront(const T &data);
  void PushBack(const T &data);
  size_t Size() {return size_;}
  void Clear();

  // TODO(svatoslav1): define an interator class instead of typedef.
  typedef void* iterator;
  iterator begin()  { return (iterator)begin_; }
  iterator end()    { return NULL; }
  iterator next(iterator node) {
    return (iterator) (reinterpret_cast<Node*>(node))->next_;
  }
  T getValue(iterator node) {return (reinterpret_cast<Node*>(node))->data_; }
  iterator Remove(iterator node);

 private:
  class Node {
   public:
    explicit Node(const T &data);

    T data_;
    Node *next_;
    Node *prev_;
  };

  Node *begin_;
  Node *end_;
  size_t size_;
};

template <class T>
List<T>::Node::Node(const T &input_data) {
  next_ = NULL;
  prev_ = NULL;
  data_ = input_data;
}

template <class T>
List<T>::List(void) {
  begin_ = NULL;
  end_ = NULL;
  size_ = 0;
}

template <class T>
List<T>::~List(void) {
  Clear();
}

template <class T>
void List<T>::PushFront(const T &input_data) {
  Node *new_node = new Node(input_data);

  if (size_) {
    new_node->next_ = begin_;
    new_node->prev_ = NULL;
    begin_->prev_ = new_node;
    begin_ = new_node;
  } else {
    end_ = new_node;
    begin_ = new_node;
    new_node->next_ = NULL;
    new_node->prev_ = NULL;
  }
  new_node->data_ = input_data;
  size_++;
}

template <class T>
void List<T>::PushBack(const T &input_data) {
  Node *new_node = new Node(input_data);

  if (size_) {
    new_node->next_ = NULL;
    new_node->prev_ = end_;
    end_->next_ = new_node;
    end_ = new_node;
  } else {
    end_ = new_node;
    begin_ = new_node;
    new_node->next_ = NULL;
    new_node->prev_ = NULL;
  }
  new_node->data_ = input_data;
  size_++;
}

template <typename T>
typename List<T>::iterator List<T>::Remove(iterator it) {
  Node *node = reinterpret_cast<Node*>(it);
  // TODO(svatoslav1): add DCHECKs to ensure "it" belongs to this list.

  if (node != begin_)
    node->prev_->next_ = node->next_;
  else
    begin_ = node->next_;
  if (node != end_)
    node->next_->prev_ =  node->prev_;
  else
    end_ = node->prev_;

  Node *nextnode = node->next_;
  delete node;
  size_--;
  return (iterator)nextnode;
}

template <class T>
void List<T>::Clear() {
  Node *nextnode;
  for (Node *node = begin_; node != NULL; node = nextnode) {
    nextnode = node->next_;
    delete node;
    node = nextnode;
  }
  begin_ = end_ = NULL;
  size_ = 0;
}

#endif  // SANDBOX_LIST_H_
