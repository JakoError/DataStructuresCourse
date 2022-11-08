#include "adjList.h"
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>

#pragma warning(disable:4996)
using namespace std;

bool insert_vertex(ListGraph *G, VertexType v) {
    if (locate_vertex(G, v) != -1 || G->vexnum >= MAX_VERTEX_NUM)
        return false;
    G->vertex[G->vexnum].data = v;
    G->vertex[G->vexnum].firstarc = NULL;
    G->vexnum++;
    return true;
}


bool insert_arc(ListGraph *G, VertexType v, VertexType w) {
    int vi = locate_vertex(G, v), wi = locate_vertex(G, w);
    if (vi == -1 || wi == -1)
        return false;

    ArcNode *pv = G->vertex[vi].firstarc;
    if (pv == NULL)
        pv = G->vertex[vi].firstarc = (ArcNode *) malloc(sizeof(ArcNode));
    else {
        while (true) {
            if (pv->adjvex == wi) return false;//已存在阻断
            if (pv->nextarc) pv = pv->nextarc;
            else break;
        }
        pv = pv->nextarc = (ArcNode *) malloc(sizeof(ArcNode));
    }

    if (G->type == UDG) {
        ArcNode *pw = G->vertex[wi].firstarc;
        if (pw == NULL)
            pw = G->vertex[wi].firstarc = (ArcNode *) malloc(sizeof(ArcNode));
        else {
            while (true) {
                if (pw->adjvex == vi) return false;//已存在阻断
                if (pw->nextarc) pw = pw->nextarc;
                else break;
            }
            pw = pw->nextarc = (ArcNode *) malloc(sizeof(ArcNode));
        }
        pw->adjvex = vi, pw->nextarc = NULL, pw->info = NULL;
    }

    pv->adjvex = wi, pv->nextarc = NULL, pv->info = NULL;

    G->arcnum++;
    return true;
}

int freeNode(ArcNode *p) {
    int num = 0;
    if (p == NULL) return 0;
    num += freeNode(p->nextarc);
    free(p);
    return num + 1;
}

bool del_vertex(ListGraph *G, VertexType v) {
    int vi = locate_vertex(G, v);
    if (vi == -1) return false;
    //free vi
    G->arcnum -= freeNode(G->vertex[vi].firstarc);
    //vertex向前移
    for (int i = vi + 1; i < G->vexnum; ++i)
        G->vertex[i - 1] = G->vertex[i];

    //改变adjvex
    G->vexnum--;
    for (int i = 0; i < G->vexnum; ++i) {
        ArcNode *p = G->vertex[i].firstarc, *pre = NULL;
        while (p) {
            if (p->adjvex == vi) {
                if (pre)
                    pre->nextarc = p->nextarc;
                else G->vertex[i].firstarc = p->nextarc;
                free(p);
                if (pre)
                    p = pre->nextarc;
                else p = G->vertex[i].firstarc;
                G->arcnum--;
            } else {
                p->adjvex -= p->adjvex > vi;
                pre = p;
                p = p->nextarc;
            }
        }
    }
    return true;
}

int main() {
    return 0;
}