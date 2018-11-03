#ifndef PUBLISTSTRUCT_H
#define PUBLISTSTRUCT_H
#define MAX_LIST_LEN 20
typedef int PubListElemType;
typedef void *PubListInfoType;
typedef struct _RedType{
	PubListElemType data;		//The key
	PubListInfoType *info;		//Information about record
}RedType;

typedef struct _SeqList{
	RedType red[MAX_LIST_LEN + 1];	//The record list
	int length;			//The length of the list
}SeqList;
void swap(SeqList *list,int i,int j);
void inputData(SeqList *list);
void printData(SeqList *list);
#endif
