#!/bin/sh

g++-5 -std=gnu++1y -Wall -Wextra -O2 -I$PWD/boost/include -L$PWD/boost/lib -o a.out $1

if [ $? = 0 ]; then

oj test $2 $3

rm a.out

fi
