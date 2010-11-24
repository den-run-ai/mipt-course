# Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

CC=g++
CC_FLAGS=$(CXXFLAGS)
CC_FLAGS+=-I.    # Add src root to the include path.
CC_FLAGS+=-Wall  # Print all warnings

# We use BUILDTYPE because TARGET is already used in module script

ifeq ($(BUILDTYPE),release)
  OUTDIR=out/Release/
  CC_FLAGS+=-DNDEBUG # No debug info, full optimize
  ifeq ($(OPTIMIZE),no)
    CC_FLAGS+=-O1 # Seldom we need not full optimize in debug
  else
    CC_FLAGS+=-O2 # But by default full optimize
  endif
else # By default do debug
  OUTDIR=out/Debug/
  CC_FLAGS+=-g -D_DEBUG # Add debug information
  ifeq ($(OPTIMIZE),yes)
    CC_FLAGS+=-O1 # Seldom we need some optimize in debug
  else
    CC_FLAGS+=-O0 # But by default no optimize
  endif
endif

OBJ=obj
AR=ar cru

LINK=g++
ADDITIONAL_LIBS=  # Will contain the list of system libs to link (e.g. pthread)
# Targets can add libs using "ADDITIONAL_LIBS+=<libs>"
# and they will automatically be added to LINK_FLAGS since variable values are
# calculated when they are used, see
# http://stackoverflow.com/questions/448910/makefile-variable-assignment
LINK_FLAGS += $(patsubst %,-l%,$(ADDITIONAL_LIBS))

# "@" at the beginning means "don't print the command itself"
all:
	@echo "Nothing to do by default, for details try: make help "
# help  - Display callable targets.
help:
	@egrep "^# [a-z ]+ - " Makefile
	@echo "Additional flags:"
	@echo "  BUILDTYPE=debug|release [default: debug]"
	@echo "  For debug"
	@echo "    OPTIMIZE=yes|no [default: no]"
	@echo "  For release"
	@echo "    OPTIMIZE=yes|no [default: yes]"

TARGETS=base sandbox

TARGET_LIBS=$(patsubst %,$(OUTDIR)lib%.a,$(TARGETS))
TARGET_TESTS=$(patsubst %,$(OUTDIR)%_tests,$(TARGETS))
RUN_TEST_TARGETS=$(patsubst %,run_%_test,$(TARGETS))

include $(patsubst %,%/target.mk,$(TARGETS))

include testing/googletest.mk

# http://www.gnu.org/software/automake/manual/make/Phony-Targets.html
.PHONY: build test clean

# build - Build the program.
build: $(TARGET_LIBS) $(TARGET_TESTS)

# rebuild - Clean & rebuild the program.
rebuild: clean build

USE_VALGRIND=
TEST_COMMAND_PREFIX=
ADDITIONAL_FLAGS=
ifeq ($(USE_VALGRIND),1)
  TEST_COMMAND_PREFIX=valgrind --leak-check=full --error-exitcode=255
  # TODO(timurrrr): support user-specified --gtest_filter
  ADDITIONAL_ARGS=--gtest_filter="-*Death*"
endif

run_%_test: $(OUTDIR)%_tests
	@echo "Running $<..."
	@$(TEST_COMMAND_PREFIX) ./$< $(ADDITIONAL_ARGS)

# test  - Build and run the test suite.
test: $(RUN_TEST_TARGETS)
	@echo "All tests passed"

# clean - Remove intermediate files and the program.
clean:
	rm -rf ./$(OUTDIR)
