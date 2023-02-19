#include <stdio.h>
#include "trie.h"

void print_minmax(trie *t)
{
    printf("______________________\n");
    printf("max - %s\n", trie_max(t));
    printf("min - %s\n______________________\n\n", trie_min(t));
}

int main()
{
    trie *t = trie_create();

    t = trie_insert(t, "data", "3");
    t = trie_insert(t, "test", "5");
    t = trie_insert(t, "tree", "5");
    t = trie_insert(t, "dsa", "6");
    t = trie_insert(t, "dog", "5");
    t = trie_insert(t, "dark", "5");
    t = trie_insert(t, "red", "5");
    t = trie_insert(t, "riddle", "5");
    t = trie_insert(t, "rest", "5");
    t = trie_insert(t, "green", "5");
    t = trie_insert(t, "blue", "5");
    t = trie_insert(t, "less", "5");

    print_minmax(t);

    printf("-----TRIE-----\n");
    trie_print(t);

    // trie_delete(t, "data");

    return 0;
}
