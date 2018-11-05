#include "adjlist.h"
#include "hashquad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static HashTQ H;

static AlGraph createDG(int vexnum,int arcnum);
//static AlGraph createDN(int vexnum,int arcnum);
//static AlGraph createUDG(int vexnum,int arcnum);
//static AlGraph createUDN(int vexnum,int arcnum);
static VertexType make_vertexType();
static ArcNode make_arcNode(int adjvex);
static char *makecopystring(char *str);

//initialize and create graph
AlGraph graph_create(GraphType kind,int vexnum,int arcnum){
	if(vexnum < 1){
		return NULL;
	}
	switch(kind){
		case DG:return createDG(vexnum,arcnum);break;
	//	case DN:return createDN(vexnum,arcnum);break;
	//	case UDG:return createUDG(vexnum,arcnum);break;
	//	case UDN:return createUDN(vexnum,arcnum);break;
		default:
			fprintf(stderr,"unkonw graph type\n");
			return NULL;
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
		name[namelen] = '\0';	//remove the newline
		//insert into hash table H
		hashtq_insert(name,Legal,i,H);
		grp->vertices[i].data = make_vertexType();	///////////////
		grp->vertices[i].data->name = makecopystring(name);	/////////////
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
	p->adjvex = -1;
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












