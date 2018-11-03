#!/bin/bash
#filename:rename.sh
#usage:rename the split files
count=1;
for hel in `find . -maxdepth 1 -type f -name "hello-*"`
	do
	newhel=hello-$count.split
	let count++
	echo renaming ${hel} to ${newhel}
	mv "$hel" "$newhel"
	done

