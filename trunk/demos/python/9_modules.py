#!/usr/bin/python

# Importing modules
# http://docs.python.org/tutorial/modules.html

# import all from 'math' to namespace 'math'
import math
print "pi = %f" % math.pi

# import 'math.cos' and 'math.pi' into current namespace
from math import cos, pi
print cos(pi)

# import all (public) names from 'sys' into current namespace
from sys import *

is_windows = False
if is_windows:
  import win_math  # conditional import - useful for testing!

# EXCERCISE:
# What's the difference between "import X" and "from X import *" ?
