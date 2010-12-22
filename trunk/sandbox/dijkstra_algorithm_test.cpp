// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <vector>

#include "base/common.h"

#include "sandbox/dijkstra_algorithm.h"

#include "third_party/googletest/include/gtest/gtest.h"

const int TEST_VERTEX_INDEX = 1;

TEST(GraphTest, InsertVerticesTest) {
  // adding one vertex to the graph
  std::vector<int> vert_arr;
  vert_arr.push_back(TEST_VERTEX_INDEX);

  Graph tmp_gr;
  tmp_gr.InsertVertices(vert_arr);

  std::vector<int> vertices = tmp_gr.GetVertices();
  ASSERT_EQ(vertices.size(), (size_t)1);
  EXPECT_EQ(vertices.front(), TEST_VERTEX_INDEX);
}

TEST(GraphTest, InsertEdgesTest) {
  // adding one edge to the graph
  Edge tmp_edge(TEST_VERTEX_INDEX, TEST_VERTEX_INDEX + 1, 0.0);
  EXPECT_EQ(tmp_edge.length(), 0.0);
  EXPECT_EQ(tmp_edge.head(), TEST_VERTEX_INDEX);
  EXPECT_EQ(tmp_edge.tail(), TEST_VERTEX_INDEX + 1);

  std::vector<Edge> edge_arr;
  edge_arr.push_back(tmp_edge);

  Graph tmp_graph;
  tmp_graph.InsertEdges(edge_arr);

  std::vector<Edge> edges = tmp_graph.GetEdges();
  ASSERT_EQ(edges.size(), (size_t)1);
  EXPECT_TRUE(edges.front().length() == 0.0);
}

TEST(GraphTest, FindZeroPathTest) {
  Graph tmp_graph;
  std::vector<int> vert_arr;
  vert_arr.push_back(TEST_VERTEX_INDEX);
  tmp_graph.InsertVertices(vert_arr);
  double len = -1.0;
  std::vector<int> path = tmp_graph.FindShortestPath(TEST_VERTEX_INDEX,
                                               TEST_VERTEX_INDEX,
                                               &len);
  EXPECT_EQ(len, 0.0);
  EXPECT_EQ(path.size(), (size_t)1);
}
