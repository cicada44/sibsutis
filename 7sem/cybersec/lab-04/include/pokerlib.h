#ifndef POKERLIB_H
#define POKERLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"
#include "../include/colorlib.h"

#define NUMBER_CARDS 52
#define MAXINT 512000

struct deck {
    char suit[10];
    char name[10];
    int start_card;
};

void print_card(char* name, char* suit);
void swap_card(unsigned long int *card_a, unsigned long int *card_b);
void mental_poker(int n_players);

#endif
