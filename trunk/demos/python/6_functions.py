#!/usr/bin/python

# Define a function. It's not called yet.
def Square(x):
    return x * x

# Now call it!
print Square(3)

def foo(x=2, y=3):
    print "foo(x = %d, y = %d)" % (x, y)

print foo()  # x=2, y=3
print foo(4) # x=4, y=3
print foo(5, 6) # x=5, y=6
print foo(y=7) # x=2, y=7  <- NEW

def poor_man_printf(fmt, *args):
    # Operator % substitutes format string with args (similar to C printf)
    print fmt % args # 'args' is a tuple

poor_man_printf("%d %d", 89, 56)

# For the curious - read about kwargs:
# http://stackoverflow.com/questions/1098549/proper-way-to-use-kwargs-in-python

def foo(**kwargs):  # kwargs means "keyworded args"
  # `kwargs` is a dictionary of all extra args.
  # See the 'dictionary' demos later.
  print kwargs

foo(x=42, y=72, name=112, fasdfasdf=1431)
# -------------------------------

# Access to global variables (discouraged)
glob = 42
def change_glob():
    #global glob  # un-comment to use a global var
    #print "glob = %d" % glob
    glob = 13
    print "glob = %d" % glob

change_glob()
print "glob = %d" % glob

# Returns multiple values as a tuple.
# Tuples are like lists but immutable, see
# http://rgruet.free.fr/PQR27/PQR2.7.html#SequenceTypes
def powers(x):
    return (x, x*x, x*x*x)

print "Some powers of 2 are: %s" % str(powers(2))

# NEW! Lambda functions

# You can use function as argument for another function
def Map(array, function):
    # Equivalent to the code below:
    # return [function(element) for element in array] 
    result = []
    for element in array:
        result.append(function(element))
    return result

# Call Map - using other function
print Map(range(0, 5), powers)

# Call Map - using a lambda function
print Map(range(0, 5), lambda x: x*x)

# Closure demo
a = 3
print Map(range(0, 5), lambda x: x**a)

# EXCERCISES:
# 1)
def bad_foo(arg=[]):
    arg.append(42)
    print "arg = %s" % arg

bad_foo([1])
bad_foo([1])
z = [0]
bad_foo(z)
bad_foo(z) # okay, bad_foo changes the argument...
bad_foo()
bad_foo()  # baaaah!

# 2)
def foo2(closure):
    print closure(42)

a = 3
z = lambda x: x + a
a = 4
foo2(z)
