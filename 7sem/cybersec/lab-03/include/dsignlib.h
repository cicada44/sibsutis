#ifndef DSIGNLIB_H
#define DSIGNLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "extralib.h"
#include "md5.h"

int hashMD5(FILE* input_file, MD5_CTX *md5handler);
int RSA_sign(char *input_file);
int RSA_sign_check(char *input_file);
int sgn_elgamal_create(char* input_file);
int sgn_elgamal_check(char* input_file);
int sgn_gost_create(char* input_file);
int sgn_gost_check(char* input_file);

#endif
