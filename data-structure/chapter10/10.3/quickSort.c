#include<stdio.h>
#include<stdlib.h>

int partition(int arr[],int low,int high,int *fhigh,int *flow){
	int tmp,sw;
	int t,nhigh,nlow;
	nhigh = high;
	nlow = low;
	t = (low + high) / 2;
	*fhigh = 0;
	*flow = 0;
	if(arr[low] < arr[high]){		//Find the midest value
		if(arr[high] < arr[t]){
			tmp = arr[high];
			arr[high] = arr[low];
		}else if(arr[low] < arr[t]){
			tmp = arr[t];
			arr[t] = arr[low];
		}else{
			tmp = arr[low];
		}
	}else{
		if(arr[low] < arr[t]){
			tmp = arr[low];
		}else if(arr[high] < arr[t]){
			tmp = arr[t];
			arr[t] = arr[low];
		}else{
			tmp = arr[high];
			arr[high] = arr[low];
		}
	}
	while(low < high){
		while(low < high && arr[high] >= tmp){
			if(high < nhigh){				//Not the first time
				if(arr[high] > arr[nhigh]){		//Swap
					sw = arr[nhigh];
					arr[nhigh] = arr[high];
					arr[high] = sw;
					*fhigh = 1;
				}//if(arr[high] > arr[nhigh]
				nhigh--;
			}//if(high<nhigh)
			high--;
		}//while(low<high&&arr>=tmp)
		arr[low] = arr[high];
		while(low < high && arr[low] <= tmp){
			if(low > nlow){
				if(arr[low] < arr[nlow]){
					sw = arr[nlow];
					arr[nlow] = arr[low];
					arr[low] = sw;
					*flow = 1;
				}//if(arr[low]<arr[nlow]
				nlow++;
			}//if(low > nlow)
			low++;
		}//while(low < high&&...
		arr[high] = arr[low];
	}//while(low < high)
	arr[low] = tmp;
	return low;
}


void quickSort(int arr[],int low,int high){
	int key;
	int fhigh,flow;
	fhigh = flow = 0;
	if(low < high){
		key = partition(arr,low,high,&fhigh,&flow);
		if(flow){
			quickSort(arr,low,key-1);
		}
		if(fhigh){
			quickSort(arr,key+1,high);
		}
	}
}


int main(){
	int arr[] = {49,38,65,97,76,13,27,49};
	int i;
	quickSort(arr,0,7);
	for(i=0;i<8;i++){
		printf("%4d",arr[i]);
	}
	return 0;
}
