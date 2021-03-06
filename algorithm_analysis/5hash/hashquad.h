#ifndef HASHQUAD_H
#define HASHQUAD_H
typedef char * HashEntryElemType;

enum KindOfEntry {
	Legal,Empty,Deleted,Prefix
};

struct HashEntry{
	HashEntryElemType elem;
	enum KindOfEntry info;
};

struct HashTabQuad{
	int tabsize;
	struct HashEntry *cellList;
};

typedef struct HashTabQuad *HashTQ;

HashTQ hashtq_initializeTable(int tabsize);
void hashtq_destroyTable(HashTQ H);
int hashtq_find(HashEntryElemType key,HashTQ H);
void hashtq_insert(HashEntryElemType key,enum KindOfEntry type,HashTQ H);
HashEntryElemType hashtq_retrieve(int p,HashTQ H);
HashTQ hashtq_rehash(HashTQ H);
enum KindOfEntry hashtq_getstatus(int pos,HashTQ H);

#endif
