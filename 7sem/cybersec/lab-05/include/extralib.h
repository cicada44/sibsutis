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
void prime_sqrt_mod(unsigned long int p, unsigned long long *g);
double wtime();
int test_prime_num(unsigned long int p);
void generate_prime_number(unsigned long int min, unsigned long int max, unsigned long int *p);
void generate_primitive_root(unsigned long int	p, unsigned long int *g);
int test_mutually_prime_number(unsigned long int p, unsigned long int e);
long int generate_mutually_prime_number(unsigned long int e, unsigned long int min, unsigned long int max);
void cleanup();

#endif
