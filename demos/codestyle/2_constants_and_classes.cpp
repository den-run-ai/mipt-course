// Non-Copyright 2010 Timur Iskhodzhanov
#include <assert.h>

const int kConstantName = 42;
// или
const int CONSTANT_NAME = 42;

enum UrlTableErrors {
  kOK = 0,
  kErrorOutOfMemory,
  kErrorMalformedInput,
};

#define MY_MACRO_THAT_SCARES_SMALL_CHILDREN(x) x + x

#define CHECK(x)  // TODO(timurrrr): see base/common.h

struct SimpleStruct {
  int field_name;
};

void StructDemo() {
  struct SimpleStruct test_struct;
  test_struct.field_name = 42;

  struct SimpleStruct *test_struct_pointer = &test_struct;
  test_struct_pointer->field_name = 42;
}

// Макрос, который при правильном использовании (см. ниже) запрещает конструктор
// копирования и оператор присваивания для типа данных TypeName, что позволяет
// избежать неочевидных логических ошибок, а также скрытых проблем
// производительности (копирование).
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class MyClass {
  // Вначале публичная секция - потому что именно её читают все пользователи
  // класса, а вовсе не приватные данные.
 public:  // Отступ - 1 пробел!
  // Вначале конструкторы и деструкторы.
  MyClass() { }

  // Заметьте ключевое слово "explicit" - обязательно применять его
  // для конструкторов с одним аргументом!
  explicit MyClass(int i) { }
  // explicit запрещает писать так:
  // MyClass mc = 42;

  ~MyClass() { }

  // Публичные методы - именуются как функции.
  void MyMethod() const { }

  // get-ер для поля X_ называется X.
  int value() const { return value_; }

  // set-ер называется set_X для поля X_.
  void set_value(int value) {
    assert(value > 0);  // you can add extra checks
    value_ = value;
  }

  // !!! Публичные данные (поля) запрещены !!!

  // Вторая секция - protected.
 protected:
  // Вначале методы, затем поля (зачем поля?).

  // ...

  // Последняя секция - private.
 private:
  // Вначале методы, затем поля.
  int value_;  // Названия private полей заканчиваются на "_".

  DISALLOW_COPY_AND_ASSIGN(MyClass);  // А вот и использование!
};

int main() { }
