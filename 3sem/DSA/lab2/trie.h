#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>

typedef struct trie
{
    char *value;
    char ch;
    struct trie *sibling; /* Sibling node */
    struct trie *child;   /* First child node */
} trie;

struct trie *trie_create();
char *trie_lookup(struct trie *root, char *key);
struct trie *trie_insert(struct trie *root, char *key, char *value);
struct trie *trie_delete(struct trie *root, char *key);
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key,
                             int *found);

#endif // __TRIE_H__