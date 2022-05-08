#include "hashtablib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 200003

unsigned int KRHash(char* s)
{
    unsigned int h = 0, hash_mul = 31;
    while (*s)
        h = h * hash_mul + (unsigned int)*s++;
    return h % HASH_SIZE;
}

unsigned int KRHash(char* s)
{
    unsigned long hash = 5381;
    int c;

    while (c = *s++)
        hash = ((hash << 5) + hash) + c;

    return hash % HASH_SIZE;
}

void hashtabInit(struct listnode** hashtab)
{
    for (int i = 0; i < HASH_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtabAdd(struct listnode** hashtab, char* key, int value)
{
    struct listnode* node;

    unsigned int index = KRHash(key);
    node = malloc(sizeof(*node));

    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode* hashtabLookup(struct listnode** hashtab, char* key)
{
    struct listnode* node;

    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0)
            return node;
    }
    return NULL;
}

void hashtabDelete(struct listnode** hashtab, char* key)
{
    struct listnode *node, *prev = NULL;
    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}