#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include "graph.h"

#pragma warning(disable:4996)
using namespace std;

bool matrix_insert_vertex(MatrixGraph *G, VertexType v) {
    if (G->vexnum >= MAX_VERTEX_NUM || matrix_locate_vertex(G, v) != -1)//已经存在
        return false;
    G->vertex[G->vexnum++] = v;
    for (int i = 0; i < G->vexnum; ++i)
        G->arcs[i][G->vexnum-1] = G->arcs[G->vexnum-1][i] = 0;
    return true;
}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w) {
    int vi = matrix_locate_vertex(G, v), wi = matrix_locate_vertex(G, w);
    if (vi == -1 || wi == -1 || G->arcs[vi][wi] || (G->type == UDG && G->arcs[wi][vi]))
        return false;
    G->arcs[vi][wi] = 1;
    if (G->type == UDG)
        G->arcs[wi][vi] = 1;
    G->arcnum++;
    return true;
}

int main() {
    return 0;
}