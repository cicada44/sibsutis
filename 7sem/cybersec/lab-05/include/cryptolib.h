#ifndef CRYPTOLIB_H
#define CRYPTOLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

void expmod_func(unsigned long int base, unsigned long int exponent, unsigned long int module, unsigned long int *result);
void euclid(unsigned long int a, unsigned long int b, unsigned long int *res);
void diffyhellman(unsigned long int *K1, unsigned long int *K2);
void babygiant_steps(long long base, long long module, long long answer, unsigned long int *x);

#endif
