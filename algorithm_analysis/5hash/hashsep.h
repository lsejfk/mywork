#ifndef HASHSEP_H
#define HASHSEP_H
struct ListNode{
	ListElemType elem;
	struct ListNode *next;
};

typedef struct ListNode *List;
typedef List ListPosition;

struct HashTb{
	int tablesize;
	List *thelist;
};

typedef struct HashTb *HashTable;

HashTable hash_initializeTable(int tabsize);
void hash_destroyTable(HashTable H);
ListPosition hash_find(ListElemType key,HashTable H);
void hash_insert(ListElemType key,HashTable H);
ListElemType hash_retrieve(ListPosition P);

#endif
