#include <stdio.h>
#include "trie.h"

int main()
{
    trie *t = trie_create();

    t = trie_insert(t, "data", "datum");

    char *r1 = trie_lookup(t, "data");

    printf("r1 - %s\n", r1);

    return 0;
}
