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
    int cnt = 0;
    for (int c = 0; *(arr + c) != '\n'; c++) {
        if (*(arr + c) == '(') {
            cnt++;
        }
    }
    return cnt;
}

int isClsBracket(char* arr)
{
    int cnt = 0;
    for (int c = 0; *(arr + c) != '\n'; c++) {
        if (*(arr + c) == ')') {
            cnt++;
        }
    }
    return cnt;
}

int is_eq_sym(char* arr)
{
    int cnt = 0;
    for (int c = 0; *(arr + c) != '\n'; c++) {
        if (*(arr + c) == '=') {
            cnt++;
        }
    }
    return cnt;
}

char* read_to_opnbr(char* arr, unsigned int* p)
{
    int x = 0;
    char* buf = malloc(SIZE_STR * sizeof(char));
    for (int x = 0; x < SIZE_STR; x++)
        buf[x] = 0;
    while (arr[x] != '(') {
        buf[x] = arr[x];
        (*p)++;
        x++;
    }
    return buf;
}

int is_on_begin_str(const char* str1, const char* str2)
{
    for (int x = 0; x < strlen(str2); x++) {
        if (str1[x] != str2[x])
            return 1;
    }
    return 0;
}

char* highlight_name_func(char* s)
{
    char* buf = malloc(SIZE_STR * sizeof(char));
    for (int x = 0; x < SIZE_STR; x++)
        buf[x] = 0;
    int pos_end = strlen(s);
    int x = 0, p = pos_end;
    while (s[p] != ' ') {
        p--;
    }
    ++p;
    int y = 0;
    for (int x = p; x < pos_end; x++) {
        buf[y] = s[x];
        y++;
    }
    return buf;
}

int is_value_in_arr(int* arr, int val, int size)
{
    for (int x = 0; x < size; x++) {
        if (val == arr[x])
            return 1;
    }
    return 0;
}

int is_value_in_char_arr(char** arr, char* name, int size)
{
    for (int x = 0; x < size; x++) {
        if (strcmp(arr[x], name) == 0)
            return 1;
    }
    return 0;
}

char* read_name_func(char* s)
{
    if (isOpnBracket(s) == 1 && isClsBracket(s) == 1 && is_eq_sym(s) == 0) {
        unsigned int pos = 0;
        char* tmp = read_to_opnbr(s, &pos);
        char* buf = highlight_name_func(tmp);
        return buf;
    }
    return NULL;
}

size_t meets_count(const char* str, const char* wrd)
{
    return (str = strstr(str, wrd)) ? 1 + meets_count(str + 1, wrd) : 0;
}

int* merge(int a[], int m, int b[], int n)
{
    int* sorted = malloc((m + n) * sizeof(int));
    int i, j, k;

    j = k = 0;

    for (i = 0; i < m + n;) {
        if (j < m && k < n) {
            if (a[j] < b[k]) {
                sorted[i] = a[j];
                j++;
            } else {
                sorted[i] = b[k];
                k++;
            }
            i++;
        } else if (j == m) {
            for (; i < m + n;) {
                sorted[i] = b[k];
                k++;
                i++;
            }
        } else {
            for (; i < m + n;) {
                sorted[i] = a[j];
                j++;
                i++;
            }
        }
    }
    return sorted;
}

int* add_cnt(
        char** dict,
        char** dict_functions_call,
        int* ignore_dict,
        int cnt_dict,
        int size_ignore_dict)
{
    int* calls_dict = (int*)calloc(size_ignore_dict, sizeof(int));
    for (int x = 0; x < cnt_dict; x++) {
        int flag;
        int c = 0;
        while (1) {
            flag = is_value_in_arr(ignore_dict, x, size_ignore_dict);
            if (flag == 1)
                x++;
            else if (flag == 0)
                break;
        }
        for (int i = 0; i < size_ignore_dict; i++) {
            int count = meets_count(dict[x], dict_functions_call[i]);
            calls_dict[i] += count;
        }
    }
    return calls_dict;
}