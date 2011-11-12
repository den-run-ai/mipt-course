# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import copy
import hashlib
import logging
import os
import random
import re
import sys
import Queue # Renamed to queue in 3.0
import unittest

class FakeDHT:
  # This is a fake DHT, see http://en.wikipedia.org/wiki/Distributed_hash_table
  def __init__(self):
    self.__table = {}

  # O(log N)
  #
  # TODO(timurrrr): in fact, we don't need a precise set for a given key,
  # a non-empty subset of the most recent machines would work.
  # This can also automatically fix the abscence of Remove()
  def Append(self, key, new_values):
    # will raise exception if 'values' is not a sequence
    logging.debug("FakeDHT.Append('%s', '%s')", key, new_values)
    if key not in self.__table.keys():
      self.__table[key] = new_values
    else:
      self.__table[key].extend(new_values)

  # O(log N)
  def Get(self, key):
    ret = self.__table[key]
    logging.debug("FakeDHT.Get('%s') returns '%s'", key, ret)
    return ret


class FakeP2PNetwork:
  def __init__(self):
    # will contain (key -> (receive queue) pairs
    # where receive queue holds list of (sender_id, message) pairs.
    self.__nodes = {}
    self.__availableIDs = set(["Alice", "Brian", "Colin", "David", "Ellie"])

  # Returns new node ID
  def CreateNode(self):
    new_id = random.choice(list(self.__availableIDs))
    self.__availableIDs.remove(new_id)
    self.__nodes[new_id] = Queue.Queue()
    logging.info("New node: %s" % new_id)
    return new_id

  # Returns True on success, False on failure
  # Design flaw: we can use other node's ID as sender_id
  # TODO(timurrrr): FakeSocket
  def Send(self, sender_id, to_id, message):
    assert sender_id in self.__nodes.keys()

    if to_id not in self.__nodes.keys():
      logging.error("'%s' node is unknown" % to_id)
      return False
    self.__nodes[to_id].put((sender_id, copy.deepcopy(message)))

    return True

  # Returns (from, message) pair if present (FIFO), None if no messages are
  # available.
  # Design flaw: we can use other node's ID as receiver_id
  def Receive(self, receiver_id):
    if self.__nodes[receiver_id].empty():
      return None
    return self.__nodes[receiver_id].get()


class TorrentID:
  CHUNK_SIZE = 4

  def __init__(self, contents):
    # contents should be a string
    self.length = len(contents)
    self.filehash = hashlib.sha1(contents).hexdigest()
    self.partial_hashes = []
    for chunk_id in range(self.length / TorrentID.CHUNK_SIZE + 1):
      ph = self.__CalculatePartialHash(contents, chunk_id)
      if ph != None:
        self.partial_hashes.append(ph)
    logging.info("Created torrent:\nContents='%s'\n%s" % (contents, str(self)))

  # implicitly called by str(torrent_id)
  def __str__(self):
    return "Torrent:\n  hash=%s\n  size=%d\n  partial_hashes=[\n   %s\n  ]\n" % (
           self.filehash, self.length, ",\n   ".join(self.partial_hashes))

  @staticmethod
  def GetChunkData(contents, chunk_id):
    return contents[chunk_id * TorrentID.CHUNK_SIZE :
                (chunk_id+1) * TorrentID.CHUNK_SIZE]

  @staticmethod
  def SetChunkData(contents, chunk_id, new_data):
    idx_l = chunk_id * TorrentID.CHUNK_SIZE
    idx_r = idx_l + TorrentID.CHUNK_SIZE
    return contents[:idx_l] + new_data + contents[idx_r:]

  @staticmethod
  def GetChunkHash(chunk_data):
    return hashlib.sha1(chunk_data).hexdigest()

  @staticmethod
  def __CalculatePartialHash(contents, chunk_id):
    chunk = TorrentID.GetChunkData(contents, chunk_id)
    if len(chunk) > 0:
      return TorrentID.GetChunkHash(chunk)
    return None

  def IsKnownChunk(self, contents, chunk_id):
    return self.__CalculatePartialHash(contents, chunk_id) \
            == self.partial_hashes[chunk_id]


class TorrentClient:
  def __init__(self, network, dht):
    self.__network = network
    self.__id = network.CreateNode()

    # Will store (<chunk>_key -> set(machines which know <chunk>)
    self.__dht = dht

    # Torrent hash -> (torrent, contents) dictionary.
    # 'contents' should contain '*' for unknown bytes (TODO: this is a hack)
    self.__data = {}

    # Torrents to be downloaded
    # (torrent hash -> set of missing chunk indices)
    self.__partial_torrents = {}

    # List of finished-but-not-taken torrent hashes
    self.__downloaded = []

  def GetDownloadedTorrent(self):
    # Peek and return any downloaded torrent as a (torrent, contents) tuple
    # (if present), otherwise None.
    if len(self.__downloaded) == 0:
      return None
    ret_hash = self.__downloaded[-1]
    self.__downloaded = self.__downloaded[:-1]
    return self.__data[ret_hash]

  @staticmethod
  def __ChunkKey(torrent, chunk_id):
    assert chunk_id in range(len(torrent.partial_hashes))
    return "chunk_%s_%d" % (torrent.filehash, chunk_id)

  def AddTorrent(self, torrent, known_contents=None):
    assert torrent.filehash not in self.__data.keys()
    if known_contents:
      for chunk in range(len(torrent.partial_hashes)):
        self.__dht.Append(self.__ChunkKey(torrent, chunk), [self.__id])
      print "%s: Loaded torrent   '%s'" % (self.__id, known_contents)
    else:
      known_contents = "*" * torrent.length
      self.__partial_torrents[torrent.filehash] = \
          set(range(len(torrent.partial_hashes)))

    self.__data[torrent.filehash] = (torrent, known_contents)

  def Tick(self):
    message = self.__network.Receive(self.__id)
    if message:
      self.__ProcessMessage(message)

    if len(self.__partial_torrents.keys()) > 0:
      # Select random a torrent to download a chunk
      filehash = random.choice(self.__partial_torrents.keys())
      torrent = self.__data[filehash][0]

      # ... random chunk
      needed_chunks = self.__partial_torrents[filehash]
      chunk = random.choice(list(needed_chunks))
      chunk_key = self.__ChunkKey(torrent, chunk)

      # ... random host
      chunk_available_at = random.choice(self.__dht.Get(chunk_key))

      # Ask the host to send the chunk of that torrent
      self.__network.Send(self.__id, chunk_available_at, "give_" + chunk_key)

  def __ProcessMessage(self, msg):
    (from_id, contents) = msg
    logging.debug("Node '%s' received a message '%s' from '%s'",
                  self.__id, contents, from_id)
    m = re.match("give_chunk_([0-9a-f]+)_([0-9]+)", contents)
    if m:
      # Process "give_chunk_<hash>_<chunk>" message
      (filehash, chunk_id) = m.groups()
      if filehash not in self.__data.keys():
        logging.error("Hey, I don't know such a torrent!")
        return
      chunk_id = int(chunk_id)
      (torrent, contents) = self.__data[filehash]
      if not torrent.IsKnownChunk(contents, chunk_id):
        logging.error("Hey, I don't have this chunk!")
        logging.info("Current torrent contents are:\n  '%s'" % contents)
        return
      chunk_key = self.__ChunkKey(torrent, chunk_id)
      chunk_data = TorrentID.GetChunkData(contents, chunk_id)
      self.__network.Send(self.__id, from_id,
                          "take_%s %s" % (chunk_key, chunk_data))
      return

    m = re.match("take_chunk_([0-9a-f]+)_([0-9]+) (.*)", contents)
    if not m:
      logging.error("Couldn't parse this message '%s'", msg)
      return

    # Process "take_chunk_<hash>_<chunk> <contents>" message
    (filehash, chunk_id, chunk_data) = m.groups()
    chunk_id = int(chunk_id)
    if filehash not in self.__partial_torrents.keys():
      logging.info("Hey, I didn't want this torrent!")
      return
    needed_chunks = self.__partial_torrents[filehash]

    (torrent, known_contents) = self.__data[filehash]

    if chunk_id not in needed_chunks:
      logging.info("%s: Hey, I didn't want this chunk! %d not in %s" % \
                   (self.__id, chunk_id, str(needed_chunks)))
      logging.info("Current torrent contents are:\n  '%s'" % known_contents)
      return

    if torrent.GetChunkHash(chunk_data) != torrent.partial_hashes[chunk_id]:
      logging.error("Hash mismatch!")  # Call security?
      return

    known_contents = torrent.SetChunkData(known_contents, chunk_id, chunk_data)
    self.__data[filehash] = (torrent, known_contents)
    print "%s: New contents are '%s'" % (self.__id, known_contents)

    needed_chunks.remove(chunk_id)
    chunk_key = self.__ChunkKey(torrent, chunk_id)
    self.__dht.Append(chunk_key, [self.__id])

    if len(needed_chunks) == 0:
      logging.info("Torrent #%s download finished!" % filehash)
      self.__downloaded.append(filehash)
      self.__partial_torrents.pop(filehash)
      return


class TorrentDhtDemoTest(unittest.TestCase):
  def runTest(self):
    print  # ugly hack to force a newline

    myfile = "AAAABBBBCCCCDDDDEEEEFF"
    mytorrent = TorrentID(myfile)

    network = FakeP2PNetwork()
    dht = FakeDHT()

    clients = []
    for i in range(3):
      clients.append(TorrentClient(network, dht))
      if i == 0:  # Seeder
        clients[i].AddTorrent(mytorrent, myfile)
      else:  # others
        clients[i].AddTorrent(mytorrent)

    received_file = None
    while not received_file:
      for c in clients:
        c.Tick()  # Simulate parallel execution
      received_file = clients[1].GetDownloadedTorrent()

    self.assertEqual(received_file[0], mytorrent)
    self.assertEqual(received_file[1], myfile)


# Run the test suite.
if __name__ == '__main__':
  # replace ERROR with INFO, DEBUG, etc. and re-run. Notice any changes?
  logging.basicConfig(stream=sys.stdout,
                      level=logging.ERROR,  # Don't print anything less serious
                      format="%(asctime)s [%(levelname)s] %(message)s")
  unittest.main(testRunner=unittest.TextTestRunner(verbosity=2))
