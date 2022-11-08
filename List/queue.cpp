//
// Created by JakoError on 2021/3/30.
//
#include <cstdlib>
#include <cstdio>
#include "queue.h"

bool init_queue(LinkQueue *LQ) {
    LinkQueueNode *newNode = (LinkQueueNode *) malloc(sizeof(LinkQueueNode));
    if (!newNode)
        return false;
    *LQ = newNode;
    (*LQ)->next = *LQ;
    return true;
}

bool enter_queue(LinkQueue *LQ, ElemType x) {
    if (!LQ || !*LQ) return false;
    LinkQueueNode *newNode = (LinkQueueNode *) malloc(sizeof(LinkQueueNode));
    if (!newNode) return false;
    newNode->data = x;
    newNode->next = (*LQ)->next;
    (*LQ)->next = newNode;
    *LQ = newNode;
    return true;
}

bool leave_queue(LinkQueue *LQ, ElemType *x) {
    if (!LQ || !*LQ || !x || (*LQ)->next == *LQ)
        return false;
    LinkQueueNode *p = (*LQ)->next->next;
    *x = p->data;
    if (p == *LQ) {
        *LQ = (*LQ)->next;
        (*LQ)->next = *LQ;
    } else
        (*LQ)->next->next = p->next;
    free(p);
    return true;
}
