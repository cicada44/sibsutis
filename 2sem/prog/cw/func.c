#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_dict(char** dict, int cnt)
{
    for (int x = 0; x < cnt; x++)
        printf("%d - %s\n", x, dict[x]);
}

int read_cnt()
{
    int cnt = 0;
    FILE* fp;
    fp = fopen("test.c", "r");
    while (!feof(fp)) {
        fscanf(fp, "%*[^\n]%*c");
        cnt++;
    }
    fclose(fp);
    return cnt;
}

char** read_dict(int cnt)
{
    int i;
    FILE* fp;
    fp = fopen("test.c", "r");

    char** dict = (char**)malloc(cnt * sizeof(char*));
    for (i = 0; i < cnt; i++) {
        dict[i] = (char*)malloc(SIZE_STR * sizeof(char));
    }
    i = 0;
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) {
        fgets(dict[i], SIZE_STR, fp);
        i++;
    }

    fclose(fp);
    return dict;
}

int isOpnBracket(char* arr)
{
    for (int c = 0; *(arr + c) != '\n'; c++) {
        if (*(arr + c) == '(') {
            return c;
        }
    }
    return -1;
}

int isClsBracket(char* arr)
{
    for (int x = 0; *(arr + x) != '\n'; x++) {
        if (*(arr + x) == ')') {
            return x;
        }
    }
    return -1;
}

int cncatNameFunc(char* arr, int pos)
{
    for (int x = pos; x < strlen(arr); x--) {
        if (*(arr + x - 1) == ' ')
            return x;
    }
    return -1;
}

char* read_to_opnbr(char* arr)
{
    int x = 0;
    char* buf = malloc(SIZE_STR * sizeof(char));
    while (*(arr + x) != '(') {
        *(buf + x) = *(arr + x);
        x++;
    }
    return buf;
}