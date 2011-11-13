// Copyright (c) 2011 Timur Iskhodzhanov and others. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_CONDITION_VARIABLE_H_
#define BASE_CONDITION_VARIABLE_H_

#include <pthread.h>

#include "base/common.h"

namespace threading {

class Mutex;

class ConditionVariable {
 public:
  // By passing a mutex pointer to the ConditionVariable constructor instead
  // of passing it to the methods we guarantee that this ConditionVariable
  // is always used with one and only one Mutex.
  explicit ConditionVariable(Mutex *mutex);
  ~ConditionVariable();

  // All Wait/Wake methods can only be called when 'mutex' is held.
  void Wait();
  bool WaitWithTimeout(unsigned long time);
  void WakeOne();
  void WakeAll();

 private:
  pthread_cond_t cond_;
  Mutex *mutex_;

  DISALLOW_COPY_AND_ASSIGN(ConditionVariable)
};

}  // namespace threading

#endif  // BASE_CONDITION_VARIABLE_H_
