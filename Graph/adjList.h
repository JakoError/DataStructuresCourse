#ifndef DATASTRUCTURE_ADJLIST_H
#define DATASTRUCTURE_ADJLIST_H
#define MAX_VERTEX_NUM 1000
typedef int VertexType;
typedef char* InfoPtr;

typedef enum {
    DG, UDG
} GraphType;

typedef struct ArcNode {
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode;

typedef struct {
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
} ListGraph;

int locate_vertex(ListGraph *G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool insert_vertex(ListGraph *G, VertexType v);

bool insert_arc(ListGraph *G, VertexType v, VertexType w);
bool del_vertex(ListGraph *G, VertexType v); //删除顶点 v

#endif //DATASTRUCTURE_ADJLIST_H
