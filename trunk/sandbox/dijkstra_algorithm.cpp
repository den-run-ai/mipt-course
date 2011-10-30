// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/* Here should be implemented a graph search algorithm that solves the single-
   source shortest path problem for a graph with nonnegative edge path costs, 
   producing a shortest path tree
 */

#include <vector>

#include "sandbox/dijkstra_algorithm.h"

#include "base/common.h"

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::InsertVertices(const std::vector<int> &vertices) {
  for (size_t i = 0; i < vertices.size(); ++i)
    vertices_.push_back(vertices[i]);
}

void Graph::InsertEdges(const std::vector<Edge> &edges) {
  for (size_t i = 0; i < edges.size(); ++i)
    edges_.push_back(edges[i]);
}

std::vector<int> Graph::FindShortestPath(int src,
                                         int dst,
                                         double *path_length) {
    std::vector<int> result;
    // in case of zero path
    if (src == dst) {
      result.push_back(src);
      *path_length = 0.0;
      return result;
    }
    // TODO(dmitryhd): write dijkstra algorithm here.
    *path_length = -1.0;
    return result;
}

Edge::Edge() {
}

Edge::~Edge() {
}

