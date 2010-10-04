# Copyright (c) 2010 Timur Iskhodzhanov. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# TODO(timurrrr): it's probably better to list files manually in
# target-specific .mk's. We should do that when our codebase becomes
# more-or-less stable.

# Get the list of ".h" files for the given TARGET
H_LIST=$(wildcard $(TARGET)/*.h)

# Get the list of ".cpp" files and trim the ".cpp" extension
# TEST_CPP_LIST will contain *_test.cpp files
# LIB_CPP_LIST  will contain all other .cpp files
ALL_CPP_LIST=$(patsubst %.cpp,%,$(wildcard $(TARGET)/*.cpp))
TEST_CPP_LIST=$(patsubst %.cpp,%,$(wildcard $(TARGET)/*_test.cpp))
LIB_CPP_LIST=$(filter-out $(TEST_CPP_LIST), $(ALL_CPP_LIST))

# Turn all "TARGET/X.cpp" into "out/TARGET_X.obj"
LIB_OBJ_LIST=$(patsubst %,$(OUTDIR)%.$(OBJ),$(LIB_CPP_LIST))
TEST_OBJ_LIST=$(patsubst %,$(OUTDIR)%.$(OBJ),$(TEST_CPP_LIST))

TARGET_DIR=$(OUTDIR)$(TARGET)
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# "$<" stands for "first dependency"
# "$@" stands for "rule name"
$(OUTDIR)$(TARGET)/%.$(OBJ): $(TARGET)/%.cpp $(H_LIST) | $(TARGET_DIR)
	$(CC) -o $@ -c $<

# "$@" stands for "rule name"
# "$^" stands for "all dependencies
# TODO(timurrrr): this fails when there aren't any OBJs for this target
$(OUTDIR)lib$(TARGET).a: $(LIB_OBJ_LIST)
	$(AR) $@ $^

$(OUTDIR)$(TARGET)_tests: $(TEST_OBJ_LIST) $(OUTDIR)lib$(TARGET).a
	$(LINK) $(LINK_FLAGS) -o $@ $^
