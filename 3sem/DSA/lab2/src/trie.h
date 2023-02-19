#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>
#include <stdbool.h>

typedef struct trie
{
  char *value;
  char ch;
  struct trie *sibling;
  struct trie *child;
} trie;

trie *trie_create();
char *trie_lookup(trie *root, char *key);
trie *trie_insert(trie *root, char *key, char *value);
trie *trie_delete(trie *root, char *key);
trie *trie_dfsdelete(trie *root, trie *parent, char *key, int *found);
char *trie_min(trie *root);
char *trie_max(trie *root);
void spaceLevelInTrie(size_t level);
void print(trie *root, size_t level, bool *snew);
void trie_print(trie *root);

#endif // __TRIE_H__