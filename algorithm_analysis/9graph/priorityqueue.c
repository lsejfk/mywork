#include "priorityqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//static void increaseKey(int pos,HeapElemType inc,PriorityQueue H,int (*comp)(const void *a,const void *b));
//static void deletep(int p,PriorityQueue H,int (*comp)(const void *a,const void *b));
int comp(const void *a,const void *b){
     struct heap_tag *ha,*hb;
     ha = (struct heap_tag *)a;
     hb = (struct heap_tag *)b;
     if(ha->weight < hb->weight){
          return -1;
     }else if(ha->weight > hb->weight){
          return 1;
     }else{
          return 0;
     }
}

//initialize the priority queue
PriorityQueue priq_init(int maxElems){
	PriorityQueue H;
     int i;
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
     /*
     for(i=0;i<=maxElems;i++){
          H->elem[i] = (HeapElemType)malloc(sizeof(struct heap_tag));
          if(H->elem[i] == NULL){
               fprintf(stderr,"malloc failed\n");
               exit(-1);
          }
     }
     */
     /*
     H->elem[0] = (HeapElemType)malloc(sizeof(struct heap_tag));
     if(H->elem[i] == NULL){
          fprintf(stderr,"malloc failed\n");
          exit(-1);
     }
     */
	H->elem[0].weight = MINVALUE;
	return H;
}

//destroy the priority queue
void priq_destroy(PriorityQueue H){
     int i;
	if(H){
          if(H->elem == NULL){
               return;
          }
          /*
          for(i=0;i<=H->size;i++){
               if(H->elem[i]){
                    free(H->elem[i]);
               }
          }
          */
          free(H->elem);
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
void priq_insert(HeapElemType e,PriorityQueue H,int (*comp)(const void *a,const void *b)){
	int i;
	if(priq_isFull(H)){
		fprintf(stderr,"the queue is full\n");
		return;
	}
	for(i=++H->size;i > 0 && comp(&e,&H->elem[i/2]) < 0;i /= 2){
		H->elem[i] = H->elem[i / 2];
	}
	H->elem[i] = e;
}

//delete the minimum value in the queue
HeapElemType priq_deleteMin(PriorityQueue H,int (*comp)(const void *a,const void *b)){
	HeapElemType minval,lastval;
	int i,child;
	if(priq_isEmpty(H)){
		fprintf(stderr,"the Priority queue is empty\n");
		return H->elem[0];
	}
	minval = H->elem[1];
	lastval = H->elem[H->size--];
	for(i=1;2 * i <= H->size;i=child){
		child = 2 * i;
		//choose the smallest child
		if(child < H->size && comp(&H->elem[child + 1],&H->elem[child]) < 0){
			child++;
		}
		if(comp(&lastval ,&H->elem[child]) > 0){
			H->elem[i] = H->elem[child];
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

static void percolateDown(PriorityQueue H,int i,int (*comp)(const void *a,const void *b)){
     int child;
	HeapElemType tmp;
     if(i > H->size / 2){
          return;
     }
     child = i * 2;
     if(child < H->size && comp(&H->elem[child+1],&H->elem[child]) < 0){
          child++;
     }
     if(comp(&H->elem[child],&H->elem[i]) < 0){
          tmp = H->elem[child];
          H->elem[child] = H->elem[i];
          H->elem[i] = tmp;
          percolateDown(H,child,comp);
     }
}

PriorityQueue priq_buildHeap(PriorityQueue H,int (*comp)(const void *a,const void *b)){
	int i;
	for(i=H->size/2;i>0;i--){
          percolateDown(H,i,comp);
	}
	return H;
}
/*

static void decreaseKey(int pos,HeapElemType dec,PriorityQueue H,int (*comp)(const void *a,const void *b)){
	int i;
	HeapElemType tmp;
	if(pos < 1 || pos > H->size){
		fprintf(stderr,"pos is out of range in decreaseKey\n");
		return;
	}
	H->elem[pos] -= dec;
	for(i=pos/2;i>0;i/=2){
		if(comp(&H->elem[i] ,&H->elem[pos]) > 0){
			tmp = H->elem[pos];
			H->elem[pos] = H->elem[i];
			H->elem[i] = tmp;
			pos = i;
		}else{
			break;
		}
	}
}

static void increaseKey(int pos,HeapElemType inc,PriorityQueue H,int (*comp)(const void *a,const void *b)){
	int i;
	HeapElemType tmp;
	if(pos < 1 || pos > H->size){
		fprintf(stderr,"pos is out of range in increaseKey\n");
		return;
	}
	H->elem[pos] += inc;
	for(i=pos*2;i<=H->size;i*=2){
		if(i != H->size && comp(&H->elem[i+1],&H->elem[i]) < 0){
			i++;
		}
		if(comp(&H->elem[pos] ,&H->elem[i]) > 0){
			tmp = H->elem[pos];
			H->elem[pos] = H->elem[i];
			H->elem[i] = tmp;
			pos = i;
		}else{
			break;
		}
	}

}

static void deletep(int p,PriorityQueue H,int (*comp)(const void *a,const void *b)){
	if(p < 1 || p > H->size){
		fprintf(stderr,"p is out of range in deletep\n");
		return;
	}
	decreaseKey(p,INFINITE,H,comp);
	priq_deleteMin(H,comp);
     */
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
/*
}

*/
