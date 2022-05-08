#include "func.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_SIZE 260

int main()
{
    int correctLenghtData, correctSymFlag;
    char username[MAX_STRING_SIZE];
    char dir[MAX_STRING_SIZE];
    char paths[MAX_STRING_SIZE];
    char* pathsc = (char*)paths;
    char d;

    printf("del: ");
    do {
        scanf("%c", &d);
    } while (getchar() != '\n');
    correctLenghtData = allinput(username, dir, paths);
    if (correctLenghtData)
        exit(-1);
    correctSymFlag = correctcheck(username, dir, paths);
    if (correctSymFlag)
        exit(-1);
    process(pathsc, dir, d);

    return 0;
}