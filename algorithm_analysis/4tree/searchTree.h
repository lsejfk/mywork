#ifndef SEARCHTREE_H
#define SEARCHTREE_H
typedef int SearchTreeElemType;

struct SearchTreeNode{
	SearchTreeElemType data;
	struct SearchTreeNode *left;
	struct SearchTreeNode *right;
};

typedef struct SearchTreeNode *SearchTree;
typedef struct SearchTreeNode *STPosition;

SearchTree st_makeEmpty(SearchTree T);
STPosition st_find(SearchTreeElemType x,SearchTree T);
STPosition st_findMax(SearchTree T);
STPosition st_findMin(SearchTree T);
SearchTree st_insert(SearchTreeElemType x,SearchTree T);
SearchTree st_delete(SearchTreeElemType x,SearchTree T);
SearchTreeElemType st_retrieve(STPosition p);


#endif
