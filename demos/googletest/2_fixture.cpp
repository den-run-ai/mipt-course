#include <stdio.h>

#include <gtest/gtest.h>

// http://code.google.com/p/googletest/wiki/Primer#Test_Fixtures:_Using_the_Same_Data_Configuration_for_Multiple_Te

// Некое подобие класса-интерфейса для базы данных.
// Практический смысл отсутствует, просто демонстрация.
class Database {
 public:
  Database()  { printf("DB created\n"); }
  ~Database() { printf("DB destroyed\n"); }

  bool Connect() {
    printf("Connected!\n");
    return true;
  }

  void ReleaseResources() { printf("Released...\n"); }

  void DoSomething() { printf("Doing something\n"); }
  void DoSomethingElse() { printf("Doing something else\n"); }
};

// A new instance is created for each test case being run.
class DatabaseTest : public ::testing::Test {
 protected:
  // Вызывается перед запуском каждого теста.
  virtual void SetUp() {
    ASSERT_TRUE(database_.Connect());
  }

  // Вызывается после каждого теста, даже в случае FAILURE.
  virtual void TearDown() {
    database_.ReleaseResources();
  }

  Database database_;
};

TEST_F(DatabaseTest, DoSomeStuff) {
  database_.DoSomething();
}

TEST_F(DatabaseTest, DoSomeOtherStuff) {
  database_.DoSomethingElse();
}
