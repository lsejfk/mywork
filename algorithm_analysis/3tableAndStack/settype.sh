#!/bin/bash
#modify the array_stack.h
type=$1;
sed -i "s/typedef .* ArrStackType/typedef $type ArrStackType/g" /home/michael/local/include/array_stack.h;
#update dynamic library
pushd /home/michael/local/src > /dev/null;
make > /dev/null;
make clean > /dev/null;
pushd > /dev/null;

	
