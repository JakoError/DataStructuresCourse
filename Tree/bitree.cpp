#include "bitree.h"
#include <cstdio>
#include <cstdlib>

#pragma warning(disable:4996)

/**
 * @discription
 */
int main() {

    return EXIT_SUCCESS;
}

void pre_order(BiTree root) {
    if (!root) return;
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    init_stack(stack);

    BiTNode *visitNode;
    push(stack, root);
    do {
        pop(stack, &visitNode);
        visit_node(visitNode);
        if (visitNode->right)
            push(stack, visitNode->right);
        if (visitNode->left) {
            push(stack, visitNode->left);
        }
    } while (!is_empty(stack));
}

bool path1(BiTNode *root, BiTNode *node, Stack *s) {
    if (!root) return false;
    if (root == node) {
        push(s, root);
        return true;
    }
    if (root->left || root->right) {
        push(s, root);
        if (root->left && path(root->left, node, s))
            return true;
        if (root->right && path(root->right, node, s))
            return true;
        BiTNode *temp;
        pop(s, &temp);
    }
    return false;
}

bool path(BiTNode *root, BiTNode *node, Stack *s) {
    BiTNode *p = root, *child;
    do {
        while (p) {
            push(s, p);
            if (p == node) return true;
            p = p->left;
        }
        top(s, &p);
        if (!p->right)
            while (pop(s, &child) && top(s, &p) && p->right == child);
        p = p->right;
    } while (!is_empty(s));
    return false;
}

BiTNode *nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q) {
    Stack *sp = (Stack *) malloc(sizeof(Stack));
    Stack *sq = (Stack *) malloc(sizeof(Stack));
    init_stack(sp);
    init_stack(sq);
    if (!path(root, p, sp) || !path(root, q, sq))
        return NULL;
    int index = 0;
    while (sp->elem[index] == sq->elem[index])index++;
    return sp->elem[index - 1];
}

BiTNode *transform(CSNode *root) {
    // creat root and queue in
    if (!root) return NULL;
    BiTNode *biroot = (BiTNode *) malloc(sizeof(BiTNode));
    biroot->left = biroot->right = NULL;
    biroot->data = root->data;

    Queue *csQ = create_queue();
    Queue *biQ = create_queue();
    add_queue(csQ, root);
    add_queue(biQ, biroot);

    while (!is_empty_queue(csQ)) {
        CSNode *csP = (CSNode *) del_queue(csQ);
        BiTNode *biP = (BiTNode *) del_queue(biQ);
        if (csP->children[0]) {
            BiTNode *biChild = (BiTNode *) malloc(sizeof(BiTNode));
            biChild->right =biChild->left= NULL;
            biChild->data = csP->children[0]->data;
            biP->left = biChild;
            add_queue(csQ, csP->children[0]);
            add_queue(biQ, biChild);
            biP = biChild;
            for (int i = 1; i < MAX_CHILDREN_NUM && csP->children[i]; ++i) {
                add_queue(csQ, csP->children[i]);

                biChild = (BiTNode *) malloc(sizeof(BiTNode));
                biChild->right =biChild->left= NULL;
                biChild->data = csP->children[i]->data;
                biP->right = biChild;
                add_queue(biQ, biChild);
                biP = biChild;
            }
        }
    }
    free(csQ);
    free(biQ);
    return biroot;
}
