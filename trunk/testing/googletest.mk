# Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

GTEST_ROOT=third_party/googletest
# Add googletest to the include path.
CC_FLAGS+=-I$(GTEST_ROOT)/include

GTEST_LIB=$(OUTDIR)libgoogletest.a

$(OUTDIR)testing/googletest_main.obj: testing/googletest_main.cpp
	mkdir -p $(OUTDIR)testing
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(GTEST_LIB): $(OUTDIR)testing/googletest_main.obj
	make -C $(GTEST_ROOT)/make gtest-all.o
	$(AR) $@ $(GTEST_ROOT)/make/gtest-all.o $^

.PHONY: GTEST_CLEAN
GTEST_CLEAN:
	make -C $(GTEST_ROOT)/make clean
