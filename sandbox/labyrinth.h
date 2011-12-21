// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LABYRINTH_H_
#define SANDBOX_LABYRINTH_H_

#include <utility>
#include <list>

#include "base/common.h"

typedef std::pair<int, int> LabyrinthPoint;

class Path : std::list<LabyrinthPoint> {
 public:
  Path() { }

  void append(int first_index, int second_index) {
    this->push_back(LabyrinthPoint(first_index, second_index));
  }

  bool Equals(const Path &path) {
    return std::equal(this->begin(), this->end(), path.begin());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Path);
};

class Labyrinth {
 public:
  // A labyrinth is described by a two-dimensional array.
  // 0 means you can go there.
  // 1 means you can't go there.
  // The first index numbers array rows from top to down starting from 0.
  // The second index numbers array columns from left to right starting from 0.
  // Please note the order of height and width arguments.
  Labyrinth(int *field, int height, int width);

  ~Labyrinth();

  bool FindPath(const LabyrinthPoint &start_point,
                const LabyrinthPoint &end_point,
                Path *found_path) const;

 private:
  int *field_;
  int height_;
  int width_;

  DISALLOW_COPY_AND_ASSIGN(Labyrinth);
};

#endif  // SANDBOX_LABYRINTH_H_
