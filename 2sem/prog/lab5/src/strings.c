#include "strings.h"
#include <stdio.h>

int strcmp(char* s1, char* s2)
{
    unsigned char c1, c2;

    while (1) {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 != c2)
            return c1 < c2 ? -1 : 1;
        if (!c1 || !c2)
            break;
    }
    return 0;
}

int strlen(char* s)
{
    int n = 0;
    while (*(s + n) != '\0') {
        ++n;
    }
    return n;
}

int strspn(char* s, char c)
{
    int cnt = 0;
    while (*(s + cnt) != '\0') {
        if (*(s + cnt) == c)
            return cnt;
        cnt++;
    }
    return 0;
}

char* strcpy(char* dest, char* src)
{
    char* tmp = dest;

    while ((*dest++ = *src++) != '\0')
        /* nothing */;
    return tmp;
}

char* strffut(char* s, char* c)
{
    char* s1;
    for (s1 = s; *s1 != '\0'; ++s1)
        if (*s1 == *c)
            return (char*)s1;
    return 0;
}

char* strtok(char** s, char* del)
{
    char* firsttok = *s;
    char* endtok;
    if (firsttok == NULL)
        return NULL;
    endtok = strffut(firsttok, del);
    if (endtok)
        *endtok++ = '\0';
    *s = endtok;
    return firsttok;
}

char* strcncat(char* str, char* strtobecpy, int cnt)
{
    char* tmp = str;

    if (cnt) {
        while (*str)
            str++;
        while ((*str++ = *strtobecpy++) != 0) {
            if (--cnt == 0) {
                *str = '\0';
                break;
            }
        }
    }
    return tmp;
}

void remove_spaces(char* s)
{
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}