#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
typedef	int  ArrQueueType;

typedef struct Queue{
	int capacity;
	int front;
	int rear;
	int size;
	ArrQueueType *arr;
}*ArrQueue;

int arrque_isEmpty(ArrQueue Q);
int arrque_isFull(ArrQueue Q);
ArrQueue arrque_createQueue(int maxElems);
void arrque_disposeQueue(ArrQueue Q);
void arrque_makeEmpty(ArrQueue Q);
void arrque_enqueue(ArrQueueType x,ArrQueue Q);
ArrQueueType arrque_front(ArrQueue Q);
void arrque_dequeue(ArrQueue Q);
ArrQueueType arrque_frontAndDequeue(ArrQueue Q);

#endif
