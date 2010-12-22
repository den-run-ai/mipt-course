// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/* Here should be implemented a graph search algorithm that solves the single-
   source shortest path problem for a graph with nonnegative edge path costs,
   producing a shortest path tree
 */

#ifndef SANDBOX_DIJKSTRA_ALGORITHM_H_
#define SANDBOX_DIJKSTRA_ALGORITHM_H_

#include <vector>

#include "base/common.h"

class Edge {
 public:
  Edge();
  Edge(int head, int tail, double len) {
    CHECK(len >= 0.0);
    CHECK(head != tail);
    head_ = head;
    tail_ = tail;
    length_ = len;
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
  int head() {
    return head_;
  }
  int tail() {
    return tail_;
  }

 private:
  double length_;
  int head_, tail_;
};

// This class represents an unoriented graph.
class Graph {
 public:
  Graph();
  ~Graph();

  void InsertVertices(const std::vector<int> &vertices);
  void InsertEdges(const std::vector<Edge> &edges);

  std::vector<int> GetVertices() {
    return vertices_;
  }
  std::vector<Edge> GetEdges() {
    return edges_;
  }

  // On return, *path_length will store the length of the shortest path from
  // src to dst.
  std::vector<int> FindShortestPath(int src, int dst, double *path_length);

 private:
  std::vector<int> vertices_;
  std::vector<Edge> edges_;

  DISALLOW_COPY_AND_ASSIGN(Graph);
};

#endif  // SANDBOX_DIJKSTRA_ALGORITHM_H_
