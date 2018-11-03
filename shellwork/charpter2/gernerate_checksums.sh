#!/bin/bash
#generate_checksums.sh
pidarr=()
for file in timint output
do 
	md5sum $file &
	pidarr+=("$!")
done
wait ${pidarr[@]}
