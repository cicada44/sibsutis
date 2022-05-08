#include "bstlib.h"
#include "hashtablib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 200000

unsigned int KRHash(char* s)
{
    unsigned int h = 0, hash_mul = 31;
    while (*s)
        h = h * hash_mul + (unsigned int)*s++;
    return h % SIZE;
}

struct listnode* hashtab[SIZE];

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
    FILE* in = fopen("dict.txt", "r");
    char** str = (char**)malloc(sizeof(char*));
    int n = 0;
    while (!feof(in)) {
        str[n] = (char*)malloc(sizeof(char) * 256);
        fgets(str[n], 256, in);
        n++;
        str = (char**)realloc(str, sizeof(char*) * (n + 1));
    }
    fclose(in);

    struct bstree* tree = bstreeCreate(str[0], 0);
    hashtabInit(hashtab);

    for (int i = 2; i < SIZE; i++) {
        bstreeAdd(tree, str[i - 1], i - 1);
    }
    for (int i = 2; i < SIZE; i++) {
        hashtabAdd(hashtab, str[i - 1], i - 1);
    }

    long double bstT = wtime();
    bstreeLookup(tree, str[getRand(0, SIZE - 1)]);
    bstT = wtime() - bstT;

    long double htT = wtime();
    hashtabLookup(hashtab, str[getRand(0, SIZE - 1)]);
    htT = wtime() - htT;

    printf("%d\t%.6Lf\t%.6Lf\n", SIZE, bstT, htT);

    return 0;
}