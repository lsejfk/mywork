#ifndef CYCLICQUEUE_H
#define CYCLICQUEUE_H
#include<stdio.h>
#include<stdlib.h>
#define CyclicQType int
typedef struct CyclicQ{
	CyclicQType *data;		//an array that will be initialized by initCyclicQ()
	int front;			//the front pointer
	int rear;			//the rear pointer
}CyclicQ;

void initCyclicQ(CyclicQ *queue,int max);	//max is the maxmum of the queue
void enQueue(CyclicQ *queue,CyclicQType e);	//enQueue
void deQueue(CyclicQ *queue,CyclicQType *v);	//deQueue
int isQueueEmpty(CyclicQ *queue);		//check if the queue is empty
int queueLength(CyclicQ *queue);		//return the length of the queue

#endif
