#include <stdio.h>
#include <stdlib.h>

void merge(int src[],int des[],int i,int m,int s){
	int j,k;
	for(j=m+1,k=i;i<=m && j<=s;k++){
		if(src[j] < src[i]){
			des[k] = src[j++];
		}else{
			des[k] = src[i++];
		}
	}
	while(i <= m){
		des[k++] = src[i++];
	}
	while(j <= s){
		des[k++] = src[j++];
	}
}


void mSort(int src[],int des[],int s,int t){
	int m;
	static int flag = 0;
	int *store;
	if(!flag){
		store = (int *)malloc(sizeof(int) * (t + 1));
		flag = 1;
	}
	if(s == t){
		des[s] = src[s];
	}else{
		m = (s + t) / 2;
		mSort(src,store,s,m);
		mSort(src,store,m+1,t);
		merge(store,des,s,m,t);
	}
}

void mergeSort(int arr[],int n){
	mSort(arr,arr,0,n-1);
}

int main(){
	int arr[] = {49,38,65,97,76,13,27,49};
	int i;
	mergeSort(arr,8);
	for(i=0;i<8;i++){
		printf("%4d",arr[i]);
	}
	putchar('\n');
	return 0;
}
