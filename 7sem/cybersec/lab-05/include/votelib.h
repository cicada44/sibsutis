#pragma once

#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

enum vote_types { YES, NO, ABSTAIN };

struct data {
    unsigned long int P;
    unsigned long int Q;
    unsigned long int N;
    unsigned long int c;
    unsigned long int d;
} DATA;

struct bulletin {
    unsigned long int note;
    unsigned long int sign;
};

void vote_startup();
int oneside_encryption();
int initialization_transaction(int vote);
