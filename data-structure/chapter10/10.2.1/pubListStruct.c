#include "pubListStruct.h"
#include<stdio.h>


//Swap Location
void swap(SeqList *list,int i,int j){
	RedType tmp;
	tmp = list->red[i];
	list->red[i] = list->red[j];
	list->red[j] = tmp;
}

//Input information
PubListInfoType* inputInfo(){
	return NULL;
}

//Input data
void inputData(SeqList *list){
	int n;
	PubListElemType key;
	n = 0;				//Count the number of data input
	while(n < MAX_LIST_LEN && (scanf("%d",&key)) != EOF){
		list->red[n].data = key;
		list->red[n].info = inputInfo();
		n++;
	}
	list->length = n;
}

//Print data
void printData(SeqList *list){
	int n;
	for(n=0;n<list->length;n++){
		printf("%4d",list->red[n].data);
	}
	putchar('\n');

}
