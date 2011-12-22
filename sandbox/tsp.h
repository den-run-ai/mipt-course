// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_TSP_H_
#define SANDBOX_TSP_H_

#include "base/common.h"

namespace tsp {

class Path {
 public:
  explicit Path(int size);
  ~Path();

  void SetVertex(int index, int value);
  int GetVertex(int index) const;
  int length() const;

  // If vertex appears just once in the path
  bool IsHamiltonCycle() const;
  double cost() const;
  bool Equals(const Path &path) const;

 private:
  int *path_;
  int size_;
  DISALLOW_COPY_AND_ASSIGN(Path);
};

class Graph {
 public:
  // The cost table is an array N*N, N == num_vertices,
  // -1 if the edge is not present.
  Graph(double *cost_table, int num_vertices);
  ~Graph();

  bool FindPath(Path *path) const;

 private:
  static const int kInf = -1;

  double *table_;
  int size_;
  int vertexes_;
  DISALLOW_COPY_AND_ASSIGN(Graph);
};

}  // namespace tsp

#endif  // SANDBOX_TSP_H_
