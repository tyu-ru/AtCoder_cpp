#!/bin/bash

CONTEST=$1
CONTEST_NUM=$2
PROBLEM=$3

g++-5 -std=gnu++1y -Wall -Wextra -O2 -I$PWD/boost/include -L$PWD/boost/lib -o a.out ${CONTEST}/${CONTEST_NUM}/${PROBLEM}.cpp

if [ $? = 0 ]; then

FIL=$(<case.txt)
TMP="$CONTEST $CONTEST_NUM $PROBLEM"

if [ "$FIL" != "$TMP" ]; then

rm -rf test
if [ "$CONTEST" = "dowacon" ] ; then
oj dl https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_${PROBLEM,,}
else
oj dl https://atcoder.jp/contests/${CONTEST,,}${CONTEST_NUM}/tasks/${CONTEST,,}${CONTEST_NUM}_${PROBLEM,,}
fi
echo $TMP > case.txt

fi

oj test $4 $5

rm a.out

fi
