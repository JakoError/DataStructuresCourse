#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "minbinheap.h"

using namespace std;

int parent(int i) {
    return i / 2 - !(i % 2);
}

int left(int i) {
    return i << 1 | 1;
}

int right(int i) {
    return (i << 1 | 1) + 1;
}

void swap_node(MinHeapNode *x, MinHeapNode *y) {
    if (!x || !y) return;
    x->value = x->value ^ y->value;
    y->value = x->value ^ y->value;
    x->value = x->value ^ y->value;

    x->otherInfo.i = x->otherInfo.i ^ y->otherInfo.i;
    y->otherInfo.i = x->otherInfo.i ^ y->otherInfo.i;
    x->otherInfo.i = x->otherInfo.i ^ y->otherInfo.i;

    x->otherInfo.j = x->otherInfo.j ^ y->otherInfo.j;
    y->otherInfo.j = x->otherInfo.j ^ y->otherInfo.j;
    x->otherInfo.j = x->otherInfo.j ^ y->otherInfo.j;
}

void init_min_heap(PMinHeap pq, int capacity) {
    if (capacity <= 0) return;
    PMinHeapNode array = (PMinHeapNode) malloc(sizeof(MinHeapNode) * capacity);
    if (!array) return;
    pq->heap_array = array;
    for (int i = 0; i < capacity; ++i)
        pq->heap_array[i].value = pq->heap_array[i].otherInfo.i = pq->heap_array[i].otherInfo.j = 0;
    pq->heap_size = 0;
    pq->capacity = capacity;
}

bool heap_insert_value(PMinHeap pq, int value) {
    if (pq->heap_size >= pq->capacity) return false;
    pq->heap_array[pq->heap_size++].value = value;
    for (int i = pq->heap_size / 2; i >= 0; --i) {
        int p = i;
        while (p < pq->heap_size && (right(p) < pq->heap_size || left(p) < pq->heap_size)) {
            int index;
            if (right(p) >= pq->heap_size)
                index = left(p);
            else
                index = pq->heap_array[left(p)].value < pq->heap_array[right(p)].value ? left(p) : right(p);
            if (pq->heap_array[index].value < pq->heap_array[p].value)
                swap_node(&pq->heap_array[p], &pq->heap_array[index]);
            else break;
            p = index;
        }
    }
    return true;
}

void min_heapify(PMinHeap pq, int i) {
    for (int j = pq->heap_size / 2; j >= 0; --j) {
        int p = j;
        while (p < pq->heap_size && (right(p) < pq->heap_size || left(p) < pq->heap_size)) {
            int index;
            if (right(p) >= pq->heap_size)
                index = left(p);
            else
                index = pq->heap_array[left(p)].value < pq->heap_array[right(p)].value ? left(p) : right(p);
            if (pq->heap_array[index].value < pq->heap_array[p].value)
                swap_node(&pq->heap_array[p], &pq->heap_array[index]);
            else break;
            p = index;
        }
    }
}

void swap(int *a, int *b) {
    if (*a == *b) return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void quickSort(int *array, int left, int right) {
    if (left < right) {
        int pivot = array[left];
        int low = left, high = right;
        while (low < high) {
            while (array[high] >= pivot && low < high)
                high--;
            while (array[low] <= pivot && low < high)
                low++;
            swap(array[low], array[high]);
        }
        swap(array[low], array[left]);
        quickSort(array, left, low - 1);
        quickSort(array, low + 1, right);
    }
}

void merge2arrays(int *arr, int l1, int r1, int l2, int r2) {
    int i, start = l1, num = r1 + r2 - l1 - l2 + 2;
    int *buf = (int *) malloc(sizeof(int) * num + 1);
    for (i = 0; i < num; ++i) {
        if (l1 > r1 || l2 > r2) break;
        if (arr[l1] <= arr[l2]) buf[i] = arr[l1++];
        else buf[i] = arr[l2++];
    }
    if (l1 <= r1)
        while (l1 <= r1) buf[i++] = arr[l1++];
    else
        while (l2 <= r2) buf[i++] = arr[l2++];
    for (i = 0; i < num; ++i)
        arr[start + i] = buf[i];
}

void re_merge(int *arr, int n, int k, int l, int r) {
    if (l == r) return;
    if (l + 1 == r) {
        merge2arrays(arr, l * k, r * k - 1, r * k, (r + 1) * k - 1);
        return;
    }
    int mid = (l + r) / 2;
    re_merge(arr, n, k, l, mid);
    re_merge(arr, n, k, mid + 1, r);
    merge2arrays(arr, l * k, (mid + 1) * k - 1, (mid + 1) * k, (r+1) * k-1);
}

void merge_arrays(const int *arr, int n, int k, int *output) {
    if (!arr) return;
    for (int i = 0; i < n * k; ++i) output[i] = arr[i];
    re_merge(output, n, k, 0, n - 1);
}

int a[9] = {97, 100, 107, 15, 16, 24, 27, 28, 33};
int *result = (int *) malloc(sizeof(int) * 9);

int main() {
    result = (int *) malloc(sizeof(int) * 9);
    merge_arrays(a, 3, 3, result);
    for (int i = 0; i < 9; ++i) {
        printf("%d ", result[i]);
    }
    return 0;
}