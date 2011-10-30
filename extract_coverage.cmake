# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

find_program(lcov_enabled, lcov)

if (lcov_enabled STREQUAL "NOTFOUND")
  message(FATAL_ERROR
    "Couldn't find lcov. Try to install it: sudo apt-get install lcov"
  )
endif()

set (COVERAGE_OUT ${SEARCH_DIR}/CoverageResults)

if (NOT EXISTS ${COVERAGE_OUT})
  execute_process(COMMAND mkdir ${COVERAGE_OUT})
endif()

execute_process(COMMAND lcov --directory ${SEARCH_DIR}
  --capture OUTPUT_FILE ${COVERAGE_OUT}/lcov.info
)

execute_process(COMMAND lcov --remove ${COVERAGE_OUT}/lcov.info
  "/usr/include/c++/*" "third_party/*"
  OUTPUT_FILE ${COVERAGE_OUT}/modified_lcov.info
)

execute_process(COMMAND genhtml --output-directory ${COVERAGE_OUT}
  ${COVERAGE_OUT}/modified_lcov.info --highlight --legend
  --title "Coverage Statistics" --num-spaces 2
)

