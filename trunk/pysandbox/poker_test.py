#!/usr/bin/python
# -*- coding: utf-8 -*-

# Copyright (c) 2011 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

#------------------------------------------------------------------------------
# This module implements and tests functionality of some entities in poker game
# f.e. Card, Rank, Suit, Hand, Value of Hand
#------------------------------------------------------------------------------
# Suit class encapsulates information about card suit:
#     's' stands for 'Spades'   ♠
#     'c' stands for 'Clubs'    ♣
#     'd' stands for 'Diamonds' ♦
#     'h' stands for 'Hearts'   ♥
#------------------------------------------------------------------------------
# Rank class encapsulates information about card rank, and some methods for its
# creating, comparing and so on:
#     '2'  stands for 'Deuce'
#     '3'  stands for 'Three'
#     '4'  stands for 'Four'
#     '5'  stands for 'Five'
#     '6'  stands for 'Six'
#     '7'  stands for 'Seven'
#     '8'  stands for 'Eight'
#     '9'  stands for 'Nine'
#     '10' stands for 'Ten'
#     'J'  stands for 'Jack'
#     'Q'  stands for 'Queen'
#     'K'  stands for 'King'
#     'A'  stands for 'Ace'
#------------------------------------------------------------------------------

import collections
import unittest


class CardSuitTest(unittest.TestCase):
    """Tests Suit class."""

    def test_suit_equality(self):
        """Testing Suit's == operator usage."""
        self.assertEqual(Suit('s'), Suit('s'))
        self.assertEqual(Suit('c'), Suit('c'))
        self.assertEqual(Suit('d'), Suit('d'))
        self.assertEqual(Suit('h'), Suit('h'))

    def test_suit_inequality(self):
        """Testing Suit's != operator usage."""
        self.assertNotEqual(Suit('s'), Suit('c'))
        self.assertNotEqual(Suit('d'), Suit('h'))
        self.assertNotEqual(Suit('h'), Suit('s'))
        self.assertNotEqual(Suit('c'), Suit('d'))


class CardRankTest(unittest.TestCase):
    """Tests Rank class."""

    def test_rank_equality(self):
        """Testing Rank's == operator usage."""
        self.assertEqual(Rank('2'), Rank('2'))
        self.assertEqual(Rank('10'), Rank('10'))
        self.assertEqual(Rank('J'), Rank('J'))
        self.assertEqual(Rank('A'), Rank('A'))

    def test_rank_inequality(self):
        """Testing Rank's != operator usage."""
        self.assertNotEqual(Rank('3'), Rank('K'))
        self.assertNotEqual(Rank('7'), Rank('4'))
        self.assertNotEqual(Rank('Q'), Rank('9'))
        self.assertNotEqual(Rank('8'), Rank('5'))

    def test_rank_comparison(self):
        """Testing Rank's <, >, <=, >= operators usage."""
        self.assertTrue(Rank('2') < Rank('3'))
        self.assertTrue(Rank('7') <= Rank('10'))
        self.assertTrue(Rank('8') > Rank('5'))
        self.assertTrue(Rank('K') >= Rank('Q'))


class Suit(object):
    """Contains information about card's suit.

    Attributes:
      Class:
        suit_tuple: Named tuple, containing suit's name shortname and sign.
        suits: Tuple of four suit_tuples, one for each card suit.
        shortnames: List of card suit shortnames.
      Instance:
        suit_index: An index of current Suit class instance in suits tuple.
        fullname: String, full name of suit: f.e. 'Spades'.
        shortname: String, shortname of suit: f.e. 's'.
        sign: String, suit sign, f.e. '♠'.
    """

    suit_tuple = collections.namedtuple('suit_tuple', 'fullname shortname sign')

    suits = (suit_tuple('Spades', 's', '♠'),
             suit_tuple('Clubs', 'c', '♣'),
             suit_tuple('Diamonds', 'd', '♦'),
             suit_tuple('Hearts', 'h', '♥'))

    shortnames = [suit_tuple.shortname for suit_tuple in suits]

    def __init__(self, shortname):
        """Inits Suit with a suit shortname.

        Args:
          shortname: String with suit shortname: f.e. 's', 'c', 'd', 'h'.
        """
        assert shortname in Suit.shortnames, \
            "Can't make an instance of Suit({0})".format(shortname)
        self.suit_index = Suit.shortnames.index(shortname)                

    def __str__(self):
        return Suit.suits[self.suit_index].fullname

    def __eq__(self, other):
        return self.suit_index == other.suit_index

    @property
    def fullname(self):
        """Name of a suit: f.e. 'Clubs'."""
        return Suit.suits[self.suit_index].fullname

    @property
    def shortname(self):
        """Shortname of a suit: f.e. 'c' for clubs."""
        return Suit.suits[self.suit_index].shortname

    @property
    def sign(self):
        """Sign of a suit: f.e. '♣' for clubs."""
        return Suit.suits[self.suit_index].sign


class Rank(object):
    """Contains information about card's rank.

    Attributes:
      Class:
        rank_tuple: Named tuple, containing card rank's name and shortname.
        ranks: Tuple of rank_tuples, one for each card rank.
        shortnames: List of card rank shortnames.
      Instance:
        rank_index: An index of current Rank class instance in ranks tuple.
        fullname: String, full name of rank: f.e. 'Ace'.
        shortname: String, shortname of rank: f.e. 'A'.
    """

    rank_tuple = collections.namedtuple('rank_tuple', 'fullname shortname')

    ranks = (rank_tuple('Deuce', '2'),
             rank_tuple('Three', '3'),
             rank_tuple('Four', '4'),
             rank_tuple('Five', '5'),
             rank_tuple('Six', '6'),
             rank_tuple('Seven', '7'),
             rank_tuple('Eight', '8'),
             rank_tuple('Nine', '9'),
             rank_tuple('Ten', '10'),
             rank_tuple('Jack', 'J'),
             rank_tuple('Queen', 'Q'),
             rank_tuple('King', 'K'),
             rank_tuple('Ace', 'A'))

    shortnames = [rank_tuple.shortname for rank_tuple in ranks]

    def __init__(self, shortname):
        """Inits Rank with a rank shortname.

        Args:
          shortname: String with rank shortname: f.e. '2', '3', '10', 'K', 'A'.
        """
        assert shortname in Rank.shortnames, \
            "Can't make an instance of Rank({0})".format(shortname)
        self.rank_index = Rank.shortnames.index(shortname)

    def __str__(self):
        return Rank.ranks[self.rank_index].fullname

    @property
    def fullname(self):
        """Name of a card rank: f.e. 'Deuce'."""
        return Rank.ranks[self.rank_index].fullname

    @property
    def shortname(self):
        """Shortname of a card rank: f.e. '2'."""
        return Rank.Ranks[self.rank_index].shortname

    def __eq__(self, other):
        return self.rank_index == other.rank_index

    def __lt__(self, other):
        return self.rank_index < other.rank_index

    def __le__(self, other):
        return self.rank_index <= other.rank_index

if __name__ == '__main__':
    unittest.main(testRunner=unittest.TextTestRunner(verbosity=2))
