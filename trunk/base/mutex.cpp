// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/mutex.h"

namespace threading {

Mutex::Mutex() {
#ifndef NDEBUG
  pthread_mutexattr_t attr;
  CHECK_EQ(pthread_mutexattr_init(&attr), 0);

  // If a thread attempts to relock a mutex that it has already locked,
  // an error shall be returned. If a thread attempts to unlock a mutex
  // that it has not locked or a mutex which is unlocked, an error
  // shall be returned.
  CHECK_EQ(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK), 0);
  CHECK_EQ(pthread_mutex_init(&mutex_, &attr), 0);
  CHECK_EQ(pthread_mutexattr_destroy(&attr), 0);
  is_locked_ = false;
#else
  CHECK_EQ(pthread_mutex_init(&mutex_, NULL), 0);
#endif
}

Mutex::~Mutex() {
#ifndef NDEBUG
  CHECK_EQ(is_locked_, false);
#endif
  CHECK_EQ(pthread_mutex_destroy(&mutex_), 0);
}

void Mutex::AssertHeld() {
#ifndef NDEBUG
  CHECK_EQ(is_locked_, true);
#endif
}

void Mutex::Lock() {
  // Since we have PTHREAD_MUTEX_ERRORCHECK mutex type, we need not perform
  // twice-lock checks in debug mode.
  CHECK_EQ(pthread_mutex_lock(&mutex_), 0);
#ifndef NDEBUG
  CHECK_EQ(is_locked_, false);
  is_locked_ = true;
#endif
}

bool Mutex::TryLock() {
  bool result = (pthread_mutex_trylock(&mutex_) == 0);
#ifndef NDEBUG
  if (result) {
    CHECK_EQ(is_locked_, false);
    is_locked_ = true;
  }
#endif
  return result;
}

void Mutex::Unlock() {
#ifndef NDEBUG
  CHECK_EQ(is_locked_, true);
  is_locked_ = false;
#endif
  CHECK_EQ(pthread_mutex_unlock(&mutex_), 0);
}

}  // namespace threading
