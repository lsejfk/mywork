#include "CyclicQueue.h"
static int MAX_CQ_SIZE;			//the maxmum of queue

//initialize
void initCyclicQ(CyclicQ *queue,int max){
	queue->front = queue->rear = 0;
	MAX_CQ_SIZE = max;
	if(MAX_CQ_SIZE <= 2){
		fprintf(stderr,"error:initCyclicQ:max is too small\n");
		return;
	}
	queue->data = (CyclicQType *)malloc(sizeof(CyclicQType) * (MAX_CQ_SIZE));
	if(queue->data == NULL){
		fprintf(stderr,"error:initCyclicQ:malloc failed\n");
		return;
	}
}

//enQueue
void enQueue(CyclicQ *queue,CyclicQType e){
	if((queue->rear + 1) % MAX_CQ_SIZE == queue->front){
		fprintf(stderr,"error:enQueue:the queue is full\n");
		return;
	}
	queue->data[queue->rear] = e;		//enQueue
	queue->rear = (queue->rear + 1) % MAX_CQ_SIZE;
}

//deQueue
void deQueue(CyclicQ *queue,CyclicQType *v){
	if(queue->rear == queue->front){
		fprintf(stderr,"error:deQueue:the queue is empty\n");
		return;
	}
	*v = queue->data[queue->front];
	queue->front = (queue->front + 1) % MAX_CQ_SIZE;
}


//check if the queue is empty
int isQueueEmpty(CyclicQ *queue){
	return (queue->rear == queue->front);
}

//return the length of the queue
int queueLength(CyclicQ *queue){
	return (queue->rear - queue->front + MAX_CQ_SIZE) % MAX_CQ_SIZE;
}
