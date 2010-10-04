# Copyright (c) 2010 Timur Iskhodzhanov. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

OUTDIR=out/
CC=g++
AR=ar cru
LINK=g++
OBJ=obj

ADDITIONAL_LIBS=  # Will contain the list of system libs to link (e.g. pthread)
LINK_FLAGS += $(patsubst %,-l%,$(ADDITIONAL_LIBS))

# "@" at the beginning means "don't print the command itself"
all:
	@echo "Hello $(LOGNAME), nothing to do by default"
	@echo "Try 'make help'"

# help  - Display callable targets.
help:
	@egrep "^# [a-z ]+ - " Makefile

TARGETS=base

TARGET_LIBS=$(patsubst %,$(OUTDIR)lib%.a,$(TARGETS))
TARGET_TESTS=$(patsubst %,$(OUTDIR)%_tests,$(TARGETS))
RUN_TEST_TARGETS=$(patsubst %,run_%_test,$(TARGETS))

include $(patsubst %,%/target.mk,$(TARGETS))

# http://www.gnu.org/software/automake/manual/make/Phony-Targets.html
.PHONY: build test clean

# build - Build the program.
build: $(TARGET_LIBS) $(TARGET_TESTS)

run_%_test: $(OUTDIR)%_tests
	@echo "Running $<..."
	@./$<

# test  - Build and run the test suite.
test: $(RUN_TEST_TARGETS)
	@echo "All tests passed"

# clean - Remove intermediate files and the program.
clean:
	# This can be dangerous!! Please double-check before removing anything.
	rm -rI $(OUTDIR)
