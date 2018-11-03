#include <stdio.h>
#include <stdlib.h>
int max_mul_sub(int arr[],int n);
int min(int a,int b,int c);
int max(int a,int b,int c);

int main(){
	int n,i;
	int arr[100];
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("The max multiple of subset is %d\n",max_mul_sub(arr,n));
}

int max_mul_sub(int arr[],int n){
	int i,ans;
	int max_ahead,min_ahead,tmp_max,tmp_min;
	ans = max_ahead = min_ahead = arr[0];
	for(i=1;i<n;i++){
		tmp_max = max_ahead * arr[i];
		tmp_min = min_ahead * arr[i];
		max_ahead = max(arr[i],tmp_max,tmp_min);
		min_ahead = min(arr[i],tmp_max,tmp_min);
		ans = ans > max_ahead ? ans : max_ahead;
	}
	return ans;
}


int max(int a,int b,int c){
	if(a > b){
		if(b > c){
			return a;
		}else if(a > c){
			return a;
		}else{
			return c;
		}
	}else{
		if(a > c){
			return b;
		}else if(b > c){
			return b;
		}else{
			return c;
		}
	}
}

int min(int a,int b,int c){
	if(a < b){
		if(b < c){
			return a;
		}else if(a < c){
			return a;
		}else{
			return c;
		}
	}else{
		if(a < c){
			return b;
		}else if(b < c){
			return b;
		}else{
			return c;
		}
	}
}
