#!/bin/bash

DIR=$1/$2

mkdir $DIR

if [ $# = 3 ]; then

FILES=$3

else

FILES=ABCDEF

fi

echo $FILES | fold -w 1 | while read c; do
    cp template.cpp $DIR/${c}.cpp
done
