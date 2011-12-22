// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/sudoku_solver.h"

#include <vector>

#include "gtest/gtest.h"

using std::vector;

// TODO(timurrrr): Tests for Sudoku::CheckCorrectness

TEST(SudokuSolverTests, RowsOnly) {
  // All these unknown numbers are trivial to find
  // just by looking at rows (or columns).
  Sudoku task = {
    {
      {0, 4, 3, 5, 9, 8, 2, 1, 6},
      {2, 0, 5, 6, 1, 7, 8, 3, 4},
      {6, 1, 0, 4, 2, 3, 7, 9, 5},
      {5, 8, 9, 0, 4, 6, 1, 2, 7},
      {1, 7, 6, 8, 0, 2, 9, 4, 3},
      {4, 3, 2, 1, 7, 0, 6, 5, 8},
      {8, 5, 7, 2, 3, 1, 0, 6, 9},
      {3, 6, 1, 9, 8, 4, 5, 0, 2},
      {9, 2, 4, 7, 6, 5, 3, 8, 0}
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

  vector<Sudoku> solutions;
  SudokuSolver::Solve(task, &solutions, 42);
  ASSERT_EQ(1u, solutions.size());
  ASSERT_TRUE(expected_solution.IsEqual(solutions[0]));
}

TEST(SudokuSolverTests, RowsAndColumnsAndBlocks) {
  // All these unknown numbers can be found
  // by looking at rows, columns and blocks.
  Sudoku task = {
    {
      {0, 4, 3, 5, 9, 8, 2, 1, 6},
      {2, 9, 5, 6, 1, 7, 8, 3, 4},
      {0, 1, 0, 4, 2, 3, 7, 9, 5},
      {5, 8, 9, 3, 4, 6, 1, 2, 7},
      {1, 7, 6, 8, 5, 2, 9, 4, 3},
      // TODO(timurrrr): remove +X once we handle blocks in O(1) too
      {4, 3, 2, 1, 7, 0 + 9, 0, 5, 8},
      {8, 5, 7, 2, 3, 0 + 1, 0 + 4, 6, 9},
      {3, 6, 1, 9, 8, 4, 5, 7, 2},
      {9, 2, 4, 7, 6, 5, 3, 8, 1}
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

  vector<Sudoku> solutions;
  SudokuSolver::Solve(task, &solutions, 42);
  ASSERT_EQ(1u, solutions.size());
  ASSERT_TRUE(expected_solution.IsEqual(solutions[0]));
}

TEST(SudokuSolverTests, TwoSolutions) {
  // Two solutions are possible.
  Sudoku task = {
    {
      {0, 0, 3, 4, 5, 6, 7, 8, 9},
      {4, 5, 6, 7, 8, 9, 1, 2, 3},
      {7, 8, 9, 1, 2, 3, 4, 5, 6},
      {0, 0, 4, 3, 9, 8, 5, 6, 7},
      {8, 6, 5, 2, 7, 1, 3, 9, 4},
      {9, 3, 7, 6, 4, 5, 8, 1, 2},
      {3, 4, 1, 8, 6, 2, 9, 7, 5},
      {5, 7, 2, 9, 1, 4, 6, 3, 8},
      {6, 9, 8, 5, 3, 7, 2, 4, 1}
    }
  };
  Sudoku expected_solution1 = {
    {
      {1, 2, 3, 4, 5, 6, 7, 8, 9},
      {4, 5, 6, 7, 8, 9, 1, 2, 3},
      {7, 8, 9, 1, 2, 3, 4, 5, 6},
      {2, 1, 4, 3, 9, 8, 5, 6, 7},
      {8, 6, 5, 2, 7, 1, 3, 9, 4},
      {9, 3, 7, 6, 4, 5, 8, 1, 2},
      {3, 4, 1, 8, 6, 2, 9, 7, 5},
      {5, 7, 2, 9, 1, 4, 6, 3, 8},
      {6, 9, 8, 5, 3, 7, 2, 4, 1},
    }
  };

  Sudoku expected_solution2 = {
    {
      {2, 1, 3, 4, 5, 6, 7, 8, 9},
      {4, 5, 6, 7, 8, 9, 1, 2, 3},
      {7, 8, 9, 1, 2, 3, 4, 5, 6},
      {1, 2, 4, 3, 9, 8, 5, 6, 7},
      {8, 6, 5, 2, 7, 1, 3, 9, 4},
      {9, 3, 7, 6, 4, 5, 8, 1, 2},
      {3, 4, 1, 8, 6, 2, 9, 7, 5},
      {5, 7, 2, 9, 1, 4, 6, 3, 8},
      {6, 9, 8, 5, 3, 7, 2, 4, 1},
    }
  };

  vector<Sudoku> solutions;
  SudokuSolver::Solve(task, &solutions, 3);
  ASSERT_EQ(2u, solutions.size());
  // TODO(timurrrr): the order is not guaranteed
  ASSERT_TRUE(expected_solution1.IsEqual(solutions[0]));
  ASSERT_TRUE(expected_solution2.IsEqual(solutions[1]));
}

TEST(SudokuSolverTests, NeedsSmartBlocksHandling) {
  // The Sudoku given below requires "smart" checking of rows and blocks.
  // If you simply put '8' instead of '0' on the second line, the top-right
  // block of the Sudoku will have two '8' cells which is wrong.
  Sudoku tricky = {
    {
      {7, 4, 3, 2, 6, 5, 8, 1, 9},
      {2, 9, 5, 3, 1, 7, 6, 0, 4},  // <-- here
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 7},
      {1, 7, 0, 0, 5, 0, 0, 0, 3},
      {0, 3, 2, 1, 0, 0, 0, 5, 0},
      {0, 0, 7, 0, 0, 1, 0, 0, 0},
      {0, 6, 1, 9, 0, 0, 5, 7, 0},
      {9, 2, 4, 0, 0, 0, 0, 8, 0},
    }
  };
  vector<Sudoku> solutions;
  SudokuSolver::Solve(tricky, &solutions, 1);
}

// DISABLED_ because it's too slow now. TODO(timurrrr): re-enabled once Solve is
// well optimized.
TEST(SudokuSolverTests, DISABLED_ManySolutionsStressTest) {
  // There are ~16000 solutions.
  Sudoku task = {
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
  Sudoku possible_solution = {
    {
      {7, 4, 3, 2, 6, 9, 8, 1, 5},
      {2, 9, 6, 5, 1, 8, 7, 3, 4},
      {5, 1, 8, 4, 7, 3, 2, 9, 6},
      {4, 8, 5, 3, 9, 2, 1, 6, 7},
      {1, 7, 9, 8, 5, 6, 4, 2, 3},
      {6, 3, 2, 1, 4, 7, 9, 5, 8},
      {8, 5, 7, 6, 2, 1, 3, 4, 9},
      {3, 6, 1, 9, 8, 4, 5, 7, 2},
      {9, 2, 4, 7, 3, 5, 6, 8, 1},
    }
  };

  vector<Sudoku> solutions;
  const size_t NUM_SOLUTIONS = 10;
  SudokuSolver::Solve(task, &solutions, NUM_SOLUTIONS);
  ASSERT_EQ(NUM_SOLUTIONS, solutions.size());

  bool found_possible = false;
  for (size_t i = 0; i < solutions.size(); i++) {
    ASSERT_TRUE(solutions[i].CheckCorrectness(true));
    found_possible |=  possible_solution.IsEqual(solutions[0]);
  }
  printf("The predefined solution is %sin the %d we've found\n",
         found_possible ? "" : "not ", static_cast<int>(NUM_SOLUTIONS));
}
