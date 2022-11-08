//
// Created by JakoError on 2021/4/11.
//

#ifndef DATASTRUCTURE_DSSTRING_H
#define DATASTRUCTURE_DSSTRING_H

#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

typedef struct block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct block *next;    //块的指针域
} Block;

typedef struct {
    Block *head;        // 串的头指针
    Block *tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString *T);
bool blstr_substr(BLString src, int pos, int len, BLString *sub);

int getLength(const char *str);
int str_compare(const char* ptr1, const char* ptr2);
int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr);

#endif //DATASTRUCTURE_DSSTRING_H
