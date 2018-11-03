#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>
void push(ArrQueueType x,ArrQueue Q);
ArrQueueType pop(ArrQueue Q);
void inject(ArrQueueType x,ArrQueue Q);
ArrQueueType eject(ArrQueue Q);

int main(){
	ArrQueue Q;
	Q = arrque_createQueue(20);
	push(2,Q);
	inject(3,Q);
	printf("eject:%d,pop:%d\n",eject(Q),pop(Q));

}

int decc(int loc,ArrQueue Q){
	if(loc == 0){
		return Q->capacity - 1;
	}
	return loc - 1;
}
//insert at the front of front
void push(ArrQueueType x,ArrQueue Q){
	if(arrque_isFull(Q)){
		fprintf(stderr,"full queue\n");
		return;
	}
	Q->size++;
	Q->front = decc(Q->front,Q);
	Q->arr[Q->front] = x;
}

//delete at the front
ArrQueueType pop(ArrQueue Q){
	return arrque_frontAndDequeue(Q);
}

//insert at the rear
void inject(ArrQueueType x,ArrQueue Q){
	arrque_enqueue(x,Q);
}

//delete at the rear
ArrQueueType eject(ArrQueue Q){
	if(arrque_isEmpty(Q)){
		fprintf(stderr,"empty queue");
		return 0;
	}
	Q->rear = decc(Q->rear,Q);
	Q->size--;
	return Q->arr[Q->rear];
}
