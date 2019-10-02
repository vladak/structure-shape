#!/bin/bash

if ./cstyle.pl *.c 2>/dev/null | grep '.*'; then
	echo "C style check failed"
	exit 1
fi
