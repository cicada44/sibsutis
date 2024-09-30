#ifndef EXTRALIB_H
#define EXTRALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

void closefiles(int N, ...);
void prime_sqrt_mod(unsigned long long int p, unsigned long long *g);
double wtime();
int test_prime_num(unsigned long long int p);
void generate_prime_number(unsigned long long int min, unsigned long long int max, unsigned long long int *p);
void generate_primitive_root(unsigned long long int	p, unsigned long long *g);
int test_mutually_prime_number(unsigned long long int p, unsigned long long int e);
long int generate_mutually_prime_number(unsigned long long int e, unsigned long long int min, unsigned long long int max);
void cleanup();

#endif
