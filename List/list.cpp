#include <cstdlib>
#include <cstdio>
#include "list.h"


/**
 * 顺序表 删除指定范围
 */
void del_x2y(SeqList *L, ElemType x, ElemType y) {
    int set = 0;
    for (int i = 0; i <= L->last; ++i)
        if (L->elem[i] < x || L->elem[i] > y)
            L->elem[set++] = L->elem[i];
    L->last = set - 1;
}

/**
 * 顺序表 删除重复
 */
void del_dupnum(SeqList *L) {
    int set = 0;
    for (int i = 1; i <= L->last; ++i)
        if (L->elem[i] != L->elem[set])
            L->elem[++set] = L->elem[i];
    L->last = set;
}

/**
 * 顺序表 数据调整
 */
 /*
void odd_even(SeqList *L) {
    int left = 0, right = L->last;
    while (left != right) {
        while (L->elem[left] % 2 && left != right) left++;
        while (!(L->elem[right] % 2) && left != right) right--;
        if (left != right) {
            L->elem[left] ^= L->elem[right];
            L->elem[right] ^= L->elem[left];
            L->elem[left] ^= L->elem[right];
        }
    }
}
*/
void odd_even(SeqList *L) {
    int index = 0;
    for (int i = 0; i <= L->last; ++i) {
        if (L->elem[i]%2){
            if (i!=index){
                L->elem[i] ^= L->elem[index];
                L->elem[index] ^= L->elem[i];
                L->elem[i] ^= L->elem[index];
            }
            index++;
        }
    }
}

/**
 * 链表 删除范围内结点 若非递增排序
 */
void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk) {
    while (L != NULL && L->data > mink && L->data < maxk) L = L->next;
    LinkList p = L, check;
    while (p->next != NULL) {
        check = p->next;
        if (check->data > maxk) return;
        if (check->data > mink && check->data < maxk) {
            p->next = check->next;
            free(check);
        } else
            p = check;
    }
}

/**
 * 链表 倒数查找
 * 三种方法
 * 1.把整个list倒过来（题目不改变链表）
 * 2.把所有数存在数组（不适合过大链表）
 * 3.计数后顺数读取
 */
int lnk_search(LinkList L, int k, ElemType *p_ele) {
    int length = 0;
    LinkList p = L;
    while (p != NULL) {
        p = p->next;
        length++;
    }
    if (length < k) return 0;
    p = L;
    for (int i = 0; i < length - k; ++i)
        p = p->next;
    *p_ele = p->data;
    return 1;
}

/**
 * 链表 合并 并不保留AB不变
 */

void lnk_merge(LinkList A, LinkList B, LinkList C) {
   if (A==NULL){
       C = B;
       return;
   }
   if (B==NULL){
       C = A;
       return;
   }
   LinkList pA = A->next, pB = B->next,pC = C;
   while (true) {
       if (pA!=NULL){
           pC->next = pA;
           pA = pA->next;
           pC = pC->next;
       }
       else break;
       if (pB!=NULL){
           pC->next = pB;
           pB = pB->next;
           pC = pC->next;
       }
       else break;
   }
}
/*
void lnk_merge(LinkList A, LinkList B, LinkList C) {
    *C = *A;
    LinkList pC = C, pB = B;

    while (B != NULL && pC != NULL) {
        pB = B;
        B = B->next;
        if (pC->next == NULL) {
            pC->next = pB;
            return;
        }
        pB->next = pC->next;
        pC->next = pB;
        pC = pC->next->next;
    }
}
*/
/*
void lnk_merge(LinkList A, LinkList B, LinkList C) {
    LinkList pA = A, pB = B, pC = C;
    while (pA != NULL || pB != NULL) {
        if (pA != NULL) {
            LinkList temp = (LinkList) malloc(sizeof(LinkList));
            temp->next = NULL;
            temp->data = pA->data;

            pC->next = temp;

            pC = pC->next;
            pA = pA->next;
        }
        if (pB != NULL) {
            LinkList temp = (LinkList) malloc(sizeof(LinkList));
            temp->next = NULL;
            temp->data = pB->data;

            pC->next = temp;

            pC = pC->next;
            pB = pB->next;
        }
    }
    *C = *C->next;
}
 */