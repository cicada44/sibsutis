#pragma once
#define SIZE_STR 200

int read_cnt();
char** read_dict(int cnt);
void print_dict(char** dict, int cnt);
int isOpnBracket(char* arr);
int isClsBracket(char* arr);
int cncatNameFunc(char* arr, int pos);
char* read_to_opnbr(char* arr);