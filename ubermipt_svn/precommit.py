#!/usr/bin/python
# vim:set ts=4 sw=4 sts=4 expandtab:

# pre-commit hook
# This pre-commit hook is invoked to check the file size of any new
# files added in a commit. If there's a file who's size is larger
# than the allowed limit, the script will return a non-zero value
#
# This script gets two parameters:
#       [1] REPOS-PATH (the path to the repository)
#       [2] TXN-NAMED  (the name of the txn about to be committed)

import optparse
import sys

# sudo apt-get install python-svn
import pysvn

# maximum size of allowed files in kilobytes
MAX_SIZE_IN_KB = 100

# This is the error message to display users if they try to commit
# a file whose size is bigger than the maximum allowed
error_msg = ("""
--------------------------------------------------------------------------------
COMMIT HAS BEEN ABORTED!
You are trying to commit a file larger than the max allowed size (""" +
str(MAX_SIZE_IN_KB) + """KB).
Usually this happens when uploading .exe/.suo/.pdb/.class/etc files by mistake.
Please email timurrrr+miptsvn@gmail.com if you're not doing any mistakes!

Please check the list of files below for wrong files:""")

def main():
    assert len(sys.argv) == 3
    repos, txn = sys.argv[1:]
    # get the list of changed files and their sizes
    files = get_files(repos, txn)
    # check if there are any files too big
    files_too_big = check_size(files)

    output = 0
    # display error message if necessary
    if files_too_big:
        output = get_error_message(files_too_big)

    return output

# This function returns a dictionary where the keys
# are the names of the files in the commmit and 
# and the values of the dictionary is the size of
# the files in bytes
def get_files(repos_path, txn):
    # start transaction
    transaction = pysvn.Transaction(repos_path, txn)
    changed = transaction.changed()
    # get a list of changed files and their size
    files = {}
    for file,attrs in transaction.changed().iteritems():
        # directories cannot be cat'd
        # if a file is deleted, it's not in the transaction
        if attrs[1] == pysvn.node_kind.file and not attrs[0] == 'D':
            files[file] = len(transaction.cat(file))

    return files

# This function checks the files in the commit
# to make sure that they are not bigger than the
# maximum allowed size.
#
# This function receives as a parameter a dictionary
# where the keys are the filenames and the values
# is the size of the file in bytes
def check_size(changed_files):
    # max allowed size of file
    max_size_bytes = MAX_SIZE_IN_KB * 1024
    files_too_big = {}
    # check files
    for file in changed_files:
        if changed_files[file] > max_size_bytes:
            files_too_big[file] = changed_files[file]

    return files_too_big

# This function returns an error message string
# and the list of files that were bigger than the 
# maximum allowed size
def get_error_message(files_too_big):
    output = error_msg
    for file in files_too_big:
        output = output + "\n" + get_human_readable_size(files_too_big[file]) + "\t" + file
    output += "\n--------------------------------------------------------------------------------"

    return output

# This function receives as a parameter a numeric
# value. It converts the filesize into Kilybotes,
# and Megabyates to make it easier on humans.
def get_human_readable_size(file_size):
    size = 1
    if file_size < 1024:
        # file is less than a Kilobyte
        size = str(file_size) 
    elif file_size < 1024**2:
        # file is less than a Megabyte
        size = str(round(file_size / 1024.0, 1)) + "K"
    elif file_size < 1024**3:
        # file is less than a gigabyte
        size = str(round(file_size / (1024.0**2), 1)) + "M"

    return size

if __name__ == "__main__":
    sys.exit(main())
