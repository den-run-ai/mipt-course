// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <vector>
#include <list>

#include "base/common.h"

#include "sandbox/dijkstra_algorithm.h"

#include "third_party/googletest/include/gtest/gtest.h"

TEST(GraphTest, DISABLED_InsertVerticesTest) {
  // adding one vertex to the graph
  Vertex tmp_vert(1);
  EXPECT_EQ(tmp_vert.id(), (unsigned int)1);

  std::vector<Vertex> vert_arr;
  vert_arr.push_back(tmp_vert);

  Graph tmp_gr;
  tmp_gr.InsertVertices(vert_arr);

  std::list<Vertex *> vertices = tmp_gr.GetVertices();
  ASSERT_EQ(vertices.size(), (size_t)1);
  EXPECT_TRUE(vertices.front() != NULL);
}

TEST(GraphTest, DISABLED_InsertEdgesTest) {
  // adding one edge to the graph
  Vertex tmp_vert(1);
  Edge tmp_edge(&tmp_vert, &tmp_vert);
  EXPECT_EQ(tmp_edge.length(), 0.0);
  EXPECT_EQ(tmp_edge.head(), tmp_edge.tail());

  std::vector<Edge> edge_arr;
  edge_arr.push_back(tmp_edge);

  Graph tmp_graph;
  tmp_graph.InsertEdges(edge_arr);

  std::list<Edge *> edges = tmp_graph.GetEdges();
  ASSERT_EQ(edges.size(), (size_t)1);
  EXPECT_TRUE(edges.front() != NULL);
}

TEST(GraphTest, DISABLED_FindZeroPathTest) {
  Graph tmp;
  std::vector<Vertex> vert_arr;
  Vertex a(1);
  vert_arr.push_back(a);
  tmp.InsertVertices(vert_arr);
  double len = -1.0;
  std::vector<Vertex> path = tmp.FindShortestPath(a, a, &len);
  EXPECT_EQ(path.size(), (size_t)1);
  EXPECT_EQ(len, 0.0);
}
