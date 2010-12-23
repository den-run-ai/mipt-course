// Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MUTEX_H_
#define BASE_MUTEX_H_

#include <pthread.h>

#include "base/common.h"

namespace threading {

class ConditionVariable;

// OS-independent wrapper for mutex/critical section synchronization primitive.
// This Mutex is NOT re-entrant!
class Mutex {
 public:
  Mutex();
  ~Mutex();
  void Lock();

  /*!
      Attempts to lock the mutex. If the lock was obtained, this function
      returns true. If another thread has locked the mutex, this
      function returns false immediately.

      If the lock was obtained, the mutex must be unlocked with Unlock()
      before another thread can successfully lock it.
  */
  bool TryLock();
  void Unlock();
  void AssertHeld();

 private:
  pthread_mutex_t mutex_;
#ifndef NDEBUG
  bool is_locked_;
#endif
  // pthread_cond_t wrapper needs access to mutex_ to use pthread_cond_wait
  friend class ConditionVariable;
  DISALLOW_COPY_AND_ASSIGN(Mutex)
};


// A helper class that acquires the given Mutex while the MutexLock is in scope
class MutexLock {
 public:
  explicit MutexLock(Mutex *m): mutex_(m) {
    CHECK(mutex_ != NULL);
    mutex_->Lock();
  }

  ~MutexLock() {
    mutex_->Unlock();
  }

 private:
  Mutex * const mutex_;
  DISALLOW_COPY_AND_ASSIGN(MutexLock)
};

}  // namespace threading

#endif  // BASE_MUTEX_H_
