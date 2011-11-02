// Non-Copyright 2010 Timur Iskhodzhanov
#include <assert.h>

const int kConstantName = 42;

enum UrlTableErrors {
  kOK = 0,
  kErrorOutOfMemory,
  kErrorMalformedInput,
};

#define MY_MACRO_THAT_SCARES_SMALL_CHILDREN(x) x+x

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

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class MyClass {
  // Public first
 public:  // 1-space indent!
  // constructors & destructors
  MyClass() { }

  explicit MyClass(int i) { }  // note the "explicit"!
  /* to ban the following construction:
     MyClass mc = 42;
   */

  ~MyClass() { }

  // public methods
  void MyMethod() const { }

  int value() const { return value_; }  // get-accessor for value_

  // set-accessor for value_
  void set_value(int value) {
    assert(value > 0);  // you can add extra checks
    value_ = value;
  }

  // !!! should be no public fields !!!

  // Protected second
 protected:
  // Methods, then fields

  // ...

  // Private last
 private:
  // Methods, then fields
  int value_;  // private field names should end with "_"

  DISALLOW_COPY_AND_ASSIGN(MyClass);
};

int main() { }
