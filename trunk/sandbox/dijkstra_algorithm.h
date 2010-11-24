// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/* Here should be implemented a graph search algorithm that solves the single-
   source shortest path problem for a graph with nonnegative edge path costs,
   producing a shortest path tree
 */

#ifndef SANDBOX_DIJKSTRA_ALGORITHM_H_
#define SANDBOX_DIJKSTRA_ALGORITHM_H_

#include <list>
#include <vector>

#include "base/common.h"

class Vertex;
class Edge;
class Graph;

class Graph {
 public:
  Graph();
  ~Graph();
  void InsertVertices(const std::vector<Vertex> &vertices) {
  }
  void InsertEdges(const std::vector<Edge> &edges) {
  }
  std::vector<Vertex> FindShortestPath(const Vertex &src,
                                       const Vertex &dst,
                                       double* path_length);
  std::list<Vertex*> GetVertices() {
    return vertices_;
  }
  std::list<Edge*> GetEdges() {
    return edges_;
  }

 private:
  std::list<Vertex*> vertices_;
  std::list<Edge*> edges_;

  DISALLOW_COPY_AND_ASSIGN(Graph);
};

class Vertex {
 public:
  Vertex();
  explicit Vertex(int xid) {
    id_ = xid;
  }
  ~Vertex();
  int operator==(const Vertex &arg) const {
    return 0;
  }
  int operator<(const Vertex &arg) const {
    return 0;
  }
  unsigned int id() const {
    return id_;
  }

 private:
  unsigned int id_;
};

class Edge {
 public:
  Edge();
  Edge(Vertex *head, Vertex *tail) {
    head_ = head;
    tail_ = tail;
  }
  ~Edge();
  int operator==(const Edge &arg) const {
    return 0;
  }
  int operator<(const Edge &arg) const {
    return 0;
  }
  double length() {
    return length_;
  }
  Vertex *head() {
    return head_;
  }
  Vertex *tail() {
    return tail_;
  }

 private:
  double length_;
  Vertex *head_, *tail_;
};

#endif  // SANDBOX_DIJKSTRA_ALGORITHM_H_
