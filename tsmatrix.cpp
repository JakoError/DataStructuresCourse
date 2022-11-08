#include <cstdio>
#include <cstdlib>

#pragma warning(disable:4996)

#define ElemType int
#define MAXSIZE 100          //假设非零元个数的最大值为100
typedef struct {
    int i, j;                                    //非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;                        //非零元的值
} Triple;

typedef struct {
    Triple data[MAXSIZE];            // 非零元三元组表
    int m, n, len;                            // 矩阵的行数、列数和非零元个数
} TSMatrix;

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ);

/**
 * @discription
 */
int main() {
    TSMatrix  *pM = (TSMatrix*) malloc(sizeof(TSMatrix));
    TSMatrix  *pN = (TSMatrix*) malloc(sizeof(TSMatrix));
    TSMatrix  *pQ = (TSMatrix*) malloc(sizeof(TSMatrix));
    pM->m = pN->m = 5;
    pM->n = pN->n = 5;
    pM->len = 2;
    pN->len = 7;

    pM->data[0].i = 1;
    pM->data[0].j = 3;
    pM->data[0].e = 20;

    pM->data[1].i = 5;
    pM->data[1].j = 3;
    pM->data[1].e = 19;

    pN->data[0].i = 1;
    pN->data[0].j = 1;
    pN->data[0].e = 15;

    pN->data[1].i = 1;
    pN->data[1].j = 2;
    pN->data[1].e = 43;

    pN->data[2].i = 2;
    pN->data[2].j = 4;
    pN->data[2].e = 25;

    pN->data[3].i = 3;
    pN->data[3].j = 3;
    pN->data[3].e = 44;

    pN->data[4].i = 3;
    pN->data[4].j = 4;
    pN->data[4].e = 42;

    pN->data[5].i = 4;
    pN->data[5].j = 4;
    pN->data[5].e = 33;

    pN->data[6].i = 5;
    pN->data[6].j = 3;
    pN->data[6].e = 4;

    add_matrix(pM,pN,pQ);
    return EXIT_SUCCESS;
}

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ) {
    if (!pM || !pN || pM->m != pN->m || pM->n != pN->n)
        return false;

    if (!pM->len) {
        *pQ = *pN;
        return true;
    }
    if (!pN->len) {
        *pQ = *pM;
        return true;
    }

    pQ->m = pM->m;
    pQ->n = pM->n;
    pQ->len = 0;

    int i = 0, j = 0;
    while (i != pM->len && j != pN->len) {
        if (pM->data[i].i == pN->data[j].i && pM->data[i].j == pN->data[j].j) {
            if (pM->data[i].e + pN->data[j].e!=0) {
                pQ->data[pQ->len] = pM->data[i];
                pQ->data[pQ->len].e += pN->data[j].e;
                pQ->len++;
            }
            i++, j++;
        } else if (pM->data[i].i<pN->data[j].i||((pM->data[i].i==pN->data[j].i)&&pM->data[i].j<pN->data[j].j))
            pQ->data[pQ->len++] = pM->data[i++];
        else
            pQ->data[pQ->len++] = pN->data[j++];
    }
    if (i != pM->len || j != pN->len) {
        if (i != pM->len) {
            while (i < pM->len)
                pQ->data[pQ->len++] = pM->data[i++];
        } else {
            while (j < pN->len)
                pQ->data[pQ->len++] = pN->data[j++];
        }
    }
    return true;
}
