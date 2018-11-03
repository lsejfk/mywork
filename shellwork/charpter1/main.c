#include<stdio.h>

int main(){
	int i,j;
	for(i=0;i<99999;i++){
		for(j=0;j<10000;j++);
	}
	printf("hello world\n");
	return 0;
}
