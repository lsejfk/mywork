#include "adjlist.h"
#include "hashquad.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static HashTQ H;

static AlGraph createDG(int vexnum,int arcnum);
static AlGraph createDGW(int vexnum,int arcnum);
//static AlGraph createDN(int vexnum,int arcnum);
static AlGraph createUDGW(int vexnum,int arcnum);
static AlGraph createUDG(int vexnum,int arcnum);
//static AlGraph createUDN(int vexnum,int arcnum);
static VertexType make_vertexType();
static ArcNode make_arcNode(int adjvex);
static char *makecopystring(char *str);
static ArcInfoType make_arcInfoType(int weight);
static void free_vertexType(VertexType ptr);
static void free_arcNode(ArcNode ptr);

//initialize and create graph
AlGraph graph_create(GraphType kind,int vexnum,int arcnum){
	if(vexnum < 1){
		return NULL;
	}
	switch(kind){
		case DG:return createDG(vexnum,arcnum);break;
		case DGW:return createDGW(vexnum,arcnum);break;
	//	case DN:return createDN(vexnum,arcnum);break;
		case UDGW:return createUDGW(vexnum,arcnum);break;
		case UDG:return createUDG(vexnum,arcnum);break;
	//	case UDN:return createUDN(vexnum,arcnum);break;
		default:
			fprintf(stderr,"unkonw graph type\n");
			return NULL;
	}

}

void graph_dispose(AlGraph G){
	int i;
	if(G){
		for(i=0;i<G->vexnum;i++){
			if(G->vertices[i].data){
				free_vertexType(G->vertices[i].data);
			}
			if(G->vertices[i].firstarc){
				free_arcNode(G->vertices[i].firstarc);
			}
		}
		free(G->vertices);
		free(G);
	}
}

static AlGraph createDG(int vexnum,int arcnum){
	AlGraph grp;
	int i,namelen,adjvex;
	char name[64];
	ArcNode p;
	grp = (AlGraph)malloc(sizeof(struct AlGraph_tag));
	if(grp == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	grp->vexnum = vexnum;
	grp->arcnum = arcnum;
	grp->kind = DG;
	grp->vertices = (struct VNode_tag *)calloc(vexnum,sizeof(struct VNode_tag));
	if(grp->vertices == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	//initialize the hash table H
	H = hashtq_initializeTable(vexnum * 2);
	for(i=0;i<vexnum;i++){
		fgets(name,64,stdin);		//get the vertex name,it must end by newline
		namelen = strlen(name) - 1;
		if(namelen == 0){		//remove the newline
			fgets(name,64,stdin);		//get the vertex name,it must end by newline
			namelen = strlen(name) - 1;
		}
		name[namelen] = '\0';	//remove the newline
		//insert into hash table H
		hashtq_insert(name,Legal,i,H);
		grp->vertices[i].data = make_vertexType();	///////////////
		grp->vertices[i].data->name = makecopystring(name);	/////////////
		grp->vertices[i].data->flag = 0;	/////////////////haven't enqueue
		//input the arc
		scanf("%d",&adjvex);
		if(adjvex != -1){
			p = make_arcNode(adjvex);
			grp->vertices[i].firstarc = p;
		}else{
			grp->vertices[i].firstarc = NULL;
			continue;
		}
		while((scanf("%d",&adjvex),adjvex != -1)){
			p->next = make_arcNode(adjvex);		//////////////////

			p = p->next;
		}
		/*
		fgets(name,64,stdin);
		if(name[0] != '\n'){
			namelen = strlen(name) - 1;
			name[namelen] = '\0';
			adjvex = hashtq_retrieveIndex(name,H);
			if(adjvex < 0){
				fprintf(stderr,"invalid vertex\n");
				exit(-1);
			}
			p = make_arcNode(adjvex);		///////////////////
			grp->vertices[i].firstarc = p;
			//p->info = make_arcInfoType(weight);	////////////////
		}else{
			grp->vertices[i].firstarc = NULL;
			continue;
		}
		while((fgets(name,64,stdin),name[0]) != '\n'){
			namelen = strlen(name) - 1;
			name[namelen] = '\0';
			adjvex = hashtq_retrieveIndex(name,H);
			if(adjvex < 0){
				fprintf(stderr,"invalid vertex\n");
				exit(-1);
			}
			p->next = make_arcNode(adjvex);		///////////////////
		}
		*/
	}//for
	return grp;
}

static AlGraph createDGW(int vexnum,int arcnum){
	AlGraph grp;
	int i,namelen,adjvex,weight;
	char name[64];
	ArcNode p;
	grp = (AlGraph)malloc(sizeof(struct AlGraph_tag));
	if(grp == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	grp->vexnum = vexnum;
	grp->arcnum = arcnum;
	grp->kind = DGW;
	grp->vertices = (struct VNode_tag *)calloc(vexnum,sizeof(struct VNode_tag));
	if(grp->vertices == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	//initialize the hash table H
	H = hashtq_initializeTable(vexnum * 2);
	for(i=0;i<vexnum;i++){
		fgets(name,64,stdin);		//get the vertex name,it must end by newline
		namelen = strlen(name) - 1;
		if(namelen == 0){		//remove the newline
			fgets(name,64,stdin);		//get the vertex name,it must end by newline
			namelen = strlen(name) - 1;
		}
		name[namelen] = '\0';	//remove the newline
		//insert into hash table H
		hashtq_insert(name,Legal,i,H);
		grp->vertices[i].data = make_vertexType();	///////////////
		grp->vertices[i].data->name = makecopystring(name);	/////////////
		grp->vertices[i].data->flag = 0;		/////////////haven't enqueue
		//input the arc
		scanf("%d",&adjvex);
		if(adjvex != -1){
			p = make_arcNode(adjvex);
			scanf("%d",&weight);
			p->info = make_arcInfoType(weight);	//////////////
			grp->vertices[i].firstarc = p;
		}else{
			grp->vertices[i].firstarc = NULL;
			continue;
		}
		while((scanf("%d",&adjvex),adjvex != -1)){
			p->next = make_arcNode(adjvex);		//////////////////
			p = p->next;
			scanf("%d",&weight);
			p->info = make_arcInfoType(weight);
		}
	}//for
	return grp;
}

static AlGraph createUDGW(int vexnum,int arcnum){
	AlGraph grp;
	int i,namelen,adjvex,weight;
	char name[64];
	ArcNode p;
	grp = (AlGraph)malloc(sizeof(struct AlGraph_tag));
	if(grp == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	grp->vexnum = vexnum;
	grp->arcnum = arcnum;
	grp->kind = UDGW;
	grp->vertices = (struct VNode_tag *)calloc(vexnum,sizeof(struct VNode_tag));
	if(grp->vertices == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	//initialize the hash table H
	H = hashtq_initializeTable(vexnum * 2);
	for(i=0;i<vexnum;i++){
		fgets(name,64,stdin);		//get the vertex name,it must end by newline
		namelen = strlen(name) - 1;
		if(namelen == 0){		//remove the newline
			fgets(name,64,stdin);		//get the vertex name,it must end by newline
			namelen = strlen(name) - 1;
		}
		name[namelen] = '\0';	//remove the newline
		//insert into hash table H
		hashtq_insert(name,Legal,i,H);
		grp->vertices[i].data = make_vertexType();	///////////////
		grp->vertices[i].data->name = makecopystring(name);	/////////////
		grp->vertices[i].data->flag = 0;		/////////////haven't enqueue
		//input the arc
		scanf("%d",&adjvex);
		if(adjvex != -1){
			p = make_arcNode(adjvex);
			scanf("%d",&weight);
			p->info = make_arcInfoType(weight);	//////////////
			grp->vertices[i].firstarc = p;
		}else{
			grp->vertices[i].firstarc = NULL;
			continue;
		}
		while((scanf("%d",&adjvex),adjvex != -1)){
			p->next = make_arcNode(adjvex);		//////////////////
			p = p->next;
			scanf("%d",&weight);
			p->info = make_arcInfoType(weight);
		}
	}//for
	return grp;
}

static AlGraph createUDG(int vexnum,int arcnum){
	AlGraph grp;
	int i,namelen,adjvex,weight;
	char name[64];
	ArcNode p;
	grp = (AlGraph)malloc(sizeof(struct AlGraph_tag));
	if(grp == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	grp->vexnum = vexnum;
	grp->arcnum = arcnum;
	grp->kind = UDG;
	grp->vertices = (struct VNode_tag *)calloc(vexnum,sizeof(struct VNode_tag));
	if(grp->vertices == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	//initialize the hash table H
	H = hashtq_initializeTable(vexnum * 2);
	for(i=0;i<vexnum;i++){
		fgets(name,64,stdin);		//get the vertex name,it must end by newline
		namelen = strlen(name) - 1;
		if(namelen == 0){		//remove the newline
			fgets(name,64,stdin);		//get the vertex name,it must end by newline
			namelen = strlen(name) - 1;
		}
		name[namelen] = '\0';	//remove the newline
		//insert into hash table H
		hashtq_insert(name,Legal,i,H);
		grp->vertices[i].data = make_vertexType();	///////////////
		grp->vertices[i].data->name = makecopystring(name);	/////////////
		grp->vertices[i].data->flag = 0;		/////////////haven't enqueue
		//input the arc
		scanf("%d",&adjvex);
		if(adjvex != -1){
			p = make_arcNode(adjvex);
			//scanf("%d",&weight);
			p->info = make_arcInfoType(0);	//////////////
               //p->info->arcid = getarcid(i,adjvex);    //////////////
			grp->vertices[i].firstarc = p;
               grp->vertices[i].data->last = p;
		}else{
			grp->vertices[i].firstarc = NULL;
			grp->vertices[i].data->last = NULL;
			continue;
		}
		while((scanf("%d",&adjvex),adjvex != -1)){
			p->next = make_arcNode(adjvex);		//////////////////
			p = p->next;
			//scanf("%d",&weight);
			p->info = make_arcInfoType(0);
               //p->info->arcid = getarcid(i,adjvex);    //////////////
		}
	}//for
	return grp;
}

//create the record table
PRTable prt_create(int size,int start){
	PRTable T;
	int i;
	if(start < 0 || start >= size){
		fprintf(stderr,"invalid start in prt_create\n");
		return NULL;
	}
	T = (struct PRTable_tag *)malloc(sizeof(struct PRTable_tag));
	if(T == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	T->list = (struct PathRecordTable_tag *)calloc(size,sizeof(struct PathRecordTable_tag));
	if(T->list == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	for(i=0;i<size;i++){
		T->list[i].known = 0;
		if(i == start){
			T->list[i].dist = 0;
		}else{
			T->list[i].dist = INFINITE;
		}
		T->list[i].path = -1;
	}
	T->size = size;
	T->startindex = start;
	return T;
}

void prt_dispose(PRTable T){
	if(T){
		if(T->list){
			free(T->list);
		}
		free(T);
	}
}

void prt_printThePath(AlGraph G,PRTable T,int start,int des){
	int i;
	Stack S;
	S = arr_createStack(G->vexnum);
	if(start < 0 || start >= G->vexnum || des < 0 || des >= G->vexnum){
		fprintf(stderr,"invalid start or des in prt_printThePath\n");
		exit(-1);
	}
	arr_push(des,S);
	i = des;
	while(T->list[i].path != -1 && T->list[i].path != start){
		arr_push(T->list[i].path,S);
		i = T->list[i].path;
	}
	if(T->list[i].path == -1){
		printf("%s->INIFITE\n",G->vertices[start].data->name);
		arr_disposeStack(S);
		return;
	}else if(T->list[i].path == start){
		arr_push(start,S);
	}
	while(!arr_isEmpty(S)){
		i = arr_topAndPop(S);
		printf("%s->",G->vertices[i].data->name);
	}
	printf("\n");
	arr_disposeStack(S);
}

void prt_printtab(AlGraph G,PRTable T){
     int i;
     printf("v\t\tknown\t\tdist\t\tpath\n");
     for(i=0;i<T->size;i++){
          printf("%d\t\t%d\t\t%d\t\t%d\n",i,T->list[i].known,T->list[i].dist,T->list[i].path);
     }
}



















static VertexType make_vertexType(){
	VertexType p;
	p = (struct VertexDataType_tag *)malloc(sizeof(struct VertexDataType_tag));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	p->name = NULL;
	return p;
}

static ArcNode make_arcNode(int adjvex){
	ArcNode p;
	p = (struct ArcNode_tag *)malloc(sizeof(struct ArcNode_tag));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	p->adjvex = adjvex;
	p->next = NULL;
	p->info = NULL;
	return p;
}
static char *makecopystring(char *str){
	char *s;
	int len;
	len = strlen(str);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if(s == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	strcpy(s,str);
	return s;
}

static ArcInfoType make_arcInfoType(int weight){
	ArcInfoType p;
	p = (struct ArcInfo_tag *)malloc(sizeof(struct ArcInfo_tag));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	p->weight = weight;
	return p;
}
static void free_vertexType(VertexType ptr){
	if(ptr){
		if(ptr->name){
			free(ptr->name);
		}
		free(ptr);
	}
}
static void free_arcNode(ArcNode ptr){
	if(ptr){
		if(ptr->info){
			free(ptr->info);
		}
		free(ptr);
	}
}
/*
//get the unique id for arc
static int getarcid(int i,int j,int arcs){
     static int count = arcs;
     static int *hash = NULL;
     if(hash == NULL){
          hash = (int *)calloc(nextprime(2*arcs),sizeof(int));
          if(hash == NULL){
               fprintf(stderr,"getarcid:malloc failed\n");
               exit(1);
          }
     }
}

*/











