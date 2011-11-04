#!/usr/bin/python

l = range(0, 10)

# NEW! Read as in English.
print "Squares of l:\n  %s" % [x*x for x in l]
print "Squares of odd elements of l:\n  %s" % [x*x for x in l if x % 2 == 1]
