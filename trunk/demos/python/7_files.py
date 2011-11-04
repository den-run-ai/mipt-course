#!/usr/bin/python

# http://docs.python.org/library/stdtypes.html#file-objects

f1 = open("1.txt","r") # opening modes are the same as in C/C++ stdio
f2 = open("2.txt","w")
for line in f1:
    print line

f2.write("Sample string")

print f2.tell() # position in the file
f2.seek(0) # go to the beginning of file
print f2.tell() # and see the result of 'seek'

f1.close() # you should close files. GC cannot do it
f2.close()
