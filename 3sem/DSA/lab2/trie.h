#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>

typedef struct trie {
  char *value;
  char ch;
  struct trie *next;
  struct trie *child;
} trie;

trie *trie_create();
char *trie_lookup(trie *root, char *key);
trie *trie_insert(trie *root, char *key, char *value);
trie *trie_delete(trie *root, char *key);
trie *trie_delete_dfs(trie *root, trie *parent, char *key, int *found);
void print(trie *root);
// void display(struct trie *root, char *str, int level);

#endif // __TRIE_H__