#pragma once
#define SIZE_STR 200
#include <stddef.h>

int read_cnt();
char** read_dict(int cnt);
void print_dict(char** dict, int cnt);
int isOpnBracket(char* arr);
int isClsBracket(char* arr);
int cncatNameFunc(char* arr, int pos);
char* read_to_opnbr(char* arr, unsigned int* p);
int is_on_begin_str(const char* str1, const char* str2);
char* read_name_func(char* s);
int is_eq_sym(char* arr);
int is_value_in_arr(int* arr, int val, int size);
int is_value_in_char_arr(char** arr, char* name, int size);
size_t meets_count(const char* str, const char* wrd);
int* merge(int a[], int m, int b[], int n);
int* add_cnt(
        char** dict,
        char** dict_functions_call,
        int* ignore_dict,
        int cnt_dict,
        int size_ignore_dict);