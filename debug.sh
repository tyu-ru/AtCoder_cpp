#!/bin/bash

CONTEST=$1
CONTEST_NUM=$2
PROBLEM=$3

g++-5 -std=gnu++1y -Wall -Wextra -O2 -I$PWD/boost/include -L$PWD/boost/lib -o a.out ${CONTEST}/${CONTEST_NUM}/${PROBLEM}.cpp

./a.out
