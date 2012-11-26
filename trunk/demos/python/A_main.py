#!/usr/bin/python

# EXCERCISE:
# run it from command line:
#   $ python B_main.py
# and then from interactive python shell:
#   $ python
#   >>> import B_main
# and compare the results.

print "Hello, this is B_main.py"

if __name__ == "__main__":
  # __name__ == "__main__" is only set for the "main" module.
  print "You ran `python B_main.py`!"
else:
  print "You've imported me!"
