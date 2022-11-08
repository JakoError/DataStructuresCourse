#include <cstdio>
#include <cstdlib>

#pragma warning(disable:4996)

typedef int ElemType;

// 非零元素结点结构
typedef struct OLNode {
    int row, col;
    ElemType value;
    struct OLNode *right, *down;
} OLNode, *OLink;

// 十字链表结构
typedef struct {
    OLink *rowhead, *colhead;
    int rows, cols, nums;
} CrossList, *PCrossList;

int init_cross_list(PCrossList L, const ElemType *A, int m, int n);

int init_cross_list2(PCrossList L, const ElemType *A, int m, int n);

int del_cross_list(PCrossList L, ElemType k);

int main() {
    PCrossList L = (PCrossList) malloc(sizeof(CrossList));
    int a[] = {1,0,0,7};
    init_cross_list(L, a, 2, 2);
    del_cross_list(L, 7);
    return EXIT_SUCCESS;
}

int init_cross_list(PCrossList L, const ElemType *A, int m, int n) {
    L->rows = m, L->cols = n, L->nums = 0;
    if (!(L->rowhead = (OLink *) malloc((m+1) * sizeof(OLink)))) exit(3);
    if (!(L->colhead = (OLink *) malloc((n+1) * sizeof(OLink)))) exit(3);
    for (int i = 0; i < m; ++i)
        L->rowhead[i] = NULL;
    for (int i = 0; i < n; ++i)
        L->colhead[i] = NULL;

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (A[n * i + j]) {
                OLink target = (OLink) malloc(sizeof(OLNode));
                //填充数据
                target->right = target->down = NULL;
                target->row = i;
                target->col = j;
                target->value = A[n * i + j];
                //插入
                if (!L->rowhead[i]) L->rowhead[i] = target;
                else {
                    OLink last = L->rowhead[i];
                    while (last->right) last = last->right;
                    last->right = target;
                }
                if (!L->colhead[j]) L->colhead[j] = target;
                else {
                    OLink last = L->colhead[j];
                    while (last->down) last = last->down;
                    last->down = target;
                }
                L->nums++;
            }
    return L->nums;
}
int del_cross_list(PCrossList L, ElemType k) {
    if (!L) return 0;
    int num = 0;
    //从row遍历
    for (int i = 0; i < L->rows; ++i)
        if (L->rowhead[i]) {
            //增加空头
            OLink preTargetRow = (OLink) malloc(sizeof(OLNode));
            preTargetRow->right = L->rowhead[i];
            while (preTargetRow && preTargetRow->right) {
                if (preTargetRow->right->value == k) {
                    OLink Target = preTargetRow->right;
                    //从行中删除Target(使用pre的惩罚)
                    if(L->rowhead[i]==Target) preTargetRow = L->rowhead[i] = Target->right;
                    else preTargetRow->right = Target->right;
                    //从列中删除Target(使用pre的惩罚)
                    if(L->colhead[Target->col]==Target) L->colhead[Target->col] = Target->down;
                    else{
                        OLink preTargetCol = (OLink) malloc(sizeof(OLNode));
                        preTargetCol->down = L->colhead[Target->col];
                        while (preTargetCol->down != Target) preTargetCol = preTargetCol->down;
                        preTargetCol->down = Target->down;
                    }
                    //free
                    free(Target);
                    num++;
                }else preTargetRow = preTargetRow->right;
            }
        }
    L->nums -= num;
    return num;
}