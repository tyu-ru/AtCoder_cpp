#!/bin/bash

DIR=$1/$2

mkdir $DIR

if [ $# = 3 ]; then

FILES=$3

else

FILES=ABCDEF

fi

echo $FILES | fold -w 1 | while read c; do
if [ ! -e $DIR/${c}.cpp ]; then
    cp -u template.cpp $DIR/${c}.cpp
fi
done
