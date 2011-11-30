// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

struct Sudoku {
  int field[9][9];

  const bool IsEqual(const Sudoku &s2) {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (field[i][j] != s2.field[i][j])
          return false;
      }
    }
    return true;
  }
};

Sudoku Solve(const Sudoku&) {
  Sudoku object = {
    {
     {7, 4, 3, 5, 9, 8, 2, 1, 6},
     {2, 9, 5, 6, 1, 7, 8, 3, 4},
     {6, 1, 8, 4, 2, 3, 7, 9, 5},
     {5, 8, 9, 3, 4, 6, 1, 2, 7},
     {1, 7, 6, 8, 5, 2, 9, 4, 3},
     {4, 3, 2, 1, 7, 9, 6, 5, 8},
     {8, 5, 7, 2, 3, 1, 4, 6, 9},
     {3, 6, 1, 9, 8, 4, 5, 7, 2},
     {9, 2, 4, 7, 6, 5, 3, 8, 1}
    }
  };
  return object;
}

TEST(SudokuSolveTest, Solve) {
  Sudoku start = {
    {
      {7, 0, 0, 0, 0, 0, 0, 1, 0},
      {2, 9, 0, 0, 1, 0, 0, 0, 4},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 7},
      {1, 7, 0, 0, 5, 0, 0, 0, 3},
      {0, 3, 2, 1, 0, 0, 0, 5, 0},
      {0, 0, 7, 0, 0, 1, 0, 0, 0},
      {0, 6, 1, 9, 0, 0, 5, 7, 0},
      {9, 2, 4, 0, 0, 0, 0, 8, 0}
    }
  };
  Sudoku expected_solution = {
    {
     {7, 4, 3, 5, 9, 8, 2, 1, 6},
     {2, 9, 5, 6, 1, 7, 8, 3, 4},
     {6, 1, 8, 4, 2, 3, 7, 9, 5},
     {5, 8, 9, 3, 4, 6, 1, 2, 7},
     {1, 7, 6, 8, 5, 2, 9, 4, 3},
     {4, 3, 2, 1, 7, 9, 6, 5, 8},
     {8, 5, 7, 2, 3, 1, 4, 6, 9},
     {3, 6, 1, 9, 8, 4, 5, 7, 2},
     {9, 2, 4, 7, 6, 5, 3, 8, 1}
    }
  };
  Sudoku actual_solution = Solve(start);
  ASSERT_TRUE(expected_solution.IsEqual(actual_solution));
}
