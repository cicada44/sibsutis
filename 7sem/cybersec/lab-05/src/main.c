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
#include "../include/extralib.h"
// #include "../include/votelib.h"

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    vote_startup();

    int vote = 0;
    while (vote != -1) {
        printf("%s[I]%s Vote:\n", YELLOW, RESET);
        scanf("%d", &vote);
        printf("%s[BANK]%s Starting transaction...\n", YELLOW, RESET);
        if (!initialization_transaction(vote))
            printf("%s[I]%s Vote done successfully!\n", GREEN, RESET);
        else
            printf("%s[I]%s Vote rejected!\n", RED, RESET);
    }
}
