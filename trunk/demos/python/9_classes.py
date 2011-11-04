#!/usr/bin/python

class Foo:
    def __init__(self, arg1):
        self.public_field = arg1
        self.__private_field = 42  # note the leading __

    def Method(self, arg1, arg2):  # note the 'self'
        print "arg1 = %d, arg2 = %d" % (arg1, arg2)

    # You can override some stuff like len() and operators
    # but it's a black belt python-fu.

instance = Foo(13)
instance.Method(1, 2)
