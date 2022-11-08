//
// Created by JakoError on 2021/3/30.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H
#define ElemType int

typedef struct _QueueNode {
    ElemType data;          //数据域
    struct _QueueNode *next;      //指针域
} LinkQueueNode, *LinkQueue;


bool init_queue(LinkQueue *LQ);

bool enter_queue(LinkQueue *LQ, ElemType x);

bool leave_queue(LinkQueue *LQ, ElemType *x);

#endif //DATASTRUCTURE_QUEUE_H
