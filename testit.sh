#!/bin/sh

ret=0
TEST="./shapeup -t"

$TEST 0 0 0 0
if [ $? -ne 0 ]; then
	echo FAILED
	ret=1
fi

$TEST 0 14000 0 0
if [ $? -ne 0 ]; then
	echo FAILED
	ret=1
fi

$TEST 0 0 200 100
if [ $? -ne 0 ]; then
	echo FAILED
	ret=1
fi

exit $ret
