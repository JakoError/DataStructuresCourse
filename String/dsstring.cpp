//
// Created by JakoError on 2021/4/11.
//

#include <cstdlib>
#include "dsstring.h"

int str_compare(const char *ptr1, const char *ptr2) {
    int bias = 'A' - 'a';
    int i;
    for (i = 0; ptr1[i] != '\0' && ptr2[i] != '\0'; ++i) {
        if (ptr1[i] == ptr2[i]) continue;
        int n1 = ptr1[i] - 'a', n2 = ptr2[i] - 'a';
        if (ptr1[i] >= 'A' && ptr1[i] <= 'Z')
            n1 -= bias;
        if (ptr2[i] >= 'A' && ptr2[i] <= 'Z')
            n2 -= bias;
        if (n1 == n2) continue;
        return ptr1[i] - ptr2[i];
    }
    if (ptr1[i] == '\0' && ptr2[i] == '\0')
        return 0;
    if (ptr1[i] == '\0')
        return -1;
    if (ptr2[i] == '\0')
        return 1;
}

int getLength(const char *str) {
    int len = -1;
    while (str[++len] != '\0');
    return len;
}

//其实在outlen<inlen时可优化，但const限制了复制操作，反而使操作更加麻烦
int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr) {
    outlen--;
    int times = 0, outi = 0, ini = 0, inLen = getLength(in), oldlen = getLength(oldstr), newlen = getLength(
            newstr), maxTimes = inLen;
    if (newlen > oldlen)
        maxTimes = (outlen - inLen) / (newlen - oldlen);
    while (in[ini] != '\0' && outi < outlen) {
        int j = -1;
        if (in[ini] == oldstr[0])
            for (j = 0; j < oldlen; ++j)
                if (in[ini + j] != oldstr[j]) {
                    j = -1;
                    break;
                }
        if (j != -1 && times < maxTimes) {
            for (j = 0; j < newlen; j++)
                out[outi + j] = newstr[j];
            ini += oldlen;
            outi += newlen;
            times++;
        } else
            out[outi++] = in[ini++];
    }
    out[outi] = '\0';
    return times;
}

void blstr_init(BLString *T) {
    T->len = 0;
    T->head = nullptr;
    T->tail = nullptr;
}

bool blstr_substr(BLString src, int pos, int len, BLString *sub) {
    if (!src.len || !len || !src.head || !src.tail || !sub || pos >= src.len)
        return false;
    sub->len = 0;

    int start = pos / BLOCK_SIZE;
    Block *sBlock = src.head;
    while (start--)sBlock = sBlock->next;

    int i = pos % BLOCK_SIZE, j;
    Block *p = (Block *) malloc(sizeof(Block));
    sub->head = p;
    while (len > 0) {
        if (i == 4) {
            if (sBlock == src.tail)
                break;
            sBlock = sBlock->next;
            i = 0;
        }
        if (sBlock->ch[i] == BLS_BLANK)
            break;
        if (j == 4) {
            p->next = (Block *) malloc(sizeof(Block));
            p = p->next;
            j = 0;
        }

        p->ch[j++] = sBlock->ch[i++];
        sub->len++;
        --len;
    }
    sub->tail = p;
    while (j < 4) sub->tail->ch[j++] = BLS_BLANK;
    return true;
}