#!/usr/bin/python
# -*- coding: utf-8 -*-

# Regular expressions
# http://docs.python.org/2.7/library/re.html
# http://rgruet.free.fr/PQR27/PQR2.7.html#reModule
import re

my_string = "Vasya Pupkin, 666"

m = re.match("([a-zA-Z]+) ([a-zA-Z]+), ([0-9]+)", my_string)
if m:
  name, surname, group = m.groups()  # Множественное присваивание!
  print "Student's name is '%s', surname is '%s', group is '%s'" % \
        (name, surname, group)
else:
  print "No match?"

# Демо именованных матч-групп:
m = re.match("(?P<Name>[a-zA-Z]+) (?P<Surname>[a-zA-Z]+), (?P<Group>[0-9]+)", \
             my_string)
if m:
  print "'Surname' named match group value is %s" % m.group("Surname")
else:
  print "No match?"
