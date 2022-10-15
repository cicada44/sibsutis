#include <stdio.h>
#include <sys/time.h>
#include "AVLTree.h"

#define SIZE 1000000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    char *dest_key = "null";

    // double t1 = wtime();

    struct avltree *avl = avltree_create(0, dest_key);

    for (int x = 1; x < SIZE; x++)
        avl = avltree_add(avl, x, dest_key);

    // double t2 = wtime() - t1;

    printf("%d\t%d\n", SIZE, avltree_height(avl));

    avltree_free(avl);

    return 0;
}