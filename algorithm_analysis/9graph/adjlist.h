#ifndef ADJLIST_H
#define ADJLIST_H
#ifdef INT_MAX
#define INFINITE INT_MAX
#else
#define INFINITE 2147483647
#endif
struct ArcNode_tag;

//the vertex data structure
struct VertexDataType_tag{
	char *name;	//vertex name
     struct ArcNode_tag *last;
	int flag;
};
typedef struct VertexDataType_tag *VertexType;
//
//the arc information structure
struct ArcInfo_tag{
	int weight;	
     int arcid;
};
typedef struct ArcInfo_tag *ArcInfoType;

//the arc node structure
struct ArcNode_tag{
	int adjvex;	//the location the arc point to
	struct ArcNode_tag *next;
	ArcInfoType info;	//the arc information
};
typedef struct ArcNode_tag *ArcNode;
typedef ArcNode ArcPtr;

//the vertex node structure
struct VNode_tag{
	VertexType data;
	ArcNode firstarc;
};
typedef struct VNode_tag *VNodeList;

enum GraphType_enum {DG,DGW,DN,UDG,UDGW,UDN};
typedef enum GraphType_enum GraphType;

//the graph structure
struct AlGraph_tag{
	VNodeList vertices;
	int vexnum;	//the number of vertes
	int arcnum;	//the number of arc
	GraphType kind;
};
typedef struct AlGraph_tag *AlGraph;

//the record table
struct PathRecordTable_tag{
	int known;
	int dist;
	int path;
};
typedef struct PathRecordTable_tag *PREntry;
struct PRTable_tag{
	PREntry list;
	int size;
	int startindex;
};
typedef struct PRTable_tag *PRTable;




AlGraph graph_create(GraphType kind,int vexnum,int arcnum);
void graph_dispose(AlGraph G);
PRTable prt_create(int size,int start);
void prt_dispose(PRTable T);
void prt_printThePath(AlGraph G,PRTable T,int start,int des);
void prt_printtab(AlGraph G,PRTable T);
/*
ArcPtr graph_nextarc(ArcPtr cur);
int graph_vexnum(AlGraph G);
int graph_arcnum(AlGraph G);
GraphType graph_kind(AlGraph G);
*/

#endif
