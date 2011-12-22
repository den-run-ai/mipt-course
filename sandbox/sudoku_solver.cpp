// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/sudoku_solver.h"

#include <set>
#include <vector>

using std::set;

void FindTrivialCells(const Sudoku& task, Sudoku* result) {
  CHECK(task.CheckCorrectness(false));
  if (task.CheckCorrectness(true))
    return;  // Nothing to do.

  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      result->cells[c][r] = task.cells[c][r];
    }
  }

  char all_digits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  set<char> digits(all_digits, all_digits+9);

  do {
    bool advanced_further = false;

    for (int r = 0; r < 9; r++) {
      set<char> to_find = digits;
      set<int> empty_indices;
      for (int c = 0; c < 9; c++) {
        if (result->cells[r][c] == 0)
          empty_indices.insert(c);
        else
          to_find.erase(result->cells[r][c]);
      }

      if (empty_indices.size() == 1) {
        CHECK_EQ(1, to_find.size());
        result->cells[r][*empty_indices.begin()] = *to_find.begin();
        // We haven't checked for blocks before... ok, check now.
        // TODO(timurrrr): make a code that doesn't generate incorrect blocks.
        if (!result->CheckCorrectness(false))
          result->cells[r][*empty_indices.begin()] = 0;
        else
          advanced_further = true;
      }
    }

    for (int c = 0; c < 9; c++) {
      set<char> to_find = digits;
      set<int> empty_indices;
      for (int r = 0; r < 9; r++) {
        if (result->cells[r][c] == 0)
          empty_indices.insert(r);
        else
          to_find.erase(result->cells[r][c]);
      }

      if (empty_indices.size() == 1) {
        CHECK_EQ(1, to_find.size());
        result->cells[*empty_indices.begin()][c] = *to_find.begin();
        // We haven't checked for blocks before... ok, check now.
        // TODO(timurrrr): make a code that doesn't generate incorrect blocks.
        if (!result->CheckCorrectness(false))
          result->cells[*empty_indices.begin()][c] = 0;
        else
          advanced_further = true;
      }
    }

    // TODO(timurrrr): make a code that's smart enough to fill blocks with just
    // one empty cell.

    if (!advanced_further)
      return;
  } while (true);
}

bool SudokuSolver::Solve(const Sudoku &task,
                         std::vector<Sudoku>* solutions,
                         int max_solutions) {
  Sudoku trivial;
  FindTrivialCells(task, &trivial);
  if (trivial.CheckCorrectness(true)) {
    solutions->push_back(trivial);
    return true;
  }

  int zero_id = -1;
  // TODO(timurrrr): avoid checking the cells that are definitely nonzero due to
  // the previous levels of recursion
  for (int i = 0; i < 9*9; i++) {
    if (trivial.cells[i/9][i%9] == 0) {
      zero_id = i;
      break;
    }
  }
  CHECK_NE(-1, zero_id);

  bool found_any = false;
  for (int t = 1; t <= 9; t++) {
    trivial.cells[zero_id/9][zero_id%9] = t;
    if (!trivial.CheckCorrectness(false))
      continue;  // We've created an incorrect Sudoku, never mind.
    found_any |= Solve(trivial, solutions, max_solutions);
    if (solutions->size() >= (unsigned)max_solutions)
      return true;
  }

  return found_any;
}
