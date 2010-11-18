// Copyright (c) 2010 Timur Iskhodzhanov and others. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <math.h>

#include <map>
#include <memory>
#include <set>
#include <string>

#include "base/common.h"
#include "third_party/googletest/include/gtest/gtest.h"

int Factorial(int v) {
  // NB we wrote the implementation of this function on the lecture;
  // before the lecture it was simply "return -1;"

  CHECK(v >= 0);
  // TODO(timurrrr): CHECK(v < MAX_FACTORIAL);
  // We can get past (2^31 - 1)
  if (v <= 1)
    return 1;

  // TODO(timurrrr): don't use recursion.
  return v * Factorial(v - 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(1, Factorial(1));
  EXPECT_EQ(2, Factorial(2));
  EXPECT_EQ(6, Factorial(3));
  EXPECT_EQ(40320, Factorial(8));
}

// Tests factorial of 0.
// "Corner case test"
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(1, Factorial(0));
}

TEST(FactorialTest, FailsOnNegativeInputDeathTest) {
  // Suppress the "fork() is unsafe" warnings
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(Factorial(-1), "");
}

//////////////////////////////////////////////
// TODO(timurrrr): move the code below to projects/mipt_library or smth

typedef int ISBN;  // TODO(timurrrr): define a real ISBN

// TODO(timurrrr): make this a class
struct BookID {
  ISBN isbn;
  std::string author, caption;
};

class LibraryIndex {
 public:
  LibraryIndex() {}

  void Add(ISBN isbn, std::string author, std::string caption) {
    CHECK_EQ(index_.count(isbn), 0);
    BookID new_book;
    new_book.isbn = isbn;
    new_book.author = author;
    new_book.caption = caption;
    index_[isbn] = new_book;
  }

  bool Lookup(ISBN isbn, BookID *b) {
    CHECK(b != NULL);
    if (index_.count(isbn) == 0)
      return false;
    *b = index_[isbn];
    return true;
  }

 private:
  std::map<ISBN, BookID> index_;

  DISALLOW_COPY_AND_ASSIGN(LibraryIndex);
};

class LibraryIndexTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Set up a library index
    index.Add(TDD_ISBN, "Kent Beck", "Test Driven Development: By Example");
    /*
    TODO(timurrrr): define a wider range of fields (e.g. co-authors, initials,
                                                    volume #, etc).
    index.Add(LANDAU_ISBN, "L.D. Landau, E.M. Lifshitz",
                           "The Classical Theory of Fields. Vol. 2"); */
  }

  virtual void TearDown() {}

  static const ISBN TDD_ISBN = 1;
  static const ISBN LANDAU_ISBN = 2;

  LibraryIndex index;
};

TEST_F(LibraryIndexTest, LookupOneBookTest) {
  BookID book;
  ASSERT_TRUE(index.Lookup(TDD_ISBN, &book));
  ASSERT_EQ(book.author, "Kent Beck");

  ASSERT_FALSE(index.Lookup(0xDEADBEEF, &book));
  // Check that the book didn't change
  ASSERT_EQ(book.author, "Kent Beck");
}

class LibraryDB {
 public:
  typedef int UserID;

  class User {
   public:
    explicit User(UserID id) : id_(id) { }

    UserID id() { return id_; }

    int CountBooks(ISBN isbn) {
      // Fake it for now. TODO(timurrrr): implement
      return 0;
    }

   private:
    UserID id_;

    // TODO(timurrrr): use std::multiset<> to store the book record

    DISALLOW_COPY_AND_ASSIGN(User);
  };

  LibraryDB() {}

  // TODO(timurrrr): implement the methods below
  User* GetUser(UserID id) {
    // Fake it for now!
    return new User(id);
  }

  bool GiveBook(ISBN isbn, User *recipient) {
    // Fake it for now!
    return true;
  }

  bool ReturnBook(ISBN isbn, User *holder) {
    // Fake it for now!
    return true;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(LibraryDB);
};

class LibraryUserTest : public LibraryIndexTest {
 protected:
  LibraryUserTest() : user(NULL) {}

  virtual void SetUp() {
    LibraryIndexTest::SetUp();
    // Parent::SetUp() should be the first line here.

    user.reset(library.GetUser(1234));
    ASSERT_TRUE(user.get() != NULL);
  }

  virtual void TearDown() {
    // Parent::TearDown() should be the last line here.
    LibraryIndexTest::TearDown();
  }

  std::auto_ptr<LibraryDB::User> user;
  LibraryDB library;
};

// These test don't pass yet, so I've temporarily disabled them
// http://code.google.com/p/googletest/wiki/AdvancedGuide#Temporarily_Disabling_Tests
// Feel free to re-enable them locally or once they start to pass.

TEST_F(LibraryUserTest, DISABLED_UserTakesOneBookTest) {
  // Typical use-case: a user comes to a library, asks for a book and takes it.
  BookID book;
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 0);
  ASSERT_TRUE(library.GiveBook(TDD_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 1);
}

TEST_F(LibraryUserTest, DISABLED_UserTakesTwoBooksTest) {
  BookID book;
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 0);
  ASSERT_EQ(user->CountBooks(LANDAU_ISBN), 0);

  ASSERT_TRUE(library.GiveBook(TDD_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 1);
  ASSERT_EQ(user->CountBooks(LANDAU_ISBN), 0);

  ASSERT_TRUE(library.GiveBook(LANDAU_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 1);
  ASSERT_EQ(user->CountBooks(LANDAU_ISBN), 1);
}

TEST_F(LibraryUserTest, DISABLED_UserReturnsOneBookTest) {
  // Typical use-case: a user comes to a library and returns a book he had;
  BookID book;

  // User should have the book first, right?
  ASSERT_TRUE(library.GiveBook(TDD_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 1);

  ASSERT_TRUE(library.ReturnBook(TDD_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 0);
}
