#include "strings.h"
#include <stdio.h>
#define MAX_STRING_SIZE 260

char symbols[] = "/\\:*?«<>|";
void delinput(char d)
{
    scanf("%c", &d);
}

void input(char s[MAX_STRING_SIZE])
{
    fgets(s, MAX_STRING_SIZE, stdin);
}

int allinput(
        char username[MAX_STRING_SIZE],
        char dir[MAX_STRING_SIZE],
        char paths[MAX_STRING_SIZE])
{
    // printf("del: ");
    // delinput(del);
    printf("user name: ");
    input(username);
    printf("dir: ");
    input(dir);
    printf("paths: ");
    input(paths);
    int unLen = strlen(username);
    int dirLen = strlen(dir);
    int pathsLen = strlen(paths);
    if (unLen == 1)
        printf("Problems with user name lenght\n");
    if (dirLen == 1)
        printf("Problems with dir lenght\n");
    if (pathsLen == 1)
        printf("Problems with paths lenght\n");
    if (unLen + dirLen + pathsLen > 3)
        return 0;
    return 1;
}

int correctUnCheck(char* s)
{
    int f;
    for (int x = 0; x < 10; x++) {
        f = strspn(s, symbols[x]);
        if (f > 0) {
            return f;
        }
    }
    return 0;
}

int correctDirCheck(char* s)
{
    int f;
    for (int x = 1; x < 10; x++) {
        f = strspn(s, symbols[x]);
        if (f > 0) {
            return f;
        }
    }
    return 0;
}

int correctPathsCheck(char* s)
{
    int f;
    for (int x = 1; x < 10; x++) {
        f = strspn(s, symbols[x]);
        if (f > 0) {
            return f;
        }
    }
    return 0;
}

/*
Check correct symbols in inputed data
0 - success
1 - something wrong
*/
int correctcheck(char* un, char* dir, char* paths)
{
    int f1 = 0, f2 = 0, f3 = 0; // len - 9
    f1 = correctUnCheck(un);
    f2 = correctDirCheck(dir);
    f3 = correctPathsCheck(paths);
    if (f1 > 0)
        printf("Problems with symbol N %d in username\n", ++f1);
    if (f2 > 0)
        printf("Problems with symbol N %d in dir\n", ++f2);
    if (f3 > 0)
        printf("Problems with symbol N %d in paths\n", ++f3);
    if (f1 + f2 + f3 > 0)
        return 1;
    return 0;
}

void process(char s[MAX_STRING_SIZE], char dir[MAX_STRING_SIZE], char d)
{
    char* tok;
    int y;
    char out[MAX_STRING_SIZE];
    char proctok[MAX_STRING_SIZE];
    char finalout[MAX_STRING_SIZE];
    char ndir[MAX_STRING_SIZE];
    for (int x = 0; x < sizeof(out); x++)
        ndir[x] = NULL;
    for (int x = 0; x < sizeof(out); x++)
        finalout[x] = NULL;
    strcncat(ndir, dir, strlen(dir) - 1);
    while (s != NULL) {
        y = 0;
        for (int x = 0; x < sizeof(out); x++)
            out[x] = NULL;
        strcpy(out, ndir);
        tok = strtok(&s, &d);
        remove_spaces(tok);
        if (*tok == '~' && *(tok + 1) == '/') {
            while (*(tok + 1 + y) != '\0') {
                proctok[y] = *(tok + 1 + y);
                y++;
            }
            for (int i = 0; i < MAX_STRING_SIZE; i++)
                proctok[y] = NULL;
            strcncat(out, proctok, strlen(proctok));
            strcncat(finalout, out, strlen(out));
        } else {
            strcncat(finalout, tok, strlen(tok));
        }
        if (s != NULL) {
            finalout[strlen(finalout)] = d;
        }
    }
    print(finalout);
}

void print(char* s)
{
    printf("new paths: %s\n", s);
}