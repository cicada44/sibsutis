#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "md5.h"

#define bool char
#define true 1
#define false 0

#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)<(y)?(x):(y)

#define RSA_RAND_LIM 20000

long long int expmod_func(long long int x, long long int ex, long long int p);
long long int gcd(long long int a, long long int b, long long int *x, long long int *y);
bool test_prime_num(long long int x);
long long int simple_rand();
long long int generate_prime_number(long long int lim);
long long int genrandom();
long long int DH(long long int *a, long long int *g, long long int *p);
long long int generation_c_d(long long int *c, long long int *d, long long int p);

int hashMD5 (FILE* fd_input, MD5_CTX *md5handler);
int RSA_sign(char *fd_input);
int RSA_sign_check(char *fd_input);
int ELG_sign(char* fd_input);
int ELG_sign_check(char* fd_input);
int GOST_sign(char* fd_input);
int GOST_sign_check(char* fd_input);

#endif
