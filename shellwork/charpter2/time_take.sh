#!/bin/bash
#filename:time_take.sh
start=$(date +%s)
$1
end=$(date +%s)
difference=$((end - start))
second=$(date --date ${difference} +%s)
echo Time taken to execute commands is $difference seconds.
