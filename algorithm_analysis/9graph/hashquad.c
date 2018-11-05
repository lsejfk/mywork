#include "hashquad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int hash(HashEntryElemType key,int tabsize){
	unsigned int hashval = 0;
	char *a = key;
	while(*a){
		hashval = (hashval << 5) + *a++;
	}
	return hashval % tabsize;
}


HashTQ hashtq_initializeTable(int tabsize){
	HashTQ H;
	int i;

	if(tabsize < 3){
		fprintf(stderr,"table size is too small\n");
		return NULL;
	}
	if((H = (HashTQ)malloc(sizeof(struct HashTabQuad))) == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	H->tabsize = nextprime(tabsize);
	H->cellList = (struct HashEntry *)calloc(H->tabsize,sizeof(struct HashEntry));
	if(H->cellList == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}

	for(i=0;i<H->tabsize;i++){
		H->cellList[i].info = Empty;
		H->cellList[i].elem = NULL;
		H->cellList[i].index = -1;
	}
	return H;
}

void hashtq_destroyTable(HashTQ H){
	int i;
	for(i=0;i<H->tabsize;i++){
		if(H->cellList[i].info  != Empty){
			free(H->cellList[i].elem);
		}
	}
	free(H->cellList);
	free(H);
}

int hashtq_find(HashEntryElemType key,HashTQ H){
	int i,cur;

	i = 0;
	cur = hash(key,H->tabsize);
	while(H->cellList[cur].info != Empty && strcmp(H->cellList[cur].elem,key) != 0){
		cur += 2 * ++i - 1;
		if(cur >= H->tabsize){
			cur -= H->tabsize;
		}
	}
	return cur;	
}
char * copyword(char *key){
	char *res;
	res = (char *)calloc(strlen(key) + 1,sizeof(char));
	if(res == NULL){
		fprintf(stderr,"calloc error\n");
		exit(-1);
	}
	strncpy(res,key,strlen(key));
	return res;
}

int hashtq_insert(HashEntryElemType key,enum KindOfEntry type,int index,HashTQ H){
	int pos;
	HashEntryElemType tmp;
	
	pos = hashtq_find(key,H);
	if(H->cellList[pos].info != Legal && H->cellList[pos].info != Prefix){
		tmp = H->cellList[pos].elem;
		H->cellList[pos].elem = copyword(key);
		H->cellList[pos].index = index;
		if(tmp){
			free(tmp);
		}
		if(type == Prefix){
			H->cellList[pos].info = Prefix;
		}else{
			H->cellList[pos].info = Legal;
		}
	}
	return pos;
}

HashEntryElemType hashtq_retrieve(int p,HashTQ H){
	return H->cellList[p].elem;
}

HashTQ hashtq_rehash(HashTQ H){
	struct HashEntry *cell;
	int oldsize,i;

	cell = H->cellList;
	oldsize = H->tabsize;
	H = hashtq_initializeTable(2 * oldsize);
	if(H == NULL){
		fprintf(stderr,"initialize table failed\n");
		exit(-1);
	}
	for(i=0;i<oldsize;i++){
		if(cell[i].info == Legal || cell[i].info == Prefix){
			hashtq_insert(cell[i].elem,cell[i].info,cell[i].index,H);
		}
	}
	return H;
}

enum KindOfEntry hashtq_getstatus(int pos,HashTQ H){
	return H->cellList[pos].info;
}

int hashtq_retrieveIndex(HashEntryElemType key,HashTQ H){
	int pos;
	pos = hashtq_find(key,H);
	if(H->cellList[pos].info == Legal){
		return H->cellList[pos].index;
	}
	return -1;
}
