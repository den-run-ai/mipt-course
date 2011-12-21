// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/labyrinth.h"

#include <algorithm>
#include <vector>
#include <map>

void Labyrinth::GetAdjacentCells(const Cell &cell,
                                 std::vector<Cell> *adjacent_cells) const {
  Cell up_cell = Cell(cell.x, cell.y - 1);
  Cell right_cell = Cell(cell.x + 1, cell.y);
  Cell down_cell = Cell(cell.x, cell.y + 1);
  Cell left_cell = Cell(cell.x - 1, cell.y);

  adjacent_cells->clear();

  if (cell.y != 0 && IsEmpty(up_cell)) {
    adjacent_cells->push_back(up_cell);
  }
  if (cell.x != this->width() - 1 && IsEmpty(right_cell)) {
    adjacent_cells->push_back(right_cell);
  }
  if (cell.y != this->height() - 1 && IsEmpty(down_cell)) {
    adjacent_cells->push_back(down_cell);
  }
  if (cell.x != 0 && IsEmpty(left_cell)) {
    adjacent_cells->push_back(left_cell);
  }
}

bool Labyrinth::FindPath(const Cell &start_cell,
                         const Cell &end_cell,
                         Path *found_path) const {
  // For path search the wave algorithm (Lee's algorithm) is used.
  // See http://en.wikipedia.org/wiki/Lee_algorithm

  if (!IsEmpty(start_cell) || !IsEmpty(end_cell)) {
    return false;
  }

  if (start_cell == end_cell) {
    found_path->append(start_cell);
    return true;
  }

  std::map<Cell, int> visited_cells;
  std::vector<Cell> current_front;
  int front_value = 1;

  visited_cells[start_cell] = front_value;
  GetAdjacentCells(start_cell, &current_front);

  bool reached_end = false;

  std::vector<Cell> next_front, temp;
  while (!reached_end) {
    next_front.clear();
    std::vector<Cell>::iterator it;
    for (it = current_front.begin(); it != current_front.end(); ++it) {
      if (visited_cells[*it] != 0) {
        continue;
      }
      visited_cells[*it] = front_value + 1;
      GetAdjacentCells(*it, &temp);
      next_front.insert(next_front.end(), temp.begin(), temp.end());
    }

    front_value++;

    if (visited_cells[end_cell] != 0) {
      reached_end = true;
    }

    if (current_front.empty()) {
      return false;
    }

    swap(current_front, next_front);
  }

  // Backtraces a path from the end_cell to the start_cell.
  Cell current_cell = end_cell;
  found_path->append(current_cell);
  while (front_value != 1) {
    GetAdjacentCells(current_cell, &current_front);
    std::vector<Cell>::iterator it;
    for (it = current_front.begin(); it != current_front.end(); ++it) {
      if (visited_cells[*it] == front_value - 1) {
        found_path->append(*it);
        current_cell = *it;
        front_value--;
        break;
      }
    }
    CHECK(it != current_front.end());
  }
  found_path->reverse();
  return true;
}
