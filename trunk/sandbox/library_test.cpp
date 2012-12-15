// Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>
#include <memory>
#include <set>
#include <string>

#include "gtest/gtest.h"

#include "base/common.h"

typedef int ISBN;  // TODO(timurrrr): define a real ISBN

// TODO(timurrrr): make this a class
struct BookID {
  ISBN isbn;
  std::string author, caption;
};

class LibraryIndex {
 public:
  LibraryIndex() {}

  void Add(ISBN isbn, const std::string &author, const std::string &caption) {
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

  class UserAccount {
   public:
    explicit UserAccount(UserID id) : id_(id) { }

    UserID id() { return id_; }

    int CountBooks(ISBN isbn) {
      // Fake it for now. TODO(timurrrr): implement
      return 0;
    }

   private:
    UserID id_;

    // TODO(timurrrr): use std::multiset<> to store the book record

    DISALLOW_COPY_AND_ASSIGN(UserAccount);
  };

  LibraryDB() {}

  // TODO(timurrrr): implement the methods below
  UserAccount* GetUser(UserID id) {
    // Fake it for now!
    return new UserAccount(id);
  }

  bool GiveBook(ISBN isbn, UserAccount *recipient) {
    // Fake it for now!
    return true;
  }

  bool ReturnBook(ISBN isbn, UserAccount *holder) {
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

  std::auto_ptr<LibraryDB::UserAccount> user;
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

  // UserAccount should have the book first, right?
  ASSERT_TRUE(library.GiveBook(TDD_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 1);

  ASSERT_TRUE(library.ReturnBook(TDD_ISBN, user.get()));
  ASSERT_EQ(user->CountBooks(TDD_ISBN), 0);
}
