// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
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

  Graph graph;
  graph.InsertVertices(vert_arr);

  std::vector<int> vertices = graph.GetVertices();
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

  Graph graph;
  graph.InsertEdges(edge_arr);

  std::vector<Edge> edges = graph.GetEdges();
  ASSERT_EQ(edges.size(), (size_t)1);
  EXPECT_TRUE(edges.front().length() == 0.0);
}

TEST(GraphTest, FindZeroPathTest) {
  Graph graph;
  std::vector<int> vert_arr;
  vert_arr.push_back(TEST_VERTEX_INDEX);
  graph.InsertVertices(vert_arr);
  double len = -1.0;
  std::vector<int> path = graph.FindShortestPath(TEST_VERTEX_INDEX,
                                               TEST_VERTEX_INDEX,
                                               &len);
  EXPECT_EQ(len, 0.0);
  EXPECT_EQ(path.size(), (size_t)1);
}

TEST(GraphTest, DISABLED_FindRealPathTest) {
  Graph graph;
  std::vector<int> vert_arr;
  for (int i = 0; i < 6; i++ )
    vert_arr.push_back(i);
  graph.InsertVertices(vert_arr);

  // unoriented graph.
  std::vector<Edge> edge_arr;
  edge_arr.push_back(Edge(0, 1, 7.0));
  edge_arr.push_back(Edge(0, 2, 9.0));
  edge_arr.push_back(Edge(0, 5, 14.0));
  edge_arr.push_back(Edge(1, 2, 10.0));
  edge_arr.push_back(Edge(1, 3, 15.0));
  edge_arr.push_back(Edge(2, 3, 11.0));
  edge_arr.push_back(Edge(2, 5, 2.0));
  edge_arr.push_back(Edge(3, 4, 6.0));
  edge_arr.push_back(Edge(4, 5, 9.0));
  graph.InsertEdges(edge_arr);

  double len = -1;
  std::vector<int> path;
  // first path: from 0 to 1.
  path = graph.FindShortestPath(0, 1, &len);
  ASSERT_EQ(path.size(), (size_t)2);
  EXPECT_EQ(path[0], 0);
  EXPECT_EQ(path[1], 1);
  EXPECT_EQ(len, 7.0);

  // path: from 0 to 2.
  len = -1;
  path = graph.FindShortestPath(0, 2, &len);
  ASSERT_EQ(path.size(), (size_t)2);
  EXPECT_EQ(path[0], 0);
  EXPECT_EQ(path[1], 2);
  EXPECT_EQ(len, 9.0);

  // path: from 0 to 3.
  len = -1;
  path = graph.FindShortestPath(0, 3, &len);
  ASSERT_EQ(path.size(), (size_t)3);
  EXPECT_EQ(path[0], 0);
  EXPECT_EQ(path[1], 2);
  EXPECT_EQ(path[2], 3);
  EXPECT_EQ(len, 20.0);

  // path: from 0 to 4.
  len = -1;
  path = graph.FindShortestPath(0, 4, &len);
  ASSERT_EQ(path.size(), (size_t)4);
  EXPECT_EQ(path[0], 0);
  EXPECT_EQ(path[1], 2);
  EXPECT_EQ(path[2], 5);
  EXPECT_EQ(path[3], 4);
  EXPECT_EQ(len, 20.0);

  // path: from 0 to 5.
  len = -1;
  path = graph.FindShortestPath(0, 5, &len);
  ASSERT_EQ(path.size(), (size_t)3);
  EXPECT_EQ(path[0], 0);
  EXPECT_EQ(path[1], 2);
  EXPECT_EQ(path[2], 5);
  EXPECT_EQ(len, 11.0);
}

TEST(GraphTest, DISABLED_FindPathBetweenNonexistentVerticesDeathTest) {
  Graph graph;
  std::vector<int> vert_arr;
  for (int i = 0; i < 2; i++ )
    vert_arr.push_back(i);
  graph.InsertVertices(vert_arr);

  std::vector<Edge> edge_arr;
  edge_arr.push_back(Edge(0, 1, 7.0));
  graph.InsertEdges(edge_arr);

  double len = -1.0;
  std::vector<int> path;

  // this vertices didn't exist.
  ASSERT_DEATH(graph.FindShortestPath(12, 31, &len), "CHECK failed");
}

TEST(GraphTest, DISABLED_FindFalsePathTest) {
  Graph graph;
  std::vector<int> vert_arr;
  for (int i = 0; i < 4; i++ )
    vert_arr.push_back(i);
  graph.InsertVertices(vert_arr);

  std::vector<Edge> edge_arr;
  edge_arr.push_back(Edge(0, 1, 7.0));
  edge_arr.push_back(Edge(2, 3, 1.0));
  graph.InsertEdges(edge_arr);

  double len = -1.0;
  std::vector<int> path;

  // unconnected components.
  path = graph.FindShortestPath(2, 0, &len);
  EXPECT_EQ(path.size(), (size_t)0);
}
