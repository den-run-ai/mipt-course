// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

#include "sandbox/tsp.h"

namespace tsp {

TEST(TSPGeneralTests, DISABLED_FindPath) {
  double input[5][5] = {
     {-1, 2, 3, 4, 5},
     {4, -1, 6, 7, 8},
     {7, 8, -1, 10, 11},
     {5, 6, 3, -1, 3},
     {4, 6, 3, 7, -1}
  };

  Graph graph(&input[0][0], 5);
  Path found_path(5);

  ASSERT_TRUE(graph.FindPath(&found_path));

  ASSERT_TRUE(found_path.IsHamiltonCycle());

  ASSERT_EQ(25, found_path.cost());

  Path expected_path(5);
  expected_path.SetVertex(0, 4);
  expected_path.SetVertex(1, 5);
  expected_path.SetVertex(2, 3);
  expected_path.SetVertex(3, 1);
  expected_path.SetVertex(4, 2);

  ASSERT_TRUE(expected_path.Equals(found_path));
}

}  // namespace tsp
