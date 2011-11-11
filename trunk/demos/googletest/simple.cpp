#include <gtest/gtest.h>

// Build with:
// g++ -lgtest_main simple.cpp

int sum(int a, int b) {
  // the function we want to test
  return a + b;
}

TEST(MyFunctionTests, Sum) {
  EXPECT_EQ(2 /* expected */, sum(1, 2) /* actual */);
  // EXPECT_ - doesn't terminate the execution on failure.
  printf("Will be executed\n");

  ASSERT_EQ(5 /* expected */, sum(2, 2) /* actual */);
  // ASSERT_ - terminates the execution on failure.
  printf("Won't be executed\n");
}
