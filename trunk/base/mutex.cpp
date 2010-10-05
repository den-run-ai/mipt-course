// Copyright (c) 2010 Timur Iskhodzhanov. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/mutex.h"

namespace threading {

Mutex::Mutex() {
  CHECK(pthread_mutex_init(&mutex_, NULL) == 0);
}

Mutex::~Mutex() {
  CHECK(pthread_mutex_destroy(&mutex_) == 0);
}

void Mutex::Lock() {
  CHECK(pthread_mutex_lock(&mutex_) == 0);
}

bool Mutex::TryLock() {
  return pthread_mutex_trylock(&mutex_) == 0;
}

void Mutex::Unlock() {
  CHECK(pthread_mutex_unlock(&mutex_) == 0);
}

}  // namespace threading
