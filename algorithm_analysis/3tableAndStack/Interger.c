#include "Interger.h"
#include <stdio.h>
#include <stdlib.h>
#include "myerr.h"

//number string to IntNum
IntNum strToIntNum(const char *str){
	int n,i;
	char *num;
	n = strlen(str);
	num = (char *)calloc(
	for(i=0;i<n;i++){
		if(str[i] < '0' || str[i] > '9'){
			str[i] 
		}
	}
}
