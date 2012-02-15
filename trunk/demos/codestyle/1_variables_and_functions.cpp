// Non-Copyright 2010 Timur Iskhodzhanov
#include <stdio.h>

#include <string>

// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Static_and_Global_Variables#Static_and_Global_Variables
int AVOID_GLOBALS;

// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Function_Declarations_and_Definitions#Function_Declarations_and_Definitions
// Function names - camel case
int DeclareSimpleFunctionsLikeThis(int a, int b) {
  return a + b;  // note the 2 spaces indentation.
}

struct Result {
  char value;
  int some_other_data;
};
/* http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Function_Parameter_Ordering#Function_Parameter_Ordering
 * POD in parameters - pass by value,
 * Compound in parameters - pass by const reference,
 * OUT parameters - pass by pointer, only at the end.

 WHY?
  int i = 42;
  std::string str = "ZZ";
  struct Result s;
  DeclareComplexFunctionsLikeThis(i, str, &s);
  -- it's easy to see that 'i' and 'str' are passed read-only
     and 's' will likely be changed. 
 */
void DeclareComplexFunctionsLikeThis(int in_parameter,
                                     const std::string &in_compound_parameter,
                                     struct Result *out_parameter) {
  out_parameter->value = in_compound_parameter.c_str()[in_parameter];
}


int main() {
  // variable names - lowercase with underscore:
  int example_variable = 0;

  // pointers - asterisks at the name.
  // Remember: in C++, "*" applies to the variable name, not the type!!!
  int *pointer_definition = &example_variable, *pointer2;
  // NOT "int* pointer1, pointer2;"

  // Some examples of if/else, for, while
  if (example_variable == 1) {
    printf("Shouldn't be printed\n");
  }
  // NOT "if(condition){"
  // NOT "if (condition){"
  // NOT "if(condition) {"

  if (*pointer_definition == 1) {
    printf("Accessing pointers should not add extra spaces!\n");
  }

  if (example_variable == 1) {
    printf("Shouldn't be printed\n");
  } else {
    printf("This program is written according "
           "to Google C++ Code Style Guide\n");
    printf("See http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml"
           " for the details.\n\n");
  }

  printf("As you've noticed, 1 indent = 2 spaces, not tabs.\n");
  printf("Also, we have a 80-char line limit.\n\n");

  if (example_variable == 1)
    printf("You can avoid {} for one-line statements\n");
  else
    printf("Indeed,\nif (condition)\n  statement;\nis compact but ");

  if (example_variable == 1)
    printf("You can avoid {} for one-line statements but ");
    printf("be careful when using if without {}!\n");  // OOPS! This is not
                                                       // detected by cpplint!

  for (int i = 0; i < 1; ++i)
    printf("\nThe same {} rules apply to for");

  while (example_variable++ < 1) {
    printf(" and while loops.\n");
  }

  // You can have small if (condition) statement on one line if that's readable:
  if (example_variable == 1) example_variable = 0;


  // Some examples of calling functions and declaring local variables {{{1
  DeclareSimpleFunctionsLikeThis(1, 2);

  std::string example_string = "Define local variables with as narrow scope as "
                               "possible to help finding the declaration in "
                               "large functions.";
  struct Result result;
  DeclareComplexFunctionsLikeThis(3, example_string, &result);

  return 0;
}
