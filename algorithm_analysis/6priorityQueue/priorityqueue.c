#include "priorityqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//initialize the priority queue
PriorityQueue priq_init(int maxElems){
	PriorityQueue H;
	if(maxElems < MINELEM){
		fprintf(stderr,"Priority size is too small\n");
		return NULL;
	}
	H = (struct Heap_tag *)malloc(sizeof(struct Heap_tag));
	if(H == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	H->capacity = maxElems;
	H->size = 0;
	H->elem = (HeapElemType *)calloc(maxElems + 1,sizeof(HeapElemType));
	if(H->elem == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	H->elem[0] = MINVALUE;
	return H;
}

//destroy the priority queue
void priq_destroy(PriorityQueue H){
	if(H){
		if(H->elem){
			free(H->elem);
		}
		free(H);
	}
}

//make empty
void priq_makeEmpty(PriorityQueue H){
	if(H){
		H->size = 0;
	}
}

//insert into priority queue
void priq_insert(HeapElemType e,PriorityQueue H){
	int i;
	if(priq_isFull(H)){
		fprintf(stderr,"the queue is full\n");
		return;
	}
	for(i=++H->size;e<H->elem[i/2];i /= 2){
		H->elem[i] = H->elem[i / 2];
	}
	H->elem[i] = e;
}

//delete the minimum value in the queue
HeapElemType priq_deleteMin(PriorityQueue H){
	HeapElemType minval,lastval;
	int i,child;
	if(priq_isEmpty(H)){
		fprintf(stderr,"the Priority queue is empty\n");
		return H->elem[0];
	}
	minval = H->elem[1];
	lastval = H->elem[H->size--];
	for(i=1;2 * i <= H->size;){
		child = 2 * i;
		//choose the smallest child
		if(child < H->size && H->elem[child + 1] < H->elem[child]){
			child++;
		}
		if(lastval > H->elem[child]){
			H->elem[i] = H->elem[child];
			i = child;
		}else{
			break;
		}
	}
	H->elem[i] = lastval;
	return minval;
}

HeapElemType priq_findMin(PriorityQueue H){
	if(priq_isEmpty(H)){
		return H->elem[0];
	}
	return H->elem[1];
}

int priq_isEmpty(PriorityQueue H){
	return H->size == 0;
}

int priq_isFull(PriorityQueue H){
	return H->size == H->capacity;
}

PriorityQueue priq_buildHeap(PriorityQueue H){
	int i,child;
	HeapElemType tmp;
	for(i=H->size/2;i>0;i--){
		child = i * 2;
		if(child != H->size && H->elem[child+1] < H->elem[child]){
			child++;
		}
		if(H->elem[child] < H->elem[i]){
			tmp = H->elem[child];
			H->elem[child] = H->elem[i];
			H->elem[i] = tmp;
		}
	}
	return H;
}

static void decreaseKey(int pos,HeapElemType dec,PriorityQueue H){
	int i;
	HeapElemType tmp;
	if(pos < 1 || pos > H->size){
		fprintf(stderr,"pos is out of range in decreaseKey\n");
		return;
	}
	H->elem[pos] -= dec;
	for(i=pos/2;i>0;i/=2){
		if(H->elem[i] > H->elem[pos]){
			tmp = H->elem[pos];
			H->elem[pos] = H->elem[i];
			H->elem[i] = tmp;
			pos = i;
		}else{
			break;
		}
	}
}

static void increaseKey(int pos,HeapElemType inc,PriorityQueue H){
	int i;
	HeapElemType tmp;
	if(pos < 1 || pos > H->size){
		fprintf(stderr,"pos is out of range in increaseKey\n");
		return;
	}
	H->elem[pos] += inc;
	for(i=pos*2;i<=H->size;i*=2){
		if(i != H->size && H->elem[i+1] < H->elem[i]){
			i++;
		}
		if(H->elem[pos] > H->elem[i]){
			tmp = H->elem[pos];
			H->elem[pos] = H->elem[i];
			H->elem[i] = tmp;
			pos = i;
		}else{
			break;
		}
	}

}

static void deletep(int p,PriorityQueue H){
	if(p < 1 || p > H->size){
		fprintf(stderr,"p is out of range in deletep\n");
		return;
	}
	decreaseKey(p,INFINITE,H);
	priq_deleteMin(H);
	/*
	lastval = H->elem[H->size--];
	for(i=p*2;i<=H->size;i*=2){
		if(i != H->size && H->elem[i+1] < H->elem[i]){
			i++;
		}
		if(lastval > H->elem[i]){
			H->elem[p] = H->elem[i];
			p = i;
		}else{
			break;
		}
	}
	*/
}


