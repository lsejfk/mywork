#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int is_even(int i);

double mypow(double x,int n){
	int *flag;
	int i,k;
	double po;
	flag = (int *)calloc(n,sizeof(int));
	assert(flag != NULL);
	k = 0;
	i = n;
	while(i > 1){
		if(is_even(i)){
			flag[k++] = 0;	//even
		}else{
			flag[k++] = 1;	//odd
		}
		i /= 2;
	}
	po = x;
	while(k > 0){
		if(flag[--k]){	//odd
			po = po * po * x; 
		}else{
			po *= po;
		}
	}
	return po;
}

int main(){
	double x;
	int n;
	scanf("%lf%d",&x,&n);
	printf("the result is %f\n",mypow(x,n));
	return 0;
}

int is_even(int i){
	return (i % 2 == 0) ? 1 : 0;
}
