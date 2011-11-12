#!/bin/bash

# don't pay attention to this bash "set" magic.
set -x
set -e

g++ -o hello.obj -c hello.cpp
g++ -o main.obj -c main.cpp
g++ -o world.obj -c world.cpp

g++ -o helloworld hello.obj main.obj world.obj
