#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char s[5];
	char *p;

	p = s;

	s[4] = 1;
	bzero(s,4);
	printf("after bzero:");
	printf("s0=%d,s1=%d,s2=%d,s3=%d,s4=%d\n",s[0],s[1],s[2],s[3],s[4]);
	bcopy(p+1,s,4);
	printf("after bcopy:");
	printf("s0=%d,s1=%d,s2=%d,s3=%d,s4=%d\n",s[0],s[1],s[2],s[3],s[4]);
	memcpy(s,p+1,4);
	printf("after memcpy:");
	printf("s0=%d,s1=%d,s2=%d,s3=%d,s4=%d\n",s[0],s[1],s[2],s[3],s[4]);
	return 0;
}
