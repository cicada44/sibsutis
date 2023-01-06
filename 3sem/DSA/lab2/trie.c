#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <string.h>

trie *trie_create()
{
    trie *node;
    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->ch = '\0';
    node->value = NULL;
    node->next = NULL;
    node->child = NULL;
    return node;
}

char *trie_lookup(trie *root, char *key)
{
    trie *node = NULL, *list = NULL;
    for (list = root; *key != '\0'; key++)
    {
        for (node = list; node != NULL; node = node->next)
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
        for (node = list; node != NULL; node = node->next) // getchild
            if (node->ch == *key)
                break;
        if (node == NULL) // setchild
        {
            node = trie_create();
            node->ch = *key;
            node->next = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
        }
        else
        {
            list = node->child;
        }
        parent = node;
    }
    node->value = strdup(value);
    return root;
}

trie *trie_delete(trie *root, char *key)
{
    int found;
    return trie_delete_dfs(root, NULL, key, &found);
}

trie *trie_delete_dfs(trie *root, trie *parent,
                      char *key, int *found)
{
    trie *node, *prev = NULL;
    *found = (*key == '\0' && root == NULL) ? 1 : 0;
    if (root == NULL || *key == '\0')
        return root;
    for (node = root; node != NULL; node = node->next)
    {
        if (node->ch == *key)
            break;
        prev = node;
    }
    if (node == NULL)
        return root;
    trie_delete_dfs(node->child, node, key + 1, found);
    if (*found > 0 && node->child == NULL)
    {
        if (prev != NULL)
            prev->next = node->next;
        else
        {
            if (parent != NULL)
                parent->child = node->next;
            else
                root = node->next;
        }
        free(node->value);
        free(node);
    }
    return root;
}
