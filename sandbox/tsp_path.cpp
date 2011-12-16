// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <stdio.h>

#include "sandbox/tsp.h"

namespace tsp {

Path::Path(int size) {}

Path::~Path() {}

void Path::SetVertex(int index, int value) {}

int Path::GetVertex(int index) const {
  return 0;
}

int Path::length() const {
  return 5;
}

bool Path::IsHamiltonCycle() const {
  return false;
}

double Path::cost() const {
  return 25;
}

bool Path::Equals(const Path &path) const {
  return true;
}

}  // namespace tsp
