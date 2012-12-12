# Copyright (c) 2012 Timur Iskhodzhanov and MIPT students. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import math
import operator
import unittest
import re


class Token(object):

    def to_test_string(self):
        return str(self)


class Value(Token):

    def __init__(self, value):
        self.value = value

    def __str__(self):
        return str(self.value)


class Bracket(Token):

    def __init__(self, is_opening):
        self.is_opening = is_opening

    def __str__(self):
        return '(' if self.is_opening else ')'


class Operation(Token):
    pass


class UnaryOperation(Operation):

    def __init__(self, name, is_postfix, func):
        """Create UnaryOperation Token.

        Args:
            name:       operation name (e.g. '+' or '-')
            is_postfix: True if this is postfix operation, False if prefix
            func:       the function itself
                (a callable object which evaluates this operation)
        """
        self.name = name
        self.is_postfix = is_postfix
        self.func = func

    def evaluate(self, arg):
        return self.func(arg)

    def to_test_string(self):
        if self.name in ['+', '-']:
            return 'u%s' % self.name
        else:
            return str(self)

    def __str__(self):
        return self.name


class BinaryOperation(Operation):

    def __init__(self, name, priority, is_right_assoc, func):
        """Create BinaryOperation Token.

        Args:
            name: operation name
            priority: operation priority
            is_right_assoc: True if right associative, False otherwise
                Left-associativity is like this: a-b-c = (a-b)-c.
                Right-associativity is like this: a^b^c = a^(b^c).
            func: the function itself
        """
        self.name = name
        self.priority = priority
        self.is_right_assoc = is_right_assoc
        self.func = func

    def evaluate(self, arg1, arg2):
        return self.func(arg1, arg2)

    def __str__(self):
        return self.name


class Evaluator(object):

    functions = {
        'sqrt': math.sqrt,
        'sin': math.sin,
        'cos': math.cos,
        'abs': abs,
    }

    # 4-tuples: (name, priority, right associativity, func)
    binary_ops = {
        '+': ('+', 4, False, operator.add),
        '-': ('-', 4, False, operator.sub),
        '*': ('*', 5, False, operator.mul),
        '/': ('/', 5, False, operator.div),
        '^': ('^', 6, True, operator.pow),
    }

    # 3-tuples: (name, is postfix, func)
    unary_ops = {
        '+': ('+', False, lambda x: x),
        '-': ('-', False, operator.neg),
    }

    def __tokenize_to_str(self, expr_str):
        """Splits expr_str into tokens as strings.

        It's a helper function for __tokenize.
        Raises ValueError exception on format errors.
        A token is one of the following:
         * a continuous sequence of letters, may include underscores
         * a continuous sequence of decimal digits, may include dots
         * one of the following symbols: ()+-*/^

        Args:
            self: instance of the Evaluator class
            expr_str: arithmetic expression as a string

        Returns:
            A list of string tokens from given expr_str

        Raises:
            ValueError: invalid expr_str, which is impossible to tokenize
        """
        token_exprs = [
            '[a-zA-Z_0-9.]+',  # numbers, functions, variables
            '[()+\\-*/^]',     # operators and brackets
        ]
        tokens_str = re.findall('|'.join(token_exprs), expr_str)
        if not ''.join(tokens_str) == expr_str.replace(' ', ''):
            raise ValueError('invalid arithmetic expression')

        return tokens_str

    def __tokenize(self, expr_str):
        """Splits expr_str into tokens.

        Args:
            self: instance of the Evaluator class
            expr_str: arithmetic expression as a string

        Returns:
            A list of tokens from given expr_str

        Raises:
            ValueError: invalid expr_str, which is impossible to tokenize
                or tokens themselves are invalid
                (e.g. 1.0.0 isn't a number, foobar isn't a known function)
        """
        tokens_str = self.__tokenize_to_str(expr_str)

        tokens = []

        for i, token_str in enumerate(tokens_str):
            prev = tokens_str[i - 1] if i > 0 else None

            is_unary = (prev is None or
                        prev == '(' or
                        prev in (self.binary_ops.keys() +
                                 self.unary_ops.keys() +
                                 self.functions.keys()))

            token = None
            if re.match('[0-9.]+', token_str):
                token = Value(float(token_str))
            elif token_str in self.functions:
                token = UnaryOperation(
                    token_str,
                    False,
                    self.functions[token_str])
            elif token_str in self.unary_ops and is_unary:
                token = UnaryOperation(*self.unary_ops[token_str])
            elif token_str in self.binary_ops:
                token = BinaryOperation(*self.binary_ops[token_str])
            elif token_str == '(':
                token = Bracket(True)
            elif token_str == ')':
                token = Bracket(False)
            else:
                raise ValueError('invalid token "%s"' % token_str)

            tokens.append(token)

        return tokens

    def __to_postfix(self, tokens):
        """Translates a string of tokens from infix form to postfix.

        Args:
            tokens: list of tokens representing expression in infix form

        Returns:
            List of the same tokens, reordered to form a postfix expression.
        """

        # helper function
        def peek(stack):
            return stack[-1] if stack else None

        stack = []
        res = []
        for token in tokens:
            if isinstance(token, Value):
                # Got an operand - append it to the result.
                res.append(token)
            elif isinstance(token, UnaryOperation) and token.is_postfix:
                # Got an unary postfix operation - append it to the result.
                res.append(token)
            elif isinstance(token, UnaryOperation) and not token.is_postfix:
                # Got an unary prefix operation (or function) -
                # push it onto the stack.
                stack.append(token)
            elif isinstance(token, BinaryOperation):
                # Got a binary operation - pop off from stack and push it there.
                # Popping off while priority is higher or equal
                # for left-associative operations,
                # or while strictly higher for right-associative ones.
                # Unaries are always treated as higher-priority operations.

                if token.is_right_assoc:
                    priority_cond = operator.gt
                else:
                    priority_cond = operator.ge

                while (isinstance(peek(stack), UnaryOperation) or
                       (isinstance(peek(stack), BinaryOperation) and
                        priority_cond(peek(stack).priority, token.priority))):
                    # pop off the element and append to the result
                    res.append(stack.pop())

                # push the token onto the stack
                stack.append(token)
            elif isinstance(token, Bracket) and token.is_opening:
                # Got an opening bracket - push it onto the stack.
                stack.append(token)
            elif isinstance(token, Bracket) and not token.is_opening:
                # Got a closing bracket -
                # pop operators off the stack and append to the result
                # while the top of the stack isn't an opening bracket.

                while (stack and
                       not (isinstance(peek(stack), Bracket) and
                            peek(stack).is_opening)):
                    res.append(stack.pop())

                # then pop the opening bracket
                stack.pop()

                # If the top of the stack is an unary prefix op,
                # pop it and append to the result.
                if (isinstance(peek(stack), UnaryOperation) and
                    not peek(stack).is_postfix):
                    res.append(stack.pop())

        while stack:
            res.append(stack.pop())

        return res

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
            self.eval('(13/(-11+145))^1.3'),
            (13.0 / (-11 + 145)) ** 1.3)
        self.assertAlmostEqual(self.eval('2.44 ^ (-1.3)'), 2.44 ** (-1.3))

    @unittest.skip('not implemented yet')
    def test_space_ignorance(self):
        self.assertAlmostEqual(
            self.eval('   -  11 +sqrt(  sin( (   13 /(-  11 + 145))  ^1.3))'),
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

    def test_postfix(self):
        def to_postfix(expr_str):
            r = self.evaluator._Evaluator__to_postfix(
                    self.evaluator._Evaluator__tokenize(expr_str))
            return map(lambda t: re.sub('.0$', '', t.to_test_string()), r)

        self.assertEqual(to_postfix('4'), ['4'])
        self.assertEqual(to_postfix('--4'), ['4', 'u-', 'u-'])
        self.assertEqual(to_postfix('+-4'), ['4', 'u-', 'u+'])
        self.assertEqual(to_postfix('-+4'), ['4', 'u+', 'u-'])
        self.assertEqual(to_postfix('-4'), ['4', 'u-'])
        self.assertEqual(to_postfix('+4'), ['4', 'u+'])
        self.assertEqual(
            to_postfix('+(5+8)-4'),
            ['5', '8', '+', 'u+', '4', '-'])
        self.assertEqual(
            to_postfix('-(+1-2)+4'),
            ['1', 'u+', '2', '-', 'u-', '4', '+'])
        self.assertEqual(
            to_postfix('3+4*5/6'),
            ['3', '4', '5', '*', '6', '/', '+'])
        self.assertEqual(to_postfix(
            '(300+23)*(43-21)/(84+7)'),
            ['300', '23', '+', '43', '21', '-', '*', '84', '7', '+', '/'])
        self.assertEqual(to_postfix(
            '(4+8)*(6-5)/((3-2)*(2+2))'),
            ['4', '8', '+', '6', '5', '-', '*', '3', '2', '-', '2', '2', '+',
             '*', '/'])
        self.assertEqual(to_postfix(
            '3+4*2/(1-5)^5^10'),
            ['3', '4', '2', '*', '1', '5', '-', '5', '10', '^', '^', '/', '+'])
        self.assertEqual(to_postfix('-5-4'), ['5', 'u-', '4', '-'])
        self.assertEqual(to_postfix('-5+4'), ['5', 'u-', '4', '+'])
        self.assertEqual(to_postfix('1^(2^3)'), ['1', '2', '3', '^', '^'])
        self.assertEqual(to_postfix('(1^2)^3'), ['1', '2', '^', '3', '^'])
        self.assertEqual(to_postfix('1^2^3'), ['1', '2', '3', '^', '^'])
        self.assertEqual(to_postfix('sin 2'), ['2', 'sin'])
        self.assertEqual(to_postfix('sin(2)'), ['2', 'sin'])
        self.assertEqual(
            to_postfix('sin(45)+cos 15'),
            ['45', 'sin', '15', 'cos', '+'])
        self.assertEqual(
            to_postfix('2+sin 30'),
            ['2', '30', 'sin', '+'])
        self.assertEqual(
            to_postfix('2+sin 30'),
            ['2', '30', 'sin', '+'])
        self.assertEqual(
            to_postfix('sin 30 + 2'),
            ['30', 'sin', '2', '+'])
        self.assertEqual(
            to_postfix('sin(30+2)'),
            ['30', '2', '+', 'sin'])
        self.assertEqual(to_postfix('abs -4'), ['4', 'u-', 'abs'])
        self.assertEqual(
            to_postfix('sin 10 + cos 20 + abs -5'),
            ['10', 'sin', '20', 'cos', '+', '5', 'u-', 'abs', '+'])
        self.assertEqual(
            to_postfix('sin(25)+cos(15+sin(45))+3'),
            ['25', 'sin', '15', '45', 'sin', '+', 'cos', '+', '3', '+'])

    def test_tokenize(self):
        def tokenize(expr_str):
            r = self.evaluator._Evaluator__tokenize(expr_str)
            return map(lambda t: re.sub('.0$', '', str(t)), r)

        tokenize_to_str = self.evaluator._Evaluator__tokenize_to_str

        for tok_func in [tokenize_to_str, tokenize]:
            self.assertEqual(tok_func('0'), ['0'])
            self.assertEqual(tok_func('0'), ['0'])
            self.assertEqual(tok_func('10.32423'), ['10.32423'])
            self.assertEqual(tok_func('-11'), ['-', '11'])
            self.assertEqual(tok_func('+11'), ['+', '11'])
            self.assertEqual(
                tok_func('abs(-3.333)'),
                ['abs', '(', '-', '3.333', ')'])
            self.assertEqual(
                tok_func('113/41-5*11'),
                ['113', '/', '41', '-', '5', '*', '11'])
            self.assertEqual(
                tok_func(' -  11 +sqrt(  sin( (   13 /(-  11 + 145))  ^1.3))'),
                ['-', '11', '+', 'sqrt', '(', 'sin', '(', '(', '13', '/', '(',
                 '-', '11', '+', '145', ')', ')', '^', '1.3', ')', ')'])

            self.assertRaisesRegexp(
                ValueError,
                'invalid arithmetic expression',
                tok_func, '!";%:?=#@$&')
            self.assertRaisesRegexp(
                ValueError,
                'invalid arithmetic expression',
                tok_func, '2 " 2')

        # these tests are for tokenize function only
        self.assertRaisesRegexp(
            ValueError,
            'invalid literal for float()',
            tokenize,
            '2.2.2')
        self.assertRaisesRegexp(
            ValueError,
            'invalid literal for float()',
            tokenize,
            '5x')
        self.assertRaisesRegexp(
            ValueError,
            'invalid token',
            tokenize,
            'foobar 5 + 3')
        self.assertRaisesRegexp(
            ValueError,
            'invalid token',
            tokenize,
            'sinx')
        self.assertRaisesRegexp(
            ValueError,
            'invalid token',
            tokenize,
            'sin41')
        self.assertRaisesRegexp(
            ValueError,
            'invalid token',
            tokenize,
            'foobar 5 + 3')


if __name__ == '__main__':
    unittest.main(testRunner=unittest.TextTestRunner(verbosity=2))
