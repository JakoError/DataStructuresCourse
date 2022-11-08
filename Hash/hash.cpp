#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "hash.h"

long hash_string(const char *str) {
    long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if (hash < 0)
        hash *= -1;
    return hash;
}

HashTable *create_hash(int size) {
    if (size <= 0) return NULL;
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (!ht) return NULL;
    ht->bucket = (HashEntry **) malloc(sizeof(HashEntry *) * size);
    if (!ht->bucket) {
        free(ht);
        return NULL;
    }
    ht->size = size;
    ht->last_error = HASH_OK;
    return ht;
}

HASH_RESULT hash_add_int(HashTable *table, const char *key, int value) {
    if (!table || table->size <= 0 || !table->bucket) return HASH_ERROR;
    long idx = hash_string(key) % table->size;
    //为null必定不存在直接保存
    if (!table->bucket[idx]) {
        table->bucket[idx] = (HashEntry *) malloc(sizeof(HashEntry));
        table->bucket[idx]->key.str_value = (char *) malloc(sizeof(key));
        strcpy(table->bucket[idx]->key.str_value, key);
        table->bucket[idx]->value.int_value = value;
        return HASH_ADDED;
    }
    //不为null进行链式比较
    HashEntry *p = table->bucket[idx];
    while (true) {
        //key相同才能出去
        if (strcmp(p->key.str_value, key) == 0) {
            if (p->value.int_value == value)
                return HASH_ALREADY_ADDED;
            p->value.int_value = value;
            return HASH_REPLACED_VALUE;
        }
        if (p->next) p = p->next;
        else break;//key都不相同哈希冲突
    }
    p = p->next = (HashEntry *) malloc(sizeof(HashEntry));
    p->key.str_value = (char *) malloc(sizeof(key));
    strcpy(p->key.str_value, key);
    p->value.int_value = value;
    return HASH_ADDED;
}