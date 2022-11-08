//
// Created by JakoError on 2021/6/26.
//

#ifndef DATASTRUCTURE_MINBINHEAP_H
#define DATASTRUCTURE_MINBINHEAP_H
typedef struct _otherInfo {
    int i;
    int j;
} OtherInfo;

typedef struct _minHeapNode {
    int value;
    OtherInfo otherInfo;
} MinHeapNode, *PMinHeapNode;

typedef struct _minPQ {
    PMinHeapNode heap_array; // 指向堆元素数组
    int heap_size; // 当前堆中的元素个数
    int capacity;  //堆数组的大小
} MinHeap, *PMinHeap;

int parent(int i); //返回堆元素数组下标为 i 的结点的父结点下标
int left(int i);  //返回堆元素数组下标为 i 的结点的左子结点下标
int right(int i);  //返回堆元素数组下标为 i 的结点的右子结点下标
void swap_node(MinHeapNode *x, MinHeapNode *y);  //交换两个堆元素的值
void init_min_heap(PMinHeap pq, int capacity);
bool heap_insert_value(PMinHeap pq, int value);
void min_heapify(PMinHeap pq, int i);
#endif //DATASTRUCTURE_MINBINHEAP_H
