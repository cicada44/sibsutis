#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "../include/cryptolib.h"
#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"

int main(int argc, char *argv[]) {
    if (vernam_encode("./vernam.txt") == vernam_decode("./vernam.txt.encode"))
        printf("VER E/D result:\t[SUCCESS]\n");
    else
        printf("VER E/D result:\t[FAILED]\n");

    if (!shamir_cipher("./shamir.txt"))
        printf("SHA E/D result:\t[SUCCESS]\n");
    else
        printf("SHA E/D result:\t[FAILED]\n");

    elgamal_generate();
    if (elgamal_encode("./elgamal.txt") ==
        elgamal_decode("./elgamal.txt.encode"))
        printf("ELG E/D result:\t[SUCCESS]\n");
    else
        printf("ELG E/D result:\t[FAILED]\n");

    // rsa_generate();
    if (rsa_encode("./rsa.txt") == rsa_decode("./rsa.txt.encode"))
        printf("RSA E/D result:\t[SUCCESS]\n");
    else
        printf("RSA E/D result:\t[FAILED]\n");

    cleanup();

    return EXIT_SUCCESS;
}
