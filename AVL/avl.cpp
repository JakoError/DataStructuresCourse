#include <cstdlib>
#include <cstdio>
#include "avl.h"
#include <algorithm>

using namespace std;

node_t *avl_insert(node_t *root, int val) {
    node *nnode, *p, *A = root, *B, *C;
    nnode = (node *) malloc(sizeof(node));
    nnode->val = val;
    nnode->left = nnode->right = nnode->parent = NULL;
    nnode->height = 1;
    if (!root)
        return nnode;
    p = root;
    while (true) {
        int pbuf = (p->left ? p->left->height : 0) - (p->right ? p->right->height : 0);
        if (pbuf != 0) A = p;//记录A
        if (val < p->val) {
            if (!p->left) {
                p->left = nnode;
                break;
            }
            p = p->left;
        } else {
            if (!p->right) {
                p->right = nnode;
                break;
            }
            p = p->right;
        }
    }
    nnode->parent = p;

    if (p->left && p->right) return root;//已经平衡

    if (val < A->val)
        B = A->left;
    else B = A->right;
    p = A;
    while (p != nnode) {
        p->height++;
        if (val < p->val) p = p->left;
        else p = p->right;
    }

    int Abuf = (A->left ? A->left->height : 0) - (A->right ? A->right->height : 0);
    int Bbuf = (B->left ? B->left->height : 0) - (B->right ? B->right->height : 0);
    //LL
    if (Abuf == 2 && Bbuf == 1) {
        A->left = B->right;
        if (A->left) A->left->parent = A;
        B->right = A;
        A->height -= 2;
        B->height++;
        if (!A->parent) root = B;
        else if (A == A->parent->left) A->parent->left = B, B->parent = A->parent;
        else A->parent->right = B, B->parent = A->parent;
        A->parent = B;
    }
        //LR
    else if (Abuf == 2 && Bbuf == -1) {
        C = B->right;
        B->right = C->left;
        if (B->right) B->right->parent = B;
        A->left = C->right;
        if (A->left) A->left->parent = A;
        C->left = B, B->parent = C;
        C->right = A;

        A->height -= 2;
        B->height--;
        C->height++;

        if (!A->parent) root = C;
        else if (A == A->parent->left) A->parent->left = C, C->parent = A->parent;
        else A->parent->right = C, C->parent = A->parent;
        A->parent = C;
    }
        //RR
    else if (Abuf == -2 && Bbuf == -1) {
        A->right = B->left;
        if (A->right) A->right->parent = A;
        B->left = A;

        A->height -= 2;
        B->height++;

        if (!A->parent) root = B;
        else if (A == A->parent->left) A->parent->left = B, B->parent = A->parent;
        else A->parent->right = B, B->parent = A->parent;
        A->parent = B;
    }
        //RL
    else if (Abuf == -2 && Bbuf == 1) {
        C = B->left;
        A->right = C->left;
        if (A->right) A->right->parent = A;
        B->left = C->right;
        if (B->left) B->left->parent = B;
        C->right = B, B->parent = C;
        C->left = A;

        A->height -= 2;
        B->height--;
        C->height++;

        if (!A->parent) root = C;
        else if (A == A->parent->left) A->parent->left = C, C->parent = A->parent;
        else A->parent->right = C, C->parent = A->parent;
        A->parent = C;
    }
    return root;
}