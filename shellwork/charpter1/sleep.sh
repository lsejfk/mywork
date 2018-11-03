#!/bin/bash
#filename:sleep.sh
echo -n Count:
tput sc
count=0;
until [ $count -gt 10 ];
do
	if [ $count -lt 40 ];
	then
		let count++;
		sleep 1;
		tput rc
		tput ed
		echo -n $count;
	else exit 0;
	fi
done
echo
