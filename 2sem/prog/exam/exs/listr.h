#pragma once
#include <stdio.h>
#include <inttypes.h>

#define err printf("err\n")

uint64_t cnt_sym(char *s, char sym);
int correct_suff(char *s, char *syms, unsigned int pre);
char *str_insert(char *str_s, char *str_p, unsigned int pos, char *str_o);
int correct_IP_check(char *s);
char *delete_str(char *s, char *s_del, char *buf);
int str_to_uint(char *s);
char *uint_to_str(int t, char *buf);
char *strcncat(char *s1, char *s2, char *buf);
char *findstr(char *s1, char *s2);
char *str_cp(char *s1, char *buf);
char *snake_to_camel(char *s1, char *buf);
char *camel_to_snake(char *s1, char *buf);
void str_tok(char *s, char del, char **arr);
int str_locate_locket_sym(char *src, char *symb, unsigned int c);
char *str_str(char *src, char *find_s);