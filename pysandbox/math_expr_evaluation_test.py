#! /usr/bin/python
# Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import math
import unittest


class Evaluator(object):

    def evaluate(self, expr_str):
        pass


class EvaluatorTest(unittest.TestCase):

    def setUp(self):
        self.evaluator = Evaluator()
        self.eval = self.evaluator.evaluate

    @unittest.skip('not implemented yet')
    def test_constants(self):
        self.assertEqual(self.eval('0'), 0)
        self.assertEqual(self.eval('1'), 1)
        self.assertEqual(self.eval('10.32423'), 10.32423)

    @unittest.skip('not implemented yet')
    def test_unary(self):
        self.assertEqual(self.eval('-1.23'), -1.23)
        self.assertEqual(self.eval('+1.23'), 1.23)

    @unittest.skip('not implemented yet')
    def test_binary(self):
        self.assertEqual(self.eval('0+1'), 0 + 1)
        self.assertEqual(self.eval('11-7'), 11 - 7)
        self.assertEqual(self.eval('11*7'), 11 * 7)
        self.assertAlmostEqual(self.eval('11/7'), 11.0 / 7)
        self.assertEqual(self.eval('25^3'), 25 ** 3)

    @unittest.skip('not implemented yet')
    def test_functions(self):
        self.assertAlmostEqual(self.eval('sqrt(2)'), math.sqrt(2))
        self.assertAlmostEqual(self.eval('sin(3.333)'), math.sin(3.333))
        self.assertAlmostEqual(self.eval('cos(3.333)'), math.cos(3.333))
        self.assertAlmostEqual(self.eval('abs(-3.333)'), 3.333)

    @unittest.skip('not implemented yet')
    def test_multiple(self):
        self.assertEqual(self.eval('7*45+10'), 7 * 45 + 10)
        self.assertAlmostEqual(self.eval('113/41-5*11'), math.sqrt(2))

    @unittest.skip('not implemented yet')
    def test_brackets(self):
        self.assertEqual(self.eval('7*(45+10)'), 7 * (45 + 10))
        self.assertAlmostEqual(
            self.eval('(13/(-11+145))**1.3'),
            (13.0 / (-11 + 145)) ** 1.3)
        self.assertAlmostEqual(self.eval('2.44 ^ (-1.3)'), 2.44 ** (-1.3))

    @unittest.skip('not implemented yet')
    def test_space_ignorance(self):
        self.assertAlmostEqual(
            self.eval('   -  11 +sqrt(  sin( (   13 /(-  11 + 145))  **1.3))'),
            -11 + math.sqrt(math.sin((13.0 / (-11 + 145)) ** 1.3)))

    @unittest.skip('not implemented yet')
    def test_errors(self):
        self.assertRaisesRegexp(
            ValueError,
            'negative number cannot be raised to a fractional power',
            self.eval, '(-2.44) ^ (-1.3)')
        self.assertRaisesRegexp(
            ValueError,
            'math domain error',
            self.eval, 'sqrt(-1)')


if __name__ == '__main__':
    unittest.main(testRunner=unittest.TextTestRunner(verbosity=2))
