#!/usr/bin/python

# http://docs.python.org/library/stdtypes.html#file-objects

f1 = open("8_files.py","r") # opening modes are the same as in C/C++ stdio
for line in f1:
    print line,  # , at the end means "no newline"
f1.close() # you should close files. GC cannot do it sometimes

f2 = open("2.txt","w")
f2.write("Sample string")

print f2.tell() # position in the file
f2.seek(0) # go to the beginning of file
print f2.tell() # and see the result of 'seek'

f2.close()
