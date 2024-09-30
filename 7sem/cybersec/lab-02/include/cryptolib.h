#ifndef CRYPTOLIB_H
#define CRYPTOLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

void expmod_func(unsigned long long int base, unsigned long long int exponent, unsigned long long int module, unsigned long long int *result);
void euclid(unsigned long long int a, unsigned long long int b, unsigned long long int *res);
void diffyhellman(unsigned long long int *K1, unsigned long long int *K2);
void babygiant_steps(long long base, long long module, long long answer, unsigned long long int *x);

#endif
