#include "unp.h"
#include <arpa/inet.h>
#include <errno.h>

int myinet_pton(int family,const char *strptr,void *addrptr){
	if(family == AF_INET){
		struct in_addr in_val;
		if(inet_aton(strptr,&in_val)){
			memcpy(addrptr,&in_val,sizeof(in_val));
			return 1;
		}
		return 0;
	}
	errno = EAFNOSUPPORT;
	return -1;
}

const char *myinet_ntop(int family,const void *addrptr,char *strptr,size_t len){
	if(family == AF_INET){
		char tmp[INET_ADDRSTRLEN + 1];
		const unsigned char *p = (unsigned char *)addrptr;
		snprintf(tmp,sizeof(tmp),"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
		if(strlen(tmp) > len){
			return NULL;
		}
		strncpy(strptr,tmp,len);
		return strptr;
	}
	errno = EAFNOSUPPORT;
	return NULL;
}

int main(){
	struct in_addr in_val;
	char *val,s[INET_ADDRSTRLEN];
	if(myinet_pton(AF_INET,"127.0.0.1",&in_val) > 0){
		printf("myinet_pton success\n");
	}else{
		if(errno == EAFNOSUPPORT){
			printf("no support\n");
		}else{
			printf("invalid string\n");
		}
		return -1;
	}

	if((val = myinet_ntop(AF_INET,&in_val,s,INET_ADDRSTRLEN))){
		printf("myinet_ntop success\n");
		printf("%s\n",val);
	}else{
		printf("myinet_ntop error\n");
		return -1;
	}
	
	return 0;
}
