// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// author: Dima Arkhangelskiy
// project: Math Expression Analyser and Calculator

#include "gtest/gtest.h"


class MathExpressionCalculator {
 public:
  enum StatusCode {
    kOk = 0,
    kDivisionByZero,
    kEmptyExpression,
    kSyntaxError,
    kUndefinedStatus,
    kUndefinedVariable,
    kUnbalancedParentheses
  };

  MathExpressionCalculator() {}

  StatusCode Calculate(const char *expr, double *result) {
    return kUndefinedStatus;
  }

  void SetVariable(const char *var_name, double value) {
    return;
  }

  // Find value by name. If there isn't variable with
  // such name return false.
  bool Lookup(const char *var_name, double *out_value) {
    return false;
  }
};

TEST(MathExpressionTests, DISABLED_SimpleExpressions) {
  MathExpressionCalculator calc;
  double result = 42.0;

  // For each expression, check it is parsed and calculated correctly.
  ASSERT_EQ(calc.kOk, calc.Calculate("1 + 2", &result));
  ASSERT_DOUBLE_EQ(3.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("10 - 5", &result));
  ASSERT_DOUBLE_EQ(5.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("2 * 3", &result));
  ASSERT_DOUBLE_EQ(6.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("6 / 3", &result));
  ASSERT_DOUBLE_EQ(2.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("10 % 3", &result));
  ASSERT_DOUBLE_EQ(1.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("2 ^ 3", &result));
  ASSERT_DOUBLE_EQ(8.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("2 + 3 * 2", &result));
  ASSERT_DOUBLE_EQ(8.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("(2 + 3) * 2", &result));
  ASSERT_DOUBLE_EQ(10.0, result);

  ASSERT_EQ(calc.kOk, calc.Calculate("7 + 6 * 20 / 5/ 4 - 3", &result));
  ASSERT_DOUBLE_EQ(10.0, result);
}

TEST(MathExpressionTests, DISABLED_ErrorHandling) {
  MathExpressionCalculator calc;
  double result;

  ASSERT_EQ(MathExpressionCalculator::kSyntaxError,
            calc.Calculate("2***2", &result));

  ASSERT_EQ(MathExpressionCalculator::kEmptyExpression,
            calc.Calculate("", &result));

  ASSERT_EQ(MathExpressionCalculator::kUnbalancedParentheses,
            calc.Calculate("((2 + 3)", &result));

  ASSERT_EQ(MathExpressionCalculator::kDivisionByZero,
            calc.Calculate("2 / 0", &result));
}

TEST(MathExpressionTests, DISABLED_VariableHandling) {
  MathExpressionCalculator calc;
  calc.SetVariable("x", 10);

  // Check the variable value is stored correctly.
  double var;
  ASSERT_TRUE(calc.Lookup("x", &var));
  ASSERT_DOUBLE_EQ(10.0, var);

  // Check that we use variable correctly.
  double result, default_result;
  ASSERT_EQ(calc.kOk, calc.Calculate("2 * 10 + 1", &default_result));

  ASSERT_EQ(calc.kOk, calc.Calculate("2 * x + 1", &result));

  ASSERT_DOUBLE_EQ(21.0, default_result);
  ASSERT_DOUBLE_EQ(default_result, result);
}

TEST(MathExpressionTests, DISABLED_UndefinedVariable) {
  MathExpressionCalculator calc;
  double var, result;
  ASSERT_FALSE(calc.Lookup("x", &var));
  ASSERT_EQ(MathExpressionCalculator::kUndefinedVariable,
            calc.Calculate("2 * x + 1", &result));
}

