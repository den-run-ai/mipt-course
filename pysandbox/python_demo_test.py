# Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import random
import unittest

# Define a single test:
class SimplePythonTest(unittest.TestCase):
  def runTest(self):
    self.assertEqual(2 + 2, 4)

# Define a fixture:
class SimpleFixtureTest(unittest.TestCase):
  def setUp(self):
    self.seq = range(10)

  def tearDown(self):
    pass

  # ... and some tests using this fixture:
  def test_shuffle(self):
    # make sure the shuffled sequence does not lose any elements
    random.shuffle(self.seq)
    self.seq.sort()
    self.assertEqual(self.seq, range(10))

  def test_choice(self):
    element = random.choice(self.seq)
    self.assertTrue(element in self.seq)

  def test_sample(self):
    for element in random.sample(self.seq, 5):
      self.assertTrue(element in self.seq)

# Run the test suite.
if __name__ == '__main__':
  unittest.main(testRunner=unittest.TextTestRunner(verbosity=2))
