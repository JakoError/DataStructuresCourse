//
// Created by JakoError on 2021/3/11.
//

#ifndef DATASTRUCTURES_LIST_H
#define DATASTRUCTURES_LIST_H
#define MAXSIZE 100
#define ElemType int

typedef struct seqlist {
    ElemType elem[MAXSIZE];
    int last;
} SeqList;

struct lnklist {
    ElemType data;
    struct lnklist *next;
};
typedef struct lnklist Node;
typedef struct lnklist *LinkList;

void del_x2y(SeqList *L, ElemType x, ElemType y);

void del_dupnum(SeqList *L);

void odd_even(SeqList *L);

void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk);

int lnk_search(LinkList L, int k, ElemType* p_ele);

void lnk_merge(LinkList A, LinkList B, LinkList C);

#endif //DATASTRUCTURES_LIST_H
