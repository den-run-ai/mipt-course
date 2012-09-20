// Non-Copyright 2010 Timur Iskhodzhanov
#include <stdio.h>

#include <string>

void VariablesAndStatemants() {
  // Переменные называются ёмкими понятными именами, маленькими буквами
  // с отделением слов подчёркиванием.
  int example_variable = 0;

  // Указатели - звёздочки обязательно НЕ отделять пробелом от имени.
  // Напоминаю: в C++, "*" относится к имени переменной, а не к типу!!!
  int *pointer_definition = &example_variable, *pointer2;
  // NOT "int* pointer1, pointer2;"

  // Примеры if/else, for, while...
  if (example_variable == 1) {
    printf("Shouldn't be printed\n");
  }
  // НЕ "if(condition){",
  // НЕ "if (condition){",
  // НЕ "if(condition) {" !

  if (*pointer_definition == 1) {
    printf("НЕ ставьте лишних пробелов при разыменовывании указателей !\n");
  }

  if (example_variable == 1) {
    printf("Не должно быть распечатано\n");
  } else {
    printf("Программа написана в соответствии "
           "с Google C++ Code Style Guide\n");
    printf("Подробнее см тут:\n"
           "http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml"
           "\n\n");
  }

  printf("Как вы заметили, 1 отступ = 2 пробела, НЕ таба.\n");
  printf("Ограничение на длину строки - 80 символов.\n\n");

  if (example_variable == 1)
    printf("Можно не писать {} для однострочных выражений\n");
  else
    printf("Конечно,\nif (condition)\n  statement;\nудобно, но ");

  if (example_variable == 1)
    printf("Можно не писать {} для однострочных выражений, но ");
    printf("тогда будьте внимательны к отступам {}!\n");  // OOPS! Не находится
                                                          // с помощью cpplint!
  for (int i = 0; i < 1; ++i)
    printf("\nТе же правила про {} применяются к циклу for");

  while (example_variable++ < 1) {
    printf(" и while.\n");
  }

  for (int i = 0; i < 1; ++i) {
    printf("Определяйте переменные");
    // Вы наверное уже обратили внимание, что у каждого
    // цикла for - своя переменная i?
    std::string example_string = " с минимально возможной областью видимости!"
                                 "\nЭто упростит поиск определения переменной"
                                 " при работе с большими функциями.";
  }

  // Можно писать if (condition) statement на одной строке,
  // если это не ухудшает читаемость:
  if (example_variable == 1) example_variable = 0;
}

// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Static_and_Global_Variables#Static_and_Global_Variables
int avoid_globals_whenever_possible;

// Константы лучше определять так:
const int CONSTANT_NAME = 42;
// или так:
const int kConstantName = 42;
// но не через define.

// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Function_Declarations_and_Definitions#Function_Declarations_and_Definitions
// Имена функций - CamelCase.
int SimpleFunction(int a, int b) {
  return a + b;  // Заметьте: отступ!
}

void CallSimpleFunction() {
  // Вызов простой функции.
  SimpleFunction(1, 2);
}

// Объявления структур:
struct Result {
  char some_field;
  int some_other_data;
};

struct OtherStruct {
  int some_field;
};

/* http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Function_Parameter_Ordering#Function_Parameter_Ordering
 * "POD" параметры (int, float, ...) - передавать по значению,
 * Составные входные параметры - по константной ссылке,
 * OUT/выходные параметры - по указателю; в последнюю очередь.
 * Позже будет пример почему ...
 */
void ComplexFunction(int in_parameter,
                     const std::string &in_compound_parameter,
                     struct Result *out_parameter) {
  struct OtherStruct other;
  other.some_field = 42;

  out_parameter->some_field = in_compound_parameter.c_str()[in_parameter];
}

void CallComplexFunction() {
  std::string example_string = "Привет!";
  struct Result result;
  ComplexFunction(3, example_string, &result);
  // Сразу видно что example_string не будет изменена, а result - будет!
}

int main() {
  VariablesAndStatemants();

  CallSimpleFunction();

  CallComplexFunction();

  return 0;
}
