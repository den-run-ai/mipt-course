// Copyright (c) 2010 Timur Iskhodzhanov and others. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/mutex.h"

namespace threading {

Mutex::Mutex() {
#ifdef _DEBUG
  pthread_mutexattr_t attr;
  CHECK(pthread_mutexattr_init(&attr) == 0);

  // If a thread attempts to relock a mutex that it has already locked,
  // an error shall be returned. If a thread attempts to unlock a mutex
  // that it has not locked or a mutex which is unlocked, an error
  // shall be returned.
  CHECK(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) == 0);
  CHECK(pthread_mutex_init(&mutex_, &attr) == 0);
  CHECK(pthread_mutexattr_destroy(&attr) == 0);
  is_locked_ = false;
#else
  CHECK(pthread_mutex_init(&mutex_, NULL) == 0);
#endif
}

Mutex::~Mutex() {
#ifdef _DEBUG
  CHECK(is_locked_ == false);
#endif
  CHECK(pthread_mutex_destroy(&mutex_) == 0);
}

void Mutex::Lock() {
  // Since we have PTHREAD_MUTEX_ERRORCHECK mutex type, we need not perform
  // twice-lock checks in debug mode.
  CHECK(pthread_mutex_lock(&mutex_) == 0);
#ifdef _DEBUG
  CHECK(is_locked_ == false);
  is_locked_ = true;
#endif
}

bool Mutex::TryLock() {
  bool result = (pthread_mutex_trylock(&mutex_) == 0);
#ifdef _DEBUG
  if (result) {
    CHECK(is_locked_ == false);
    is_locked_ = true;
  }
#endif
  return result;
}

void Mutex::Unlock() {
#ifdef _DEBUG
  CHECK(is_locked_ == true);
  is_locked_ = false;
#endif
  CHECK(pthread_mutex_unlock(&mutex_) == 0);
}

}  // namespace threading
