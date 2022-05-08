#include "bstlib.h"
#include "hashtablib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 200000

int main()
{
    struct bstree* ctree = bstreeCreate("a", 23);
    bstreeAdd(ctree, "g", 23);
    bstreeAdd(ctree, "b", 22);
    bstreeAdd(ctree, "c", 21);
    bstreeAdd(ctree, "d", 19);
    bstreeAdd(ctree, "e", 18);
    bstreeAdd(ctree, "k", 17);
    bstreeAdd(ctree, "f", 16);
    bstreeAdd(ctree, "h", 15);
    bstreeAdd(ctree, "i", 14);
    bstreeAdd(ctree, "j", 13);
    bstreeAdd(ctree, "l", 12);
    struct bstree* mtree = max(ctree);
    struct bstree* ftree = bstreeLookup(ctree, "i");
    printf("Found KEY - %s\n\tvalue - %d", ftree->key, ftree->value);
    deleteTree(ctree);
    return 0;
}