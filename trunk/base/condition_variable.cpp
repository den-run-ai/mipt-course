// Copyright (c) 2011 Timur Iskhodzhanov and others. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/condition_variable.h"

#include <pthread.h>
#include <sys/time.h>
#include <errno.h>

#include <limits>

#include "base/mutex.h"

namespace threading {

ConditionVariable::ConditionVariable(Mutex *mutex) {
  CHECK(mutex != NULL);
  mutex_ = mutex;
  CHECK_EQ(pthread_cond_init(&cond_, NULL), 0);
}

ConditionVariable::~ConditionVariable() {
  CHECK_EQ(pthread_cond_destroy(&cond_), 0);
}

void ConditionVariable::Wait() {
  mutex_->AssertHeld();
  CHECK_EQ(pthread_cond_wait(&cond_, &mutex_->mutex_), 0);
}

bool ConditionVariable::WaitWithTimeout(unsigned long time) {
  if (time == std::numeric_limits<unsigned long>::max()) {
    Wait();
    return true;
  }
  mutex_->AssertHeld();
  struct timeval tv;
  gettimeofday(&tv, 0);
  timespec ti;
  ti.tv_nsec = (tv.tv_usec + (time % 1000) * 1000) * 1000;
  ti.tv_sec = tv.tv_sec + (time / 1000) + (ti.tv_nsec / 1000000000);
  ti.tv_nsec %= 1000000000;
  const int code = pthread_cond_timedwait(&cond_, &mutex_->mutex_, &ti);
  CHECK(code == 0 || code == ETIMEDOUT);
  return (code == 0);
}

void ConditionVariable::WakeOne() {
  mutex_->AssertHeld();
  CHECK_EQ(pthread_cond_signal(&cond_), 0);
}

void ConditionVariable::WakeAll() {
  mutex_->AssertHeld();
  CHECK_EQ(pthread_cond_broadcast(&cond_), 0);
}

}  // namespace threading
