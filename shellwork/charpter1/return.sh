#!/bin/bash
#filename:return.sh
var=2038
str=$(cat /proc/${var}/environ)
oldIFS=${IFS};
IFS=":"
for i in ${str};
do
	echo ${i}
done
IFS=${oldIFS};
echo -e "\e[1;44m end \e[0m"
