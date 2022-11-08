//
// Created by JakoError on 2021/4/11.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "dsstring.h"

#pragma warning(disable:4996)

int len(char *a) {
    return sizeof(a);
}

/**
 * @discription 
 */
int main() {
    BLString *src = (BLString*)malloc(sizeof(BLString));
    Block *p = (Block*)malloc(sizeof(Block));
    p->ch[0] = 'a';
    p->ch[1] = 'b';
    p->ch[2] = 'c';
    p->ch[3] = 'd';
    src->head = p;
    p->next = (Block*)malloc(sizeof(Block));
    p = p->next;
    p->ch[0] = 'e';
    p->ch[1] = 'f';
    p->ch[2] = 'g';
    p->ch[3] = '#';
    src->tail = p;
    src->len = 7;

    BLString *sub = (BLString*)malloc(sizeof(BLString));
    blstr_substr(*src,4,5,sub);
    printf("aaa");
    return EXIT_SUCCESS;
}
