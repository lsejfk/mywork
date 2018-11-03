#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check(int arr[],int n){
	int low,high,mid;
	low = 1;
	high = n;
	while(low < high){
		mid = (low + high) / 2;
		if(mid == arr[mid]){
			return 1;	//exist
		}else if(mid < arr[mid]){
			high = mid;
		}else{
			return 0;	//error
		}
	}//while
	if(low == arr[low]){
		return 1;
	}
	return 0;
}
