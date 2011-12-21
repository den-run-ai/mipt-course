// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"
#include "sandbox/labyrinth.h"

TEST(LabyrinthSearchTests, FindPathIn_1x1) {
  int field = 0;
  Cell start_cell(0, 0), end_cell(0, 0);

  Labyrinth lab(&field, 1, 1);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path;
  correct_path.append(0, 0);

  ASSERT_TRUE(found_path == correct_path);
}

TEST(LabyrinthSearchTests, FindPathIn_2x2) {
  int field[2][2] = {
    {0, 0},
    {1, 0}
  };
  Cell start_cell(1, 0), end_cell(1, 1);

  Labyrinth lab(&field[0][0], 2, 2);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path;
  correct_path.append(1, 0);
  correct_path.append(1, 1);

  ASSERT_TRUE(found_path == correct_path);
}

TEST(LabyrinthSearchTests, FindPathIn_3x3) {
  int field[3][3] = {
    {1, 0, 1},
    {1, 0, 0},
    {1, 0, 1}
  };
  Cell start_cell(1, 0), end_cell(2, 1);

  Labyrinth lab(&field[0][0], 3, 3);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path;
  correct_path.append(1, 0);
  correct_path.append(1, 1);
  correct_path.append(2, 1);

  ASSERT_TRUE(found_path == correct_path);
}

TEST(LabyrinthSearchTests, FindPathInDefiniteLab) {
  int field[4][5] = {
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0},
    {1, 0, 1, 1, 1}
  };
  Cell start_cell(1, 3), end_cell(4, 2);

  Labyrinth lab(&field[0][0], 5, 4);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path;
  correct_path.append(1, 3);
  correct_path.append(1, 2);
  correct_path.append(1, 1);
  correct_path.append(2, 1);
  correct_path.append(3, 1);
  correct_path.append(3, 2);
  correct_path.append(4, 2);

  ASSERT_TRUE(found_path == correct_path);
}

TEST(LabyrinthSearchTests, FindPathInLabWithCycle) {
  int field[3][5] = {
    {1, 0, 0, 0, 0},
    {1, 0, 1, 0, 1},
    {0, 0, 0, 0, 1},
  };
  Cell start_cell(0, 2), end_cell(4, 0);

  Labyrinth lab(&field[0][0], 5, 3);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path_1;
  correct_path_1.append(0, 2);
  correct_path_1.append(1, 2);
  correct_path_1.append(1, 1);
  correct_path_1.append(1, 0);
  correct_path_1.append(2, 0);
  correct_path_1.append(3, 0);
  correct_path_1.append(4, 0);

  Path correct_path_2;
  correct_path_2.append(0, 2);
  correct_path_2.append(1, 2);
  correct_path_2.append(2, 2);
  correct_path_2.append(3, 2);
  correct_path_2.append(3, 1);
  correct_path_2.append(3, 0);
  correct_path_2.append(4, 0);

  bool equals_path_1 = found_path == correct_path_1;
  bool equals_path_2 = found_path == correct_path_2;

  // One of equals_path_1 and equals_path_2 should be true, another false.
  ASSERT_NE(equals_path_1, equals_path_2);
}

TEST(LabyrinthSearchTests, FindPathIn_4x1) {
  int field[1][4] = {
    {0, 0, 0, 0}
  };
  Cell start_cell(0, 0), end_cell(3, 0);

  Labyrinth lab(&field[0][0], 4, 1);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path;
  correct_path.append(0, 0);
  correct_path.append(1, 0);
  correct_path.append(2, 0);
  correct_path.append(3, 0);

  ASSERT_TRUE(found_path == correct_path);
}

TEST(LabyrinthSearchTests, FindPathIn_1x4) {
  int field[4][1] = {
    {0},
    {0},
    {0},
    {0}
  };
  Cell start_cell(0, 0), end_cell(0, 3);

  Labyrinth lab(&field[0][0], 1, 4);
  Path found_path;
  ASSERT_TRUE(lab.FindPath(start_cell, end_cell, &found_path));

  Path correct_path;
  correct_path.append(0, 0);
  correct_path.append(0, 1);
  correct_path.append(0, 2);
  correct_path.append(0, 3);

  ASSERT_TRUE(found_path == correct_path);
}

TEST(LabyrinthSearchTests, LabWithoutPath) {
  int field[3][3] = {
    {1, 0, 1},
    {1, 1, 0},
    {1, 0, 1}
  };
  Cell start_cell(1, 0), end_cell(2, 1);

  Labyrinth lab(&field[0][0], 3, 3);
  Path found_path;
  ASSERT_FALSE(lab.FindPath(start_cell, end_cell, &found_path));
}

TEST(LabyrinthSearchTests, IncorrectLab) {
  int field[2][2] = {
    {1, 0},
    {1, 1}
  };
  Cell start_cell_1(0, 0), end_cell_1(1, 0);
  Cell start_cell_2(1, 0), end_cell_2(0, 0);
  Cell start_cell_3(0, 0), end_cell_3(1, 1);

  Labyrinth lab(&field[0][0], 2, 2);

  Path found_path;
  ASSERT_FALSE(lab.FindPath(start_cell_1, end_cell_1, &found_path));
  ASSERT_FALSE(lab.FindPath(start_cell_2, end_cell_2, &found_path));
  ASSERT_FALSE(lab.FindPath(start_cell_3, end_cell_3, &found_path));
}
