#!/usr/bin/python

condition = 42

# IMPORTANT: colons, _indentation_ are significant!
if condition:
    print "Condition is true!"
elif True:  # not 'true'!
    print "I said it's true! :)"
else:
    print "Condition is false :("
# of course, elif/else are optional

assert True == (not False)

# Equivalent of `for (int i = 0; i < 13; i++) {`
for i in range(0, 13):
    print i,  # "," at the end means "no newline"
print  # newline

while True:
    if condition == 42:
        break
    elif condition == 17:
        continue
    else:
        print "?"
