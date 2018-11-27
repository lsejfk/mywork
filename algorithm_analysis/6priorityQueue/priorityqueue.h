#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#define MINELEM 1
#define MINVALUE -2147483648 
#ifndef INFINITE
#define INFINITE 2147483647
#endif
typedef int HeapElemType;

struct Heap_tag{
	int capacity;
	int size;
	HeapElemType *elem;
};

typedef struct Heap_tag *PriorityQueue;

PriorityQueue priq_init(int maxElems);
void priq_destroy(PriorityQueue H);
void priq_makeEmpty(PriorityQueue H);
void priq_insert(HeapElemType e,PriorityQueue H);
HeapElemType priq_deleteMin(PriorityQueue H);
HeapElemType priq_findMin(PriorityQueue H);
int priq_isEmpty(PriorityQueue H);
int priq_isFull(PriorityQueue H);
/*
static void decreaseKey(int pos,HeapElemType dec,PriorityQueue H);
static void increaseKey(int pos,HeapElemType inc,PriorityQueue H);
static void deletep(int p,PriorityQueue H);
*/
PriorityQueue priq_buildHeap(PriorityQueue H);


#endif
