#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trie.h"
#include <string.h>
#include <stdint.h>
#include <limits.h>

trie *trie_create()
{
    trie *node;
    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->ch = '\0';
    node->value = NULL;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

char *trie_lookup(trie *root, char *key)
{
    trie *node = NULL, *list = NULL;
    for (list = root; *key != '\0'; key++)
    {
        for (node = list; node != NULL; node = node->sibling)
            if (node->ch == *key)
                break;
        if (node != NULL)
            list = node->child;
        else
            return NULL;
    }
    return node->value;
}

trie *trie_insert(trie *root, char *key, char *value)
{
    trie *node, *parent, *list;
    parent = NULL;
    list = root;
    for (; *key != '\0'; key++)
    {
        for (node = list; node != NULL; node = node->sibling)
            if (node->ch == *key)
                break;

        if (node == NULL)
        {
            node = trie_create();
            node->ch = *key;
            node->sibling = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
            list = NULL;
        }
        else
            list = node->child;
        parent = node;
    }
    if (node->value != NULL)
        free(node->value);
    node->value = strdup(value);
    return root;
}

trie *trie_delete(trie *root, char *key)
{
    int found;
    return trie_dfsdelete(root, NULL, key, &found);
}

trie *trie_dfsdelete(trie *root, trie *parent,
                     char *key, int *found)
{
    trie *node, *prev = NULL;
    *found = (*key == '\0' && root == NULL) ? 1 : 0;
    if (root == NULL || *key == '\0')
        return root;
    for (node = root; node != NULL; node = node->sibling)
    {
        if (node->ch == *key)
            break;
        prev = node;
    }
    if (node == NULL)
        return root;
    trie_dfsdelete(node->child, node, key + 1, found);
    if (*found > 0 && node->child == NULL)
    {
        if (prev != NULL)
            prev->sibling = node->sibling;
        else
        {
            if (parent != NULL)
                parent->child = node->sibling;
            else
                root = node->sibling;
        }
        free(node->value);
        free(node);
    }
    return root;
}

char *trie_min(trie *root)
{
    char *buf = calloc(256, sizeof(char));
    int i = 0;
    while (root)
    {
        trie *find = NULL;
        char min = INT8_MAX;
        for (trie *node = root; node && node->ch; node = node->sibling)
        {
            if (node->ch < min)
            {
                min = node->ch;
                find = node;
            }
        }
        root = find->child;
        buf[i++] = min;
        // if (root->endword)
        // {
        //     buf[i++] = root ? root->ch : 0;
        //     break;
        // }
    }
    return buf;
}

char *trie_max(trie *root)
{
    char *buf = calloc(256, sizeof(char));
    int i = 0;
    while (root)
    {
        trie *find = NULL;
        char max = INT8_MIN;
        for (trie *node = root; node && node->ch; node = node->sibling)
        {
            if (node->ch > max)
            {
                max = node->ch;
                find = node;
            }
        }
        root = find->child;
        buf[i++] = max;
        // if (root->endword)
        // {
        //     buf[i++] = root ? root->ch : 0;
        //     break;
        // }
    }
    return buf;
}

void spaceLevelInTrie(size_t level)
{
    size_t i = 0;
    while (i < level)
    {
        printf(" ");
        ++i;
    }
}

void print(trie *root, size_t level, bool *snew)
{
    if (!root)
        return;
    if (*snew)
    {
        spaceLevelInTrie(level);
        *snew = false;
    }
    printf("%c", root->ch);
    if (root && root->child)
    {
        print(root->child, level + 1, snew);
    }
    else
    {
        printf("\n");
        *snew = true;
    }
    if (root->sibling)
        print(root->sibling, level, snew);
}

void trie_print(trie *root)
{
    bool f = false;
    print(root, 0, &f);
}
