#!/usr/bin/python

# Importing modules
# http://docs.python.org/tutorial/modules.html

import math  # import all from 'math' to namespace 'math'
print "pi = %f" % math.pi

from math import cos,pi  # import 'math.cos' and 'math.pi' into current namespace
print cos(pi)

from sys import *  # import all (public) names from 'sys' into current namespace

is_windows = False
if is_windows:
  import win_math  # conditional import!

# Question: difference between "import X" and "from X import *" ?
