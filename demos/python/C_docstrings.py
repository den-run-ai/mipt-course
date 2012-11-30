#!/usr/bin/python
# -*- coding: utf-8 -*-

""" Docstring demo.

Запускать так:
$ python
>>> import E_docstrings
>>> help(E_docstrings)
>>> help(E_docstrings.foo)
"""

def foo():
    """ This function has a docstring!
    
    You can write some useful tips here.
    See http://www.python.org/dev/peps/pep-0257/
    for the general docstring guidelines.
    """
    print "Hello"

if __name__ == "__main__":
    foo()
