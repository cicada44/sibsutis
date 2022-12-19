#include <stdio.h>
#include "trie.h"

int main()
{
    trie *t = trie_create();

    t = trie_insert(t, "data", "3");
    t = trie_insert(t, "datum", "5");
    t = trie_insert(t, "barnaul", "6");
    t = trie_insert(t, "barny", "5");

    char *r1 = trie_lookup(t, "data");
    char *r2 = trie_lookup(t, "datum");
    char *r3 = trie_lookup(t, "barnaul");
    char *r4 = trie_lookup(t, "barny");

    printf("r1 - %s\n", r1);
    printf("r2 - %s\n", r2);
    printf("r3 - %s\n", r3);
    printf("r4 - %s\n", r4);
    // printf("r1 - %s\n", r1);

    print(t);

    return 0;
}
