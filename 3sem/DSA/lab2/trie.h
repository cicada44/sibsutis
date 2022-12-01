#ifndef __TRIE_H__
#define __TRIE_H__

// #include "AVLTree.h"
#include <stdbool.h>

#define N 26

typedef struct Trie Trie;

struct Trie
{
    char data;
    Trie *children[N];
    int is_leaf;
};

Trie *make_trienode(char data);
void free_trienode(Trie *node);
Trie *insert_trie(Trie *root, char *word);
int search_trie(Trie *root, char *word);
void print_trie(Trie *root);
void print_search(Trie *root, char *word);

#endif // __TRIE_H__