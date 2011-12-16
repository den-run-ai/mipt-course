// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <stdio.h>

#include "sandbox/tsp.h"

namespace tsp {

Graph::Graph(double *cost_table, int num_vertices) { }

Graph::~Graph() { }

bool Graph::FindPath(Path *path) const { return false; }

}  // namespace tsp
