#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>

static int succ(int loc,ArrQueue Q){
	if(++loc == Q->capacity){
		loc = 0;
	}
	return loc;
}

//check if the queue is empty
int arrque_isEmpty(ArrQueue Q){
	return Q->size == 0;
}

//check if the queue is full
int arrque_isFull(ArrQueue Q){
	return Q->size == Q->capacity;
}

//create the queue
ArrQueue arrque_createQueue(int maxElems){
	ArrQueue Q;
	Q = (struct Queue *)malloc(sizeof(struct Queue));
	if(Q == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	Q->arr = (ArrQueueType *)calloc(maxElems,sizeof(ArrQueueType));
	if(Q->arr == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	Q->front = Q->rear = 0;
	Q->capacity = maxElems;
	return Q;
}

//destroy the queue
void arrque_disposeQueue(ArrQueue Q){
	Q->capacity = 0;
	Q->front = Q->rear = 0;
	Q->size = 0;
	free(Q->arr);
	free(Q);
}

//make empty
void arrque_makeEmpty(ArrQueue Q){
	Q->front = Q->rear = 0;
	Q->size = 0;
}

//enqueue
void arrque_enqueue(ArrQueueType x,ArrQueue Q){
	if(arrque_isFull(Q)){
		fprintf(stderr,"queue is full\n");
		return;
	}
	Q->size++;
	Q->arr[Q->rear] = x;
	Q->rear = succ(Q->rear,Q);
}	

//return the front element
ArrQueueType arrque_front(ArrQueue Q){
	return Q->arr[Q->front];
}

//dequeue
void arrque_dequeue(ArrQueue Q){
	if(arrque_isEmpty(Q)){
		fprintf(stderr,"empty queue\n");
		return;
	}

	Q->size--;
	Q->front = succ(Q->front,Q);
}

//dequeue and return the front element
ArrQueueType arrque_frontAndDequeue(ArrQueue Q){
	ArrQueueType tmp;
	if(arrque_isEmpty(Q)){
		fprintf(stderr,"empty queue\n");
		return 0;
	}
	tmp = Q->arr[Q->front];
	Q->size--;
	Q->front = succ(Q->front,Q);
	return tmp;
}
