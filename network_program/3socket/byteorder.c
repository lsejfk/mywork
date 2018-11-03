#include "unp.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	union{
		short s;
		char n[sizeof(short)];
	}un;

	un.s = 0x0102;

	printf("%s\n",CPU_VENDOR_OS);

	if(sizeof(short) == 2){
		if(un.n[0] == 1 && un.n[1] == 2){
			printf("big\n");
		}else if(un.n[0] == 2 && un.n[1] == 1){
			printf("little-endian\n");
		}else{
			printf("unknown\n");
		}
	}
	printf("short size:%d",sizeof(short));
	return 0;
}
