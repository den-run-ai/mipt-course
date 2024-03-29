#!/usr/bin/python

# Dictionaries.
# http://rgruet.free.fr/PQR27/PQR2.7.html#dictionary

d = {}  # create an unordered dictionary
d['abc'] = 8
d[1.6] = 'lol'  # yes, keys may be of different types

print d  # python can print dictionaries in readable format

del d['abc']  # remove an element

if 42 in d:  # is there key=42 in 'd'
  print d[42]

d2 = {
  'odd': [1, 3, 5, 7, 9],
  'even': [2, 4, 6, 8],  # last comma is optional but
                         # it's usually better to write it.
}

print "Фамилия %(FirstName)s - %(Surname)s" % {
          "Surname": "Pupkin",
          "FirstName": "Vasya",
      }

# Sets.
# http://rgruet.free.fr/PQR27/PQR2.7.html#set
s = set()  # create an unordered set
s.add(9)
s.add('cde')
s.add(1.8)
print s  # set is also printable in readable format
print 9 in s  # True
print 'CDE' in s  # False

t = {5, 8, 9, 90}
t = set([5, 8, 9, 90])  # an old way (2.6) to create a set
print t
print t & s  # set intersection
print t | s  # set union
