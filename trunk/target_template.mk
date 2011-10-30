# Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# TODO(timurrrr): it's probably better to list files manually in
# target-specific .mk's. We should do that when our codebase becomes
# more-or-less stable.
# TODO(timurrrr) Also, the $(TARGET)_ prefix is ugly.
# Makefile gurus are welcome to fix this more elegantly.
#
# This will be changed when we migrate to CMake, see
# (see http://code.google.com/p/mipt-course/issues/detail?id=1 )

# Get the list of ".h" files for the given TARGET
$(TARGET)_H_LIST=$(wildcard $(TARGET)/*.h)

# Get the list of ".cpp" files and trim the ".cpp" extension
# TEST_CPP_LIST will contain *_test.cpp files
# LIB_CPP_LIST  will contain all other .cpp files
$(TARGET)_ALL_CPP_LIST=$(patsubst %.cpp,%,$(wildcard $(TARGET)/*.cpp))
$(TARGET)_TEST_CPP_LIST=$(patsubst %.cpp,%,$(wildcard $(TARGET)/*_test.cpp))
$(TARGET)_LIB_CPP_LIST=$(filter-out $($(TARGET)_TEST_CPP_LIST), $($(TARGET)_ALL_CPP_LIST))

# Turn all "TARGET/X.cpp" into "out/TARGET_X.obj"
$(TARGET)_LIB_OBJ_LIST=$(patsubst %,$(OUTDIR)%.$(OBJ),$($(TARGET)_LIB_CPP_LIST))
$(TARGET)_TEST_OBJ_LIST=$(patsubst %,$(OUTDIR)%.$(OBJ),$($(TARGET)_TEST_CPP_LIST))

$(TARGET)_DIR=$(OUTDIR)$(TARGET)
$($(TARGET)_DIR):
	mkdir -p $@

# "$<" stands for "first dependency"
# "$@" stands for "rule name"
# TODO(timurrrr): smarter .h dependencies, e.g. "g++ -MM"
$(OUTDIR)$(TARGET)/%.$(OBJ): $(TARGET)/%.cpp $($(TARGET)_H_LIST) | $($(TARGET)_DIR)
	$(CC) $(CC_FLAGS) -o $@ -c $<

# "$@" stands for "rule name"
# "$^" stands for "all dependencies
# TODO(timurrrr): this fails when there aren't any OBJs for this target
$(OUTDIR)lib$(TARGET).a: $($(TARGET)_LIB_OBJ_LIST)
	$(AR) $@ $^

$(OUTDIR)$(TARGET)_tests: $($(TARGET)_TEST_OBJ_LIST) $(OUTDIR)lib$(TARGET).a \
			  $(OUTDIR)libgooglemock.a $(OUTDIR)libgoogletest.a
	$(LINK) $(LINK_FLAGS) -o $@ $^
