#include "hashtablib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashtabInit(struct listnode** hashtab)
{
    for (int i = 0; i < 200000; i++)
        hashtab[i] = NULL;
}

void hashtabAdd(struct listnode** hashtab, char* key, int value)
{
    struct listnode* node;

    int index = KRHash(key);
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