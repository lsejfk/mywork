#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextprime(int the){
	int k,res;
	if(the < 3){
		return 2;
	}else if(the < 5){
		return 3;
	}else if(the < 7){
		return 5;
	}else{
		k = the / 6;
		if((res = 6 * k + 1) >= the){
			return res;
		}else if((res = 6 * k + 5) >= the){
			return res;
		}
	}
	return the;
}

int hash(const char *key,int len){
	int hashval = 0;

	while(*key != '\0' && len > 0){
		hashval +=  *key++;
		len--;
	}
	return hashval;
}

int findpos(char *input,char *pattern){
	int inputlen,patlen,maxlen,len;
	int i;
	int pathashval,inputhashval;
	maxlen = 32;

	inputlen = strlen(input);
	patlen = strlen(pattern);
	len = patlen;
	if(patlen > maxlen){
		len = maxlen;
	}
	pathashval = hash(pattern,len);
	inputhashval = hash(input,len);
	if(pathashval == inputhashval){
		if(strncmp(pattern,input,patlen) == 0){
			return 0;
		}
	}
	for(i=1;i<=inputlen-patlen;i++){
		inputhashval = inputhashval - input[i-1] + input[i+patlen-1];	
		if(pathashval == inputhashval){
			if(strncmp(pattern,input+i,patlen) == 0){
				return i;
			}
		}
	}
	return -1;
}

int main(){
	char *pattern,*input;
	pattern = "abcdefg";
	input = "afakadfjlgljsladfjaskld asldfjalskdadaljabcefgkgdksfajlsdjfaas dfalsdkjfakldj fklasjdfklajskd";
	printf("pattern:%s\n",pattern);
	printf("input:%s\n",input);
	printf("%d\n",findpos(input,pattern));
	return 0;
}
