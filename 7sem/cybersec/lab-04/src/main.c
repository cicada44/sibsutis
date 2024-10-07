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

#include "../include/colorlib.h"
#include "../include/pokerlib.h"

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s[ERROR]%s Not enough arguments!\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    mental_poker(atoi(argv[1]));
}
