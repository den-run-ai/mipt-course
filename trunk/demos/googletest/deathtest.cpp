#include <gtest/gtest.h>
#include <stdio.h>

// http://code.google.com/p/googletest/wiki/AdvancedGuide#Death_Tests

int divide(int a, int b) {
  if (b == 0) {
    fprintf(stderr, "Shouldn't divide by zero!\n");
    abort();
  }
  return a / b;
}

TEST(MyFunctionTests, Sum) {
  ASSERT_DEATH(divide(42, 0), "by zero");
}
