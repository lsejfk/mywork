#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//when n>5, 6x-1,6x,6x+1,2(3x+1),3(2x+1),2(3x+2)...,only 6x-1 and 6x+1 can be prime number
int isPrime(int n){
	int i;
	int sqn;
	if(n < 5){
		if(n % 2 == 0){
			return 0;
		}else{
			return 1;
		}
	}else{
		i = 1;
		sqn = (int)sqrt(n);
		while(6 * i - 1 <= sqn){
			if(n % (6*i-1) == 0 || n % (6*i+1) == 0){
				return 0;
			}
			i++;
		}
		return 1;
	}
}


//filter
int isPrime2(int n){
	int *arr;
	int i,j,sqn;
	arr = (int *)calloc(n+1,sizeof(int));
	assert(arr != NULL);
	if(n < 2 || n % 2 == 0){
		return 0;
	}
	for(i=2;i<=n;i++){
		if(i % 2 == 0){	//is even
			arr[i] = 0;	//false
		}else{
			arr[i] = 1;	//true
		}
	}
	sqn = (int)sqrt((double)n);
	for(i=3;i <= sqn;i++){
		if(!arr[i]){
			continue;
		}
		for(j=i+i;j<=n;j+=i;){
			if(arr[j]){
				arr[j] = 0;	//false
			}
		}
	}
	return arr[n];

}


int main(){
	printf("%s\n",isPrime(576847) ? "yes" : "no");
	return 0;
}
