// Non-Copyright 2010 Timur Iskhodzhanov
#include <stdio.h>

// Макрос, который при правильном использовании (см. ниже) запрещает конструктор
// копирования и оператор присваивания для типа данных TypeName, что позволяет
// избежать неочевидных логических ошибок, а также скрытых проблем
// производительности (копирование).
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class Foo {
 public:
  Foo() {
    array_ = new int[10];
    printf("array_ = new int[10];  // returned %p\n", array_);
  }
  ~Foo() {
    printf("delete [] array_;  // array_ = %p\n", array_);
    delete [] array_;
  }

 private:
  int *array_;

#if 0
  // Если выше заменить 0 на 1, места где есть ошибки использования класса Foo
  // больше не будут компилироваться!
  DISALLOW_COPY_AND_ASSIGN(Foo);
#endif
};

void PassFooByValue(Foo f) { }

int main() {
  Foo a,
      b = a;  // На этой строке вызывается оператор присваивания.

  PassFooByValue(a);  // На этой строке вызывается конструктор копирования.
  // Итого, декструктор вызывается 3 раза, то есть 3 раза вызывается delete []
  // с одним и тем же адресом в качестве аргумента -> "крыша" у кучи "поехала".
}
