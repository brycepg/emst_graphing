#!/bin/bash

# Supply the file as an argument to this script to compile it using mlpack and root
# without the need for Makefile installed
# output is [filename].out

echo "g++ --std=c++11 -I/usr/include/libxml2/ $1 -o ${1/.cpp/.out} -lmlpack -larmadillo -Wl,-rpath=/usr/local/lib \`root-config --libs --cflags\`"
g++ --std=c++11 -I/usr/include/libxml2/ $1 -o ${1/.cpp/.out} -lmlpack -Wl,-rpath=/usr/local/lib `root-config --libs --cflags`
