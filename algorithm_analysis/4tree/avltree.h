#ifndef AVLTREE_H
#define AVLTREE_H
typedef int AvlElemType;

typedef struct AvlNode{
	AvlElemType elem;
	struct AvlNode *left;
	struct AvlNode *right;
	int height;
}*AvlTree;

typedef AvlTree AvlPosition;

AvlTree avl_makeEmpty(AvlTree T);
AvlPosition avl_find(AvlElemType x,AvlTree T);
AvlPosition avl_findMin(AvlTree T);
AvlPosition avl_findMax(AvlTree T);
AvlTree avl_insert(AvlElemType x,AvlTree T);
AvlTree avl_delete(AvlElemType x,AvlTree T);
AvlElemType avl_retrieve(AvlPosition p);
int avl_height(AvlTree p);

#endif
