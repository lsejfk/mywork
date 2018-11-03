#include "hashsep.h"
#include <stdio.h>
#include <stdlib.h>

int nextprime(int the){
	int k,res;
	if(the < 3){
		return 2;
	}else if(the < 5){
		return 3;
	}else if(the < 7){
		return 5;
	}else{
		k = the / 6;
		if((res = 6 * k + 1) >= the){
			return res;
		}else if((res = 6 * k + 5) >= the){
			return res;
		}
	}
	return the;
}

//initialize the hash table
HashTable hash_initializeTable(int tabsize){
	HashTable H;
	int i;

	if(tabsize < 3){
		fprintf(stderr,"table size is too small\n");
		return NULL;
	}
	H = (struct HashTb *)malloc(sizeof(struct HashTb));
	if(H == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	H->tablesize = nextprime(tabsize);
	H->thelist = (List *)calloc(tabsize,sizeof(List));
	if(H->thelist == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	for(i=0;i<tabsize;i++){
		H->thelist[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
		if(H->thelist[i] == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		H->thelist[i]->next = NULL;
	}
	H->tablesize = tabsize;
	return H;
}

void hash_destroyTable(HashTable H){
	int i;
	ListPosition p,q;

	for(i=0;i<H->tablesize;i++){
		p = H->thelist[i];
		while(p){
			q = p;
			p = p->next;
			free(q);
		}
	}
	free(H->thelist);
	free(H);
}

ListPosition hash_find(ListElemType key,HashTable H){
	ListPosition p;
	p = H->thelist[hash(key,H->tablesize)];
	if(p == NULL){
		return NULL;
	}
	p = p->next;
	while(p && p->elem != key){
		p = p->next;
	}
	return p;
}

void hash_insert(ListElemType key,HashTable H){
	int index;
	ListPosition p,q;
	index = hash(key,H->tablesize);
	p = H->thelist[index];
	q = p->next;
	while(q){
		if(q->elem == key){
			break;
		}
		q = q->next;
	}
	if(q == NULL){
		q = (struct ListNode *)malloc(sizeof(struct ListNode));
		if(q == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		q->elem = key;
		q->next = p->next;
		p->next = q;
	}
}

ListElemType hash_retrieve(ListPosition P){
	return P->elem;
}
