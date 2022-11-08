#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <random>
#include "list.h"
#include "queue.h"
#include "stack.h"

#pragma warning(disable:4996)
using namespace std;


void printList(LinkList list, int length);

void printList(SeqList list, int length);

/**
 * @discription 测试数据
 */
int main() {
    char str[30];
//    gets_s(str,30);
//    printf("%d",compute_reverse_polish_notation(str));
    for (int i = 0; i < 1000; ++i) {
        printf("\a");
    }
    return 0;
}
void printList(LinkList list, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n----------------\n");
}

void printList(SeqList list, int length) {
    for (int i = 0; i < length; ++i)
        printf("%d ", list.elem[i]);
    printf("\n----------------\n");
}