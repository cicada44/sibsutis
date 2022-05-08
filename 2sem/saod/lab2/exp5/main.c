#include "bstlib.h"
#include "hashtablib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 200000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getRand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
    FILE* in = fopen("wls.txt", "r");
    char** str = (char**)malloc(sizeof(char*));
    int n = 0;
    while (!feof(in)) {
        str[n] = (char*)malloc(sizeof(char) * 256);
        fgets(str[n], 256, in);
        n++;
        str = (char**)realloc(str, sizeof(char*) * (n + 1));
    }
    fclose(in);

    FILE* inp = fopen("wl.txt", "r");
    char** str2 = (char**)malloc(sizeof(char*));
    n = 0;
    while (!feof(inp)) {
        str2[n] = (char*)malloc(sizeof(char) * 256);
        fgets(str2[n], 256, inp);
        n++;
        str2 = (char**)realloc(str2, sizeof(char*) * (n + 1));
    }
    fclose(inp);

    struct bstree* tree = bstreeCreate(str[0], 0);
    struct bstree* treeA = bstreeCreate(str2[0], 0);

    for (int i = 2; i < SIZE; i++) {
        bstreeAdd(tree, str[i - 1], i - 1);
    }
    for (int i = 2; i < SIZE; i++) {
        bstreeAdd(treeA, str2[i - 1], i - 1);
    }

    long double bstT = wtime();
    bstreeMax(tree);
    bstT = wtime() - bstT;

    long double bstA = wtime();
    bstreeMax(treeA);
    bstA = wtime() - bstA;

    printf("%d\t%.6Lf\t%.6Lf\n", SIZE, bstT, bstA);

    return 0;
}