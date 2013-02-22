// Non-Copyright 2010 Timur Iskhodzhanov
#include <stdio.h>

// Макрос, который при правильном использовании (см. ниже) запрещает конструктор
// копирования и оператор присваивания для типа данных TypeName, что позволяет
// избежать неочевидных логических ошибок, а также скрытых проблем
// производительности (копирование).
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
/////////////////////////////////////////////////////////////////////

class Foo {
 public:
  Foo() {
    array_ = new int[10];
    printf("array_ = new int[10];  // returned %p\n", array_);
  }

  // Foo(const Foo &other);
  /* Конструктор копирования, вызывается при создании b:
     Foo b = a;

     Поведение по умолчанию - поэлементное копирование.
   */

  // Foo& operator= (const Foo &right_operand);
  /* Оператор присваивания, вызывается на такой строке:
     Foo a, b;
     b = a;
     // b.operator=(a);

     Поведение по умолчанию - поэлементное копирование.
   */

  ~Foo() {
    printf("delete [] array_;  // array_ = %p\n", array_);
    delete [] array_;
  }

 private:
  int *array_;

#if 0
  // А вот и использование макроса DISALLOW_COPY_AND_ASSIGN.
  //
  // Если выше заменить 0 на 1, места где есть ошибки использования класса Foo
  // больше не будут компилироваться!
  DISALLOW_COPY_AND_ASSIGN(Foo);
#endif
};

void PassFooByValue(Foo f) { }

int main() {
  Foo a,
      b = a,  // На этой строке вызывается конструктор копирования.
      c;
  c = a;  // Оператор присваивания - приводит ещё и к утечке памяти.

  PassFooByValue(a);  // На этой строке вызывается конструктор копирования.
  printf("DONE\n");

  // Итого, декструктор вызывается 4 раза, то есть 4 раза вызывается delete []
  // с одним и тем же адресом в качестве аргумента -> "крыша" у кучи "поехала".
  // Помимо этого, при присвоении 'c = a' происходит утечка памяти (утекает
  // память, выделенная в конструкторе 'c'),
  // да и вызов PassFooByValue не может похвастаться эффективностью.
  //
  // От всех этих ошибок на стадии компиляции спасает DISALLOW_COPY_AND_ASSIGN.
}