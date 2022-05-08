#include "hashtablib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 200003
#define SIZE 200000

struct listnode* hashtab[HASH_SIZE];

int hCol(struct listnode** hashtab)
{
    int col = 0;
    for (int i = 0; i < SIZE; i++) {
        if (hashtab[i] != NULL && hashtab[i]->next != NULL)
            col++;
    }
    return col;
}

/**/

int main()
{
    hashtabInit(hashtab);
    FILE* in = fopen("wls.txt", "r");
    char** str = (char**)malloc(sizeof(char*));
    int n = 0;
    for (int x = 0; x < SIZE; x++) {
        str[n] = (char*)malloc(sizeof(char) * 256);
        fgets(str[n], 256, in);
        n++;
        str = (char**)realloc(str, sizeof(char*) * (n + 1));
    }
    fclose(in);

    int q = 0;

    for (int i = 2; i < SIZE; i++) {
        hashtabAdd(hashtab, str[i - 1], i - 1);
        // printf("key[%d] = %s", KRHash(str[i]), str[i]);
    }

    q = hCol(hashtab);

    printf("%d\t%d\n", SIZE, q);

    return 0;
}