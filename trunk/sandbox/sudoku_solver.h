// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_SUDOKU_SOLVER_H_
#define SANDBOX_SUDOKU_SOLVER_H_

#include <string>
#include <vector>

#include "base/common.h"

struct Sudoku {
  byte cells[9][9];

  std::string ToString() const {
    std::string ret = "  {\n";
    for (int r = 0; r < 9; r++) {
      ret += "    {";
      for (int c = 0; c < 9; c++) {
        if (c != 0)
          ret += ", ";
        ret += ('0' + cells[r][c]);
      }
      ret += "},\n";
    }
    ret += "  }\n";
    return ret;
  }

  // TODO(timurrrr): think of better method/param names.
  // E.g. Check(byte flags = ROWS|COLUMNS|BLOCKS|COMPLETENESS)
  bool CheckCorrectness(bool check_solution) const {
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        CHECK_LE(cells[r][c], 9);
        if (check_solution && cells[r][c] == 0)
          return false;
      }
    }

    for (int r = 0; r < 9; r++) {
      char seen[10] = {};  // we need seen[9]
      for (int c = 0; c < 9; c++) {
        if (cells[r][c] && seen[cells[r][c]]++ >= 1)
          return false;
      }
    }

    // TODO(timurrrr): avoid code duplication?
    // Use strides?
    for (int c = 0; c < 9; c++) {
      char seen[10] = {};  // we need seen[9]
      for (int r = 0; r < 9; r++) {
        if (cells[r][c] && seen[cells[r][c]]++ >= 1)
          return false;
      }
    }

    // ... or smarter strides?..
    for (int bx = 0; bx < 9; bx += 3) {
      for (int by = 0; by < 9; by += 3) {
        char seen[10] = {};  // we need seen[9]
        for (int c = bx; c < bx + 3; c++) {
          for (int r = by; r < by + 3; r++) {
            if (cells[r][c] && seen[cells[r][c]]++ >= 1)
              return false;
          }
        }
      }
    }

    return true;
  }

  bool IsEqual(const Sudoku &s2) const {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (cells[i][j] != s2.cells[i][j])
          return false;
      }
    }
    return true;
  }
};

class SudokuSolver {
 public:
  // Expects solutions to be empty.
  static bool Solve(const Sudoku &task, std::vector<Sudoku>* solutions,
                    int max_solutions);
};

#endif  // SANDBOX_SUDOKU_SOLVER_H_
