#!/usr/bin/python

# Importing modules
# http://docs.python.org/tutorial/modules.html

import math # import all from 'math' to namespace 'math'
from math import pi # import 'pi' from 'math' to current namespace
from math import cos # and once again
from sys import * # import all (public) from 'sys' to current namespace

# Question: difference between "import X" and "from X import *" ?

# Just come examples of usage
print cos(pi)
print math.sin(pi/2)
