#!/usr/bin/python

# Code is executed top-to-bottom on load.

# Variables are defined at the first assignment
a = 2  # defines `a`
b = 2

# 'print' operator, simple form: just prints out human-readable representation
# of the argument. NOTE: no \n!
print a + b

# Types in Python are dynamic!
v = 42  # `v` is an integer
print v
v = 0.42  # now it's a float
print v
v = 2**76  # NEW: Loooong integers are supported!
print v
v = 4 + 0.2j  # NEW: complex numbers!
print v
v = "almost but not quite entirely unlike tea"  # now it's a string
print v

# 'print' operator, full form.
print "%d %.1f %s" % (42, 4.2, "forty two")
# non-optimal equivalent:
print str(42) + " " + str(4.2) + " forty two"
