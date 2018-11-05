#ifndef ADJLIST_H
#define ADJLIST_H

//the vertex data structure
struct VertexDataType_tag{
	char *name;	//vertex name
};
typedef struct VertexDataType_tag *VertexType;
//
//the arc information structure
struct ArcInfo_tag{
	int weight;	
};
typedef struct ArcInfo_tag *ArcInfoType;

//the arc node structure
struct ArcNode_tag{
	int adjvex;	//the location the arc point to
	struct ArcNode_tag *next;
	ArcInfoType info;	//the arc information
};
typedef struct ArcNode_tag *ArcNode;

//the vertex node structure
struct VNode_tag{
	VertexType data;
	ArcNode firstarc;
};
typedef struct VNode_tag *VNodeList;

enum GraphType_enum {DG,DN,UDG,UDN};
typedef enum GraphType_enum GraphType;

//the graph structure
struct AlGraph_tag{
	VNodeList vertices;
	int vexnum;	//the number of vertes
	int arcnum;	//the number of arc
	GraphType kind;
};
typedef struct AlGraph_tag *AlGraph;




AlGraph graph_create(GraphType kind,int vexnum,int arcnum);

#endif
