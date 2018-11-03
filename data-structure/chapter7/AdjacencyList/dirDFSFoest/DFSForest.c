#include "DFSForest.h"
#include "LinkStack.h"
#include "AdjacencyList.h"
static int *visited = NULL;	//the flag of whether the node has been visited
/*
//visit the node
void visit(ChildBroListType *e){
	printf("%4d",*e);
}
*/
//build a tree which root is q by depth priority search
void DFSTree(ALGraph *graph,int v,ChildBroList *root){
	int first = 0,i;	//the flag of whether it is the first arc at vth vertex
	ArcNode *pn;
	ChildBroList *newp,*cur;
	visited[v] = 1;
	cur = root;		//cur point to the current node
	for(pn=graph->alist[v].firstarc;pn != NULL;pn=pn->nextarc){
		i = pn->adjvex;
		if(!visited[i]){
			visited[i] = 1;
			newp = (ChildBroList *)malloc(sizeof(ChildBroList));	//create a new node
			if(newp == NULL){
				fprintf(stderr,"error:DFSTree:malloc newp failed\n");
				return;
			}
			//initialize newp
			newp->data = graph->alist[i].data;
			newp->firstchild = newp->nextsibling = NULL;
			if(!first){		//the node is the first arc
				root->firstchild = newp;
				first = 1;
			}else{
				cur->nextsibling = newp;	//the brother node
			}
			cur = newp;		//cur point to the current node
			DFSTree(graph,i,cur);	//traverse graph in depth priority from the ith vertex and build a child-building tree
		}
	}
}
//create Child Brother List T of generatint forest of undirected graph g in depth priority way 
void DFSForest(ALGraph *graph,ChildBroList **hlist){
	int i;
	ChildBroList *q,*p;
	visited = (int *)malloc(sizeof(int) * graph->vexnum);		//the flag of whether the node has been visited
	if(visited == NULL){
		fprintf(stderr,"error:DFSForest:malloc visited failed\n");
		return;
	}
	for(i=0;i<graph->vexnum;i++){
		visited[i] = 0;						//initialize into the status that the nodes haven't been visited
	}
	q = *hlist;		//set the current node
	for(i=0;i<graph->vexnum;i++){
		if(!visited[i]){
			p = (ChildBroList *)malloc(sizeof(ChildBroList));	//create a node
			if(p == NULL){
				fprintf(stderr,"error:DFSForest:malloc p failed\n");
				return;
			}
			//initialize p
			p->data = graph->alist[i].data;
			p->firstchild = p->nextsibling = NULL;
			if(*hlist == NULL){			//the first Building-Tree's root
				*hlist = p;
			}else{
				q->nextsibling = p;		//another Building-Tree,q always point to the current node
			}
			q = p;
			DFSTree(graph,i,q);			//build a tree which root is q by depth priority search
		}
	}
}

//preOrderTraverse
void preOrderTraverse(ChildBroList *root,void (*visit)(ChildBroListType *e)){
	ChildBroList *p;
	LinkStack s;
	initLinkStack(&s);
	p = root;
	push(&s,p);
	while(!isEmpty(&s)){
		while(getTop(&s,&p),p!=NULL){
			visit(&(p->data));
			push(&s,p->firstchild);
			p = p->firstchild;
		}
		pop(&s,&p);		//pop the NULL value
		if(!isEmpty(&s)){
			pop(&s,&p);
			push(&s,p->nextsibling);
		}
	}
}

