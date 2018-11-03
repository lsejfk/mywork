#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getbit(int num){
	static int n = 0;
	if(num == 1){
		return n + 1;
	}
	n++;
	return getbit(num / 2);
}

int main(){
	int num;
	scanf("%d",&num);
	printf("%d\n",getbit(num));
	return 0;
}
