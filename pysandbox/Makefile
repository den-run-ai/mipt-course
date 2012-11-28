# Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

PY=python
TESTS_LIST=$(wildcard *_test.py)
RUN_TEST_TARGETS=$(patsubst %,run_%_test,$(TESTS_LIST))

all:
	@echo "Nothing to do by default, for details try: make help "
# help  - Display callable targets.
help:
	@egrep "^# [a-z ]+ - " Makefile

# http://www.gnu.org/software/automake/manual/make/Phony-Targets.html
.PHONY: test 

run_%_test: %
	@echo "Running $<..."
	$(PY) $<

# test  - run the test suite.
test: $(RUN_TEST_TARGETS)
	@echo "All tests passed"
