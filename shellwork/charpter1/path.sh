#!/bin/bash 
#filename:path.sh
oldIFS=$IFS;
var=$(echo $PATH)
IFS=':';
count=0;
for i in $var;
do
	let count++;
done
echo $count
j=1;
str='';
set -x
for i in $var;
do
	if [ $j -eq 2 ]; then
		str="${i}";
	else if [ $j -gt 2 ]; then
		str="${str}:${i}";
	fi
	let j++
done
set +x
IFS=$oldIFS;
echo $str
