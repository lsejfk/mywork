#include "straInsertSort.h"

//Straight Insertion Sort
void insertSort(SeqList *list){
	int i,j;
	for(i=1;i<list->length;i++){
		for(j=i;j>0 && list->red[j].data<list->red[j-1].data;j--){
			swap(list,j,j-1);//Swap location
		}
	}
}


//Binary Insertion Sort
void binInsertSort(SeqList *list){
	int low,high,i,j,mid;
	RedType tmp;
	for(i=1;i<list->length;i++){
		low = 0;
		high = i - 1;
		while(low <= high){
			mid = (low + high) / 2;
			if(list->red[i].data < list->red[mid].data){
				high = mid - 1;
			}else{
				low = mid + 1;
			}
		}//while(low <= high)
		tmp = list->red[i];
		for(j=i;j>high+1;j--){
			swap(list,j,j-1);
		}//for
	}
}
