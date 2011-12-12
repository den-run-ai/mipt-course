// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"
#include "sandbox/labyrinth.h"

TEST(LabyrinthSearchTests, DISABLED_FindPathIn_1x1) {
  int field = 0;
  LabyrinthPoint start_point(0, 0), end_point(0, 0);

  Labyrinth lab(&field, 1, 1);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_point, end_point, &found_path));

  Path correct_path;
  correct_path.append(0, 0);

  ASSERT_TRUE(found_path.Equals(correct_path));
}

TEST(LabyrinthSearchTests, DISABLED_FindPathIn_2x2) {
  int field[2][2] = {
    {0, 0},
    {1, 0}
  };
  LabyrinthPoint start_point(0, 1), end_point(1, 1);

  Labyrinth lab(&field[0][0], 2, 2);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_point, end_point, &found_path));

  Path correct_path;
  correct_path.append(0, 1);
  correct_path.append(1, 1);

  ASSERT_TRUE(found_path.Equals(correct_path));
}

TEST(LabyrinthSearchTests, DISABLED_FindPathIn_3x3) {
  int field[3][3] = {
    {1, 0, 1},
    {1, 0, 0},
    {1, 0, 1}
  };
  LabyrinthPoint start_point(0, 1), end_point(1, 2);

  Labyrinth lab(&field[0][0], 3, 3);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_point, end_point, &found_path));

  Path correct_path;
  correct_path.append(0, 1);
  correct_path.append(1, 1);
  correct_path.append(1, 2);

  ASSERT_TRUE(found_path.Equals(correct_path));
}

TEST(LabyrinthSearchTests, DISABLED_FindPathInDefiniteLab) {
  int field[4][5] = {
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0},
    {1, 0, 1, 1, 1}
  };
  LabyrinthPoint start_point(3, 1), end_point(2, 4);

  Labyrinth lab(&field[0][0], 4, 5);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_point, end_point, &found_path));

  Path correct_path;
  correct_path.append(3, 1);
  correct_path.append(2, 1);
  correct_path.append(1, 1);
  correct_path.append(1, 2);
  correct_path.append(1, 3);
  correct_path.append(2, 3);
  correct_path.append(2, 4);

  ASSERT_TRUE(found_path.Equals(correct_path));
}

TEST(LabyrinthSearchTests, DISABLED_FindPathInLabWithCycle) {
  int field[3][5] = {
    {1, 0, 0, 0, 0},
    {1, 0, 1, 0, 1},
    {0, 0, 0, 0, 1},
  };
  LabyrinthPoint start_point(2, 0), end_point(0, 4);

  Labyrinth lab(&field[0][0], 3, 5);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_point, end_point, &found_path));

  Path correct_path_1;
  correct_path_1.append(2, 0);
  correct_path_1.append(2, 1);
  correct_path_1.append(1, 1);
  correct_path_1.append(0, 1);
  correct_path_1.append(0, 2);
  correct_path_1.append(0, 3);
  correct_path_1.append(0, 4);

  Path correct_path_2;
  correct_path_2.append(2, 0);
  correct_path_2.append(2, 1);
  correct_path_2.append(2, 2);
  correct_path_2.append(2, 3);
  correct_path_2.append(1, 3);
  correct_path_2.append(0, 3);
  correct_path_2.append(0, 4);

  bool equals_path_1 = found_path.Equals(correct_path_1);
  bool equals_path_2 = found_path.Equals(correct_path_2);

  // One of equals_path_1 and equals_path_2 should be true, another false.
  ASSERT_NE(equals_path_1, equals_path_2);
}
