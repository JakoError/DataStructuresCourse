//
// Created by JakoError on 2021/6/20.
//

#ifndef DATASTRUCTURE_AVL_H
#define DATASTRUCTURE_AVL_H
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} node_t;

//向根为 root 的平衡二叉树插入新元素 val，成功后返回新平衡二叉树根结点
node_t *avl_insert(node_t *root, int val);

#endif //DATASTRUCTURE_AVL_H
