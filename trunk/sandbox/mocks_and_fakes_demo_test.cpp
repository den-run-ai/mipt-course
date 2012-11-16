// Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>
#include <set>
#include <utility>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "base/common.h"
#include "base/random.h"

using namespace testing;  // NOLINT

// Dependency injection
// http://en.wikipedia.org/wiki/Dependency_injection

class UdpChannel {
 public:
  virtual void Send(const char *buffer, size_t size) = 0;
  virtual bool Receive(char *buffer, size_t *size) = 0;
  virtual ~UdpChannel() {}
};

class MockUdpChannel : public UdpChannel {
 public:
  MOCK_METHOD2(Send, void(const char *buffer, size_t size));
  MOCK_METHOD2(Receive, bool(char *buffer, size_t *size));
};

class ReliableUdpChannel {
 public:
  explicit ReliableUdpChannel(UdpChannel *chan)
      : channel_(chan), next_receive_(0) { }

  ~ReliableUdpChannel() {
    // TODO(timurrrr): free messages not taken from received_.
  }

  void Heartbeat() {
    const size_t MAX_BUFFER = 1024;

    char local_buffer[MAX_BUFFER];
    size_t local_size = MAX_BUFFER;

    if (!retry_ids_.empty()) {
      // TODO(timurrrr): throttle to avoid excessive traffic
      local_buffer[0] = 'R';
      local_buffer[1] = '0' + *retry_ids_.begin();
      local_buffer[2] = '\0';
      channel_->Send(local_buffer, 3);
    }

    // TODO(timurrrr): check return value
    channel_->Receive(local_buffer, &local_size);

    // TODO(timurrrr): the header should be int or larger...
    CHECK(*local_buffer >= '0' && *local_buffer <= '9');
    size_t index = *local_buffer - '0';
    if (received_.find(index) != received_.end() || index < next_receive_) {
      // Hm, packet received twice?.. Drop it.
      return;
    }

    // TODO(timurrrr): drop packets if received_.size() is too large.

    char * payload = new char[local_size - 1];
    memcpy(payload, local_buffer + 1, local_size - 1);

    received_[index] = std::pair<size_t, char*>(local_size - 1, payload);
  }

  void Send(const char *buffer, size_t size) { NOT_IMPLEMENTED; }

  bool Receive(char *buffer, size_t *size) {
    if (received_.find(next_receive_) == received_.end())
      Heartbeat();

    if (received_.find(next_receive_) == received_.end()) {
      if (!received_.empty()) {
        retry_ids_.insert(next_receive_);
      }
      return false;
    }

    size_t data_size = received_[next_receive_].first;
    char *data = received_[next_receive_].second;

    if (*size < data_size)
      return false;

    *size = data_size;
    memcpy(buffer, data, data_size);
    delete [] data;
    next_receive_++;
    return true;
  }

 private:
  UdpChannel *channel_;
  size_t next_receive_;
  std::map<size_t, std::pair<size_t, char*> > received_;
  std::set<size_t> retry_ids_;
};

ACTION_P(MockReceive, str) {
  size_t required_len = strlen(str) + 1;
  if (required_len > *arg1)
    return false;
  strcpy(arg0, str);  // NOLINT
  *arg1 = required_len;
  return true;
}

TEST(ReliableUdpChannel, SimpleSequence) {
  MockUdpChannel mock;

  // "_" значит "аргумент может принимать любое значение".
  EXPECT_CALL(mock, Receive(_, _))
        .WillOnce(MockReceive("0H"))  // Выполнить MockReceive.
        .WillOnce(MockReceive("1E"))
        .WillOnce(MockReceive("2L"))
        .WillOnce(MockReceive("3L"))
        .WillOnce(MockReceive("4O"));

  char buff[10] = {};
  size_t size;
  ReliableUdpChannel channel(&mock);

  const char *expectations[] = {"H", "E", "L", "L", "O"};
  for (size_t i = 0; i < ARRAY_SIZE(expectations); i++) {
    size = sizeof(buff);
    ASSERT_TRUE(channel.Receive(buff, &size));
    ASSERT_STREQ(expectations[i], buff);
  }
}

TEST(ReliableUdpChannel, OnePacketLost) {
  MockUdpChannel mock;

  // Поведение по умолчанию. Читать:
  // http://code.google.com/p/googlemock/wiki/ForDummies#All_Expectations_Are_Sticky_(Unless_Said_Otherwise)
  EXPECT_CALL(mock, Send(StrEq("R1"), Eq(3u))).Times(AnyNumber());

  // Читать:
  // http://code.google.com/p/googlemock/wiki/CheatSheet#Sequences
  Sequence main, retries /* and before retries */;
  // Нижеприведённый код устанавливает следующее:
  // Два первых вызова Receive вернут 0H, 2L.
  // После этого может быть несколько раз послано сообщение R1.
  // После 2L будут получены сообщения 3L, 1E, 4O.
  // Относительный порядок R1 и 3L,1E,4O не важен.
  EXPECT_CALL(mock, Receive(_, _))
      .InSequence(main, retries)
      .WillOnce(MockReceive("0H"))
      // .WillOnce(MockReceive("1E"))  <-- намеренно потерян!
      .WillOnce(MockReceive("2L"));
  EXPECT_CALL(mock, Send(StrEq("R1"), Eq(3u)))
      .InSequence(retries)
      .RetiresOnSaturation();
  EXPECT_CALL(mock, Receive(_, _))
      .InSequence(main)
      .WillOnce(MockReceive("3L"))
      .WillOnce(MockReceive("1E"))  // <-- ответ на запрос R1
      .WillOnce(MockReceive("4O"));

  char buff[10] = {};
  size_t size;
  ReliableUdpChannel channel(&mock);

  const char *expectations[] = {"H", "E", "L", "L", "O"};
  for (size_t i = 0; i < ARRAY_SIZE(expectations); i++) {
    size = sizeof(buff);
    int attempts = 20;

    while (!channel.Receive(buff, &size) && --attempts > 0) {
    }

    ASSERT_GT(attempts, 0) << "Too many Receive attempts, aborting";
    ASSERT_STREQ(expectations[i], buff);
  }
}

// TODO(timurrrr): random Receive==false tests
// TODO(timurrrr): packets reordered test

// TODO(timurrrr): Tests for Send()

class FakeUdpChannel : public UdpChannel {
 public:
  virtual void Send(const char *buffer, size_t size) {
    // TODO(timurrrr): make packet loss adjustable
    if (random_.Generate<int>() % 6 == 0)
      return;
    NOT_IMPLEMENTED;
  }
  virtual bool Receive(char *buffer, size_t *size) {
    NOT_IMPLEMENTED;
  }

 private:
  RandomGenerator random_;
  /* TODO:
     std::queue<> 
     */
};

// TODO(timurrrr): write a test sending 100K of data over a lossy FakeUdpChannel
// and make sure the other end receives it all.
