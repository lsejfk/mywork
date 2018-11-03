#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>

static AvlTree makenode(){
	AvlTree p;
	p = (AvlTree)malloc(sizeof(struct AvlNode));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	p->left = p->right = NULL;
	return p;
}

static AvlTree firstTree(){
	AvlPosition p,q;
	p = makenode();
	q = makenode();
	p->left = q;
	q->height = 0;
	p->height = 1;
	return p;
}

static AvlTree secondTree(){
	AvlPosition p,q,s;
	s = makenode();
	q = makenode();
	p = s;
	p->height = 2;
	p->left = q;
	q->height = 1;
	p->right = makenode();
	p->right->height = 1;
	q->left = makenode();
	q->left->height = 0;
	return p;
}

static AvlTree duptree(AvlTree s){
	AvlPosition p;
	if(s == NULL){
		return NULL;
	}else{
		p = makenode();
		p->elem = s->elem;
		p->height = s->height;

		p->left = duptree(s->left);
		p->right = duptree(s->right);
	}
	return p;
}



static AvlTree avl_buildlessTree(int h){
	int i = 3;
	AvlPosition p,s,q;
	p = NULL;
	if(h == 1){
		s = firstTree();
		return s;
	}else if(h == 2){
		q = secondTree();
		return q;
	}else if(h > 2){
		s = firstTree();
		q = secondTree();
		while(i <= h){
			i++;
			p = (AvlTree)malloc(sizeof(struct AvlNode));
			if(p == NULL){
				fprintf(stderr,"malloc failed\n");
				exit(-1);
			}
			p->left = duptree(s);
			p->right = q;
			p->height = q->height + 1;
			s = q;
			q = p;
		}
	}
	return p;
}


//the beautiful code
static AvlTree build_avltree(int H){
	static int elem = 0;
	AvlTree T = NULL;
	if(H >= 0){
		T = makenode();
		T->height = H;
		T->left = build_avltree(H - 1);
		T->elem = ++elem;
		T->right = build_avltree(H - 2);
		return T;
	}
	return NULL;
}
