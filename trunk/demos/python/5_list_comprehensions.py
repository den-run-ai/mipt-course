#!/usr/bin/python

l = range(0, 10)

# NEW!
# "List comprehensions".

# Read as in English:
# "Generate a list of x*x for each x in l".
squares = [x*x for x in l]
print "Squares of l:\n  %s" % squares

# "Generate a list of x*x for each x in l which is odd".
odd_squares = [x*x for x in l if x % 2 == 1]
print "Squares of odd elements of l:\n  %s" % odd_squares
