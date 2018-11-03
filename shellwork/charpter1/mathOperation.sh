#!/bin/bash
no1=1;
no2=5;
let result=$no1+$no2;
echo $result;
let no1++
let no2--
echo "no1=${no1} no2=${no2}"
result=$[no1 + no2]
echo "4 * 0.56" | bc
no=54
result=`echo "$no * 1.5" | bc`
echo $result
echo "scale=2;3/8" | bc
#
#
#
#############################
#usage:change 10d to 2
##############################
nd=123;
echo "obase=2;$nd" | bc
nd=111001010
echo "obase=16;ibase=2;$nd" | bc
##############
#usage:compute the square and square root
#
############3
n=4
echo "sqrt($n)" | bc
echo "$n^$n" | bc
