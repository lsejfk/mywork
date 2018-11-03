#!/bin/bash
#filename:function.sh
function fname(){
	echo $1;
	echo $2;
	echo $@;
	echo $*;
	return 0;
}

fname hello world;
pwd;
(cd /bin;pwd;ls);
pwd;

#read -n 2 var
#echo
#echo $var
echo "Enter the password:"
read -s pass
echo
#echo "Please retype:"
#read -s pass1
#echo
#if [[ ${pass} != ${pass1} ]]; then
#	echo failure in two password
#fi

#read -d "#" var
#echo
#echo $var

function repeat(){
	echo "Please retype:"
	read -s pass1
	while [[ $1 != ${pass1} ]];
	do
		echo 
		echo failure
		echo "Please retype:"
		read -s pass1
	done
	return 0;
}
repeat ${pass}
