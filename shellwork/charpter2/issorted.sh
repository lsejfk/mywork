#!/bin/bash
#filename:isSorted.sh
sort -C $1;
if [ $? -eq 0 ]; then
	echo Sorted;
else
	echo unsorted;
fi
