#include <stdio.h>
#include <stdlib.h>

void heapAdjust(int arr[],int s,int m){
	int i;
	int rc;
	rc = arr[s];
	for(i=2*s;i<=m;i*=2){
		if(i < m && arr[i+1] < arr[i]){
			++i;		//i is the subscript of the smaller key record
		}
		if(rc <= arr[i]){
			break;
		}
		arr[s] = arr[i];
		s = i;			//The location of rc for inserting
	}//for
	arr[s] = rc;
}


void heapSort(int arr[],int n){
	int i,j;
	for(i=(n-1)/2;i>=1;i--){
		heapAdjust(arr,i,n-1);	//Build heap
	}
	for(i=n-1;i>1;i--){
		j = arr[i];
		arr[i] = arr[1];
		arr[1] = j;		//Swap the first record and the last record that haven't been sorted.

		heapAdjust(arr,1,i-1);
	}
}


int main() {
	int arr[] = {0,49,38,65,97,76,13,27,49};
	int i;
	heapSort(arr,9);
	for(i=1;i<=8;i++){
		printf("%4d",arr[i]);
	}
	return 0;
}
