#include "../include/votelib.h"
#include "../include/colorlib.h"
#include "../include/cryptolib.h"
#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"
#include "../include/md5.h"

struct bulletin BULLETIN;
struct data DATA;

void vote_startup() {
    unsigned long int Phi, euclid_res[3];
    do {
        generate_prime_number(1, MAXINT, &DATA.P);
        generate_prime_number(1, MAXINT, &DATA.Q);
    } while (DATA.P == DATA.Q);
    DATA.N = DATA.P * DATA.Q;
    Phi = (DATA.P - 1) * (DATA.Q - 1);

    do {
        generate_prime_number(1, Phi, &DATA.c);
        euclid(abs(DATA.c), abs(Phi), euclid_res);
        DATA.d = euclid_res[0];
    } while (DATA.d > 0xFFFFFF);

    printf("%s[DEBUG]%s\tGenerated next values:\n", BLUE, RESET);
    printf("P = %lu\tQ = %lu\tN = %lu\nC = %lu\tD = %lu\n", DATA.P, DATA.Q, DATA.N, DATA.c, DATA.d);
}

int oneside_encryption() {
    uint8_t res[16];
    uint8_t arr[1];
    unsigned long int hash = 0;
    md5(arr, 1, res);
    for (int i = 0; i < 16; ++i) hash += res[i];
    return hash;
}

unsigned long int DATA_signing(unsigned long int n1) {
    unsigned long int s1;
    expmod_func(n1, DATA.c, DATA.N, &s1);
    return s1;
}

int initialization_transaction(int vote) {
    unsigned long int pseudo_note, pseudo_sign, encrypted_note, r, r_rev;
    unsigned long int euclid_res[3];

    do {
        generate_prime_number(2, DATA.N - 1, &BULLETIN.note);
        r = generate_mutually_prime_number(DATA.N, 1, DATA.N - 1);
        euclid(r, DATA.N, euclid_res);
        r_rev = euclid_res[0];
    } while (r_rev > 0xFFFFFF);

    expmod_func(r, DATA.d, DATA.N, &encrypted_note);
    pseudo_note = (BULLETIN.note * encrypted_note) % DATA.N;
    BULLETIN.sign = DATA_signing(oneside_encryption(pseudo_note));

    expmod_func(BULLETIN.sign, DATA.d, DATA.N, &pseudo_sign);

    if (oneside_encryption(pseudo_note) == pseudo_sign) {
        return 0;
    } else {
        printf("%s[DATA]%s Wrong note sign!\n", RED, RESET);
        return 1;
    }
}
