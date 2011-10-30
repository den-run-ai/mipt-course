# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

GMOCK_ROOT=third_party/googlemock
GTEST_ROOT=third_party/googlemock/gtest
# Add googletest to the include path.
CC_FLAGS+=-I$(GMOCK_ROOT)/include -I$(GTEST_ROOT)/include

GMOCK_LIB=$(OUTDIR)libgooglemock.a
GTEST_LIB=$(OUTDIR)libgoogletest.a

$(OUTDIR)testing/googletest_main.obj: testing/googletest_main.cpp
	mkdir -p $(OUTDIR)testing
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(GMOCK_LIB): $(OUTDIR)testing/googletest_main.obj
	make -C $(GMOCK_ROOT)/make gmock-all.o
	$(AR) $@ $(GMOCK_ROOT)/make/gmock-all.o $^

$(GTEST_LIB): $(OUTDIR)testing/googletest_main.obj
	make -C $(GTEST_ROOT)/make gtest-all.o
	$(AR) $@ $(GTEST_ROOT)/make/gtest-all.o $^

.PHONY: GTEST_CLEAN
GTEST_CLEAN:
	make -C $(GTEST_ROOT)/make clean
