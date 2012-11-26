#!/usr/bin/python

# Lists != arrays!
# http://rgruet.free.fr/PQR27/PQR2.7.html#list

l = [1, 2, 3, 4, 5]  # create a list
print "l = %s; length = %d" % (l, len(l))  # len = get length

# NEW! Slices!
print "l[0:2] = %s" % l[0:2]  # COPY the [0,2) part of the list (half-interval)
print "l[:3]  = %s" % l[:3]   # the left part of the slice defaults to 0
print "l[2:]  = %s" % l[2:]   # the right part of the slice defaults to "the end"
print "l[:-2] = %s" % l[:-2]  # negative indices are counted from the end

l[2] = 42  # change the value of an element

# CAUTION! Python variables are references
l2 = l
l2[0] = 13  # changes l[0] as well!
print "after l2[0] = 13, l = %s" % l

real_copy_of_l = l[:]  # create a copy of the list
l[0] = 1
l[2] = 3
print "l = %s, real_copy_of_l = %s" % (l, real_copy_of_l)

# Also:
l[4] = [7,8,9]  # list elements can store any type, including lists
l[4].append(10)  # add 10 to the end of 'l'.
print "l = %s" % l

# Repeat a list N times:
print "l * 5 = %s" % (l * 5)

m = range(10)  # built-in function generates [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print m

print

# EXCERCISE!
array_2d = [[0]*10]*10  # two-dimentional array.. beware of this construction.
for line in array_2d:
    print line
array_2d[5][4] = 7
print "\narray_2d[5][4] = 7"
for line in array_2d:
    print line
# See what's printed and try to explain?
# How to fix?
