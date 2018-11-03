#!/bin/bash
#filename:time_take.sh
start=$(date +%N)
./main
end=$(date +%N)
difference=$((end - start))
second=$(date --date ${difference} +%S)
echo Time taken to execute commands is $difference seconds.
