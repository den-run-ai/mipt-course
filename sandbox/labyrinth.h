// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LABYRINTH_H_
#define SANDBOX_LABYRINTH_H_

#include <string.h>

#include <utility>
#include <vector>
#include <list>
#include <map>

#include "base/common.h"

struct Cell {
  Cell(int x_, int y_): x(x_), y(y_) { }

  bool operator== (const Cell &cell) const {
    return (this->x == cell.x && this->y == cell.y);
  }

  bool operator< (const Cell &cell) const {
    if (this->x < cell.x) {
      return true;
    } else if (this->x > cell.x) {
      return false;
    } else {
      return this->y < cell.y;
    }
  }

  int x, y;
};

class Path : public std::list<Cell> {
 public:
  Path() { }

  bool operator== (const Path &path) const {
    return std::equal(this->begin(), this->end(), path.begin());
  }

  void append(int x, int y) {
    this->push_back(Cell(x, y));
  }

  void append(const Cell &cell) {
    this->push_back(cell);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Path);
};

class Labyrinth {
 public:
  /* A labyrinth is described by a two-dimensional array.
     0 means you can go there.
     1 means you can't go there.
   */
  Labyrinth(int *field, int width, int height) {
    field_ = new int[width * height];
    memcpy(field_, field, sizeof(field_[0]) * width * height);
    width_ = width;
    height_ = height;
  }

  ~Labyrinth() {
    delete [] field_;
  }

  bool FindPath(const Cell &start_cell,
                const Cell &end_cell,
                Path *found_path) const;

  int width() const { return width_; }
  int height() const { return height_; }

 private:
  int *field_;
  int height_;
  int width_;

  void GetAdjacentCells(const Cell &cell,
                        std::vector<Cell> *adjacent_cells) const;

  bool IsEmpty(const Cell &cell) const {
    CHECK_GE(cell.x, 0);
    CHECK_LT(cell.x, width_);
    CHECK_GE(cell.y, 0);
    CHECK_LT(cell.y, height_);
    return *(field_ + cell.x + cell.y * width_) == 0;
  }

  DISALLOW_COPY_AND_ASSIGN(Labyrinth);
};

#endif  // SANDBOX_LABYRINTH_H_
