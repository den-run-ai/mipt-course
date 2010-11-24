// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
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

std::vector<Vertex> Graph::FindShortestPath(const Vertex &src,
                                            const Vertex &dst,
                                            double* path_length) {
    std::vector<Vertex> tmp;
    *path_length = -1.0;
    return tmp;
}

Edge::Edge() {
}

Edge::~Edge() {
}

Vertex::Vertex() {
}

Vertex::~Vertex() {
}

