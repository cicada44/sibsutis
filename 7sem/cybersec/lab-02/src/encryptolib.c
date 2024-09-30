#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"

long int vernam_encode(char* input_file) {
    int fd_input, fd_output;
    char c = '\0';
    char key = 0;
    char* keystr = malloc(sizeof(char));
    char* keych = malloc(sizeof(char));
    char out[256] = {0};
    strcat(out, input_file);
    strcat(out, ".encode");
    long int k = 0;
    long int ki = 0;
    char cipherstr[8] = "vernam";
    srand(time(NULL));
    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }
    if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(1, fd_input);
        return -1;
    }

    while (read(fd_input, &c, sizeof(char)) != 0) {
        keych[ki] = (rand() % 256);
        keystr[ki] = c ^ keych[ki];
        ++ki;
        keych = realloc(keych, sizeof(char) * (ki + 1));
        keystr = realloc(keystr, sizeof(char) * (ki + 1));
    }

    write(fd_output, &key, sizeof(char));
    write(fd_output, cipherstr, 6 * sizeof(char));

    for (k = 0; k < ki; ++k) {
        write(fd_output, &keych[k], sizeof(char));
    }
    for (k = 0; k < ki; ++k) {
        write(fd_output, &keystr[k], sizeof(char));
    }

    closefiles(2, fd_input, fd_output);
    return k;
}

long int vernam_decode(char* input_file) {
    int fd_input, fd_output;
    char c = '\0';
    char out[256] = {0};
    strcat(out, input_file);
    strcat(out, ".decode");
    char* keystr = malloc(sizeof(char));
    char cipherstr[6] = "vernam";
    long int k = 0;
    long int keyi = 0;
    long int ki = 0;
    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }
    if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(1, fd_input);
        return -1;
    }

    if (read(fd_input, cipherstr, 7 * sizeof(char)) == 0) return 0;
    while (read(fd_input, &c, sizeof(char)) != 0) {
        keystr[ki] = c;
        ++ki;
        keystr = realloc(keystr, sizeof(char) * (ki + 1));
    }
    keyi = ki / 2;

    for (k = 0; k < keyi; ++k) {
        c = keystr[k] ^ keystr[k + keyi];
        write(fd_output, &c, sizeof(char));
    }
    closefiles(2, fd_input, fd_output);
    return k;
}

int rsa_generate() {
    unsigned long long int p, q, e;
    unsigned long long int eiler_res;
    unsigned long long int d = 0, n;
    int fd_public, fd_private;

    if ((fd_public =
             open("./.keyrsa.pub", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file .keyrsa.pub\n");
        return -1;
    }
    if ((fd_private = open("./.keyrsa", O_WRONLY | O_CREAT | O_TRUNC, 0600)) ==
        -1) {
        printf("[ERROR] Can't open file .keyrsa\n");
        closefiles(1, fd_public);
        return -1;
    }
    unsigned long long int gcd = 0;
    unsigned long long int euclid_res[3];
    while (gcd != 1 || test_prime_num(d) == 0 || d > 0xFFFF) {
        do {
            generate_prime_number(1, MAXINT, &p);
            generate_prime_number(1, MAXINT, &q);
        } while (p == q);
        n = p * q;
        eiler_res = (p - 1) * (q - 1);
        e = generate_mutually_prime_number(eiler_res, 1, eiler_res);
        euclid(e, eiler_res, euclid_res);
        d = euclid_res[0];
        gcd = euclid_res[2];
        d = d % eiler_res;
    }
    write(fd_public, &e, sizeof(e));
    write(fd_public, &n, sizeof(n));
    write(fd_private, &d, sizeof(d));
    write(fd_private, &n, sizeof(n));
    closefiles(2, fd_public, fd_private);
    return 0;
}

long int rsa_encode(char* input_file) {
    int fd_input, fd_output, fd_key;
    unsigned long int pubkey_e = 0, pubkey_n = 0;
    unsigned long long int c = '\0';
    long int* keystr = malloc(sizeof(long int));
    long int k = 0;
    long int ki = 0;
    char key = 0;
    char cipherstr[5] = "rsa";
    char out[256] = {0};
    strcat(out, input_file);
    strcat(out, ".encode");
    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }
    if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(1, fd_input);
        return -1;
    }
    if ((fd_key = open(".keyrsa.pub", O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(2, fd_input, fd_output);
        return -1;
    }
    read(fd_key, &pubkey_e, sizeof(unsigned long int));
    read(fd_key, &pubkey_n, sizeof(unsigned long int));

    while (read(fd_input, &c, sizeof(char)) != 0) {
        expmod_func(c, pubkey_e, pubkey_n, &c);
        keystr[ki] = c;
        ++ki;
        keystr = realloc(keystr, sizeof(long int) * (ki + 1));
        c = 0;
    }
    write(fd_output, &key, sizeof(char));
    write(fd_output, cipherstr, 3 * sizeof(char));

    for (k = 0; k < ki; ++k) {
        write(fd_output, &keystr[k], sizeof(long int));
    }

    closefiles(3, fd_input, fd_output, fd_key);
    return k;
}

long int rsa_decode(char* input_file) {
    int fd_input, fd_output, fd_key;
    unsigned long int privkey_d, privkey_n;
    unsigned long long int c = '\0';
    char* keystr = malloc(sizeof(char));
    long int k = 0;
    long int ki = 0;
    char cipherstr[5] = "rsa";
    char out[256] = {0};
    strcat(out, input_file);
    strcat(out, ".decode");
    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }
    if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(1, fd_input);
        return -1;
    }

    if ((fd_key = open(".keyrsa", O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(2, fd_input, fd_output);
        return -1;
    }
    read(fd_key, &privkey_d, sizeof(unsigned long int));
    read(fd_key, &privkey_n, sizeof(unsigned long int));

    if (read(fd_input, cipherstr, 4 * sizeof(char)) == 0) return 0;
    while (read(fd_input, &c, sizeof(long int)) != 0) {
        expmod_func(c, privkey_d, privkey_n, &c);
        keystr[ki] = c;
        ++ki;
        keystr = realloc(keystr, sizeof(char) * (ki + 1));
        c = 0;
        ++k;
    }

    for (k = 0; k < ki; ++k) {
        write(fd_output, &keystr[k], sizeof(char));
    }
    closefiles(3, fd_input, fd_output, fd_key);
    return k;
}

int shamir_cipher(char* input_file) {
    int is_it_ok = 0;
    char symb = '\0';
    long int ki = 0;
    char out[256] = {0};
    strcat(out, input_file);
    unsigned long long int p, c[2], d[2], x[2];
    int fd_input, fd_encoder, fd_decoder;
    unsigned long long int* keystr_input =
        malloc(sizeof(unsigned long long int));
    char* keystr_output = malloc(sizeof(char));

    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }

    shamir_generate(&p, c, d);

    while (read(fd_input, &symb, sizeof(char)) != 0) {
        expmod_func(symb, c[0], p, &x[0]);
        expmod_func(x[0], c[1], p, &x[1]);
        expmod_func(x[1], d[0], p, &x[0]);
        expmod_func(x[0], d[1], p, &x[1]);
        keystr_input[ki] = x[0];
        keystr_output[ki] = x[1];
        if (symb != keystr_output[ki]) {
            is_it_ok = -1;
        }
        ++ki;
        keystr_input =
            realloc(keystr_input, sizeof(unsigned long long int) * (ki + 1));
        keystr_output = realloc(keystr_output, sizeof(char) * (ki + 1));
        symb = 0;
    }

    if ((fd_encoder = open("./shamir.txt.encode", O_WRONLY | O_CREAT | O_TRUNC,
                           0666)) == -1) {
        printf("[ERROR] Can't open file shamir.txt.encode\n");
        return -1;
    }
    if ((fd_decoder = open("./shamir.txt.encode.decode",
                           O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
        printf("[ERROR] Can't open file shamir.txt.encode.decode\n");
        closefiles(1, fd_encoder);
        return -1;
    }

    for (int k = 0; k < ki; ++k) {
        write(fd_encoder, &keystr_input[k], sizeof(unsigned long long int));
        write(fd_decoder, &keystr_output[k], sizeof(char));
    }

    closefiles(3, fd_input, fd_encoder, fd_decoder);

    if (is_it_ok != 0) return -1;
    return 0;
}

void shamir_generate(unsigned long long int* p, unsigned long long int* c,
                     unsigned long long int* d) {
    unsigned long long int euclid_res[3];
    generate_prime_number(1, MAXINT, p);
    do {
        c[0] = generate_mutually_prime_number(*p - 1, 1, *p - 1);
        c[1] = generate_mutually_prime_number(*p - 1, 1, *p - 1);
        euclid(*p - 1, c[0], euclid_res);
        d[0] = euclid_res[1];
        euclid(*p - 1, c[1], euclid_res);
        d[1] = euclid_res[1];
    } while (d[0] > 0xFFFFFF || d[1] > 0xFFFFFF);
}

int elgamal_generate() {
    unsigned long long int p, g, x, y;
    int fd_public, fd_private;

    if ((fd_public = open("./.keyelgamal.pub", O_WRONLY | O_CREAT | O_TRUNC,
                          0666)) == -1) {
        printf("[ERROR] Can't open file .keyelgamal.pub\n");
        return -1;
    }
    if ((fd_private =
             open("./.keyelgamal", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
        printf("[ERROR] Can't open file .keyelgamal\n");
        closefiles(1, fd_public);
        return -1;
    }

    generate_prime_number(255, 800, &p);
    generate_prime_number(1, p - 1, &x);
    generate_primitive_root(p, &g);
    expmod_func(g, x, p, &y);

    write(fd_public, &y, sizeof(y));
    write(fd_public, &p, sizeof(p));
    write(fd_public, &g, sizeof(g));
    write(fd_private, &x, sizeof(x));
    write(fd_private, &p, sizeof(p));
    write(fd_private, &g, sizeof(g));
    // printf("GENERATED: X = %llu, Y = %llu, P = %llu, G = %llu\n", x, y, p ,
    // g);

    closefiles(2, fd_public, fd_private);
    return 0;
}

long int elgamal_encode(char* input_file) {
    int fd_input, fd_output, fd_key;
    char c = '\0';
    char key = 0;
    unsigned long long int* keystr_a = malloc(sizeof(unsigned long long int));
    unsigned long long int* keystr_b = malloc(sizeof(unsigned long long int));
    char out[256] = {0};
    strcat(out, input_file);
    strcat(out, ".encode");
    long int k = 0;
    long int ki = 0;
    unsigned long long int p, g, a = 1, b = 1;
    unsigned long long int pubkey = 0, sessionkey = 0;
    char cipherstr[9] = "elgamal";
    srand(time(NULL));
    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }
    if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(1, fd_input);
        return -1;
    }
    if ((fd_key = open(".keyelgamal.pub", O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(2, fd_input, fd_output);
        return -1;
    }
    read(fd_key, &pubkey, sizeof(unsigned long long int));
    read(fd_key, &p, sizeof(unsigned long long int));
    read(fd_key, &g, sizeof(unsigned long long int));
    // printf("ENCODED WITH: Y = %llu, P = %llu, G = %llu\n", pubkey, p , g);
    generate_prime_number(1, p - 1, &sessionkey);
    while (read(fd_input, &c, sizeof(char)) != 0) {
        expmod_func(g, sessionkey, p, &a);
        expmod_func(pubkey, sessionkey, p, &b);
        b = (b % p) * (c % p);
        keystr_a[ki] = a;
        keystr_b[ki] = b;
        ++ki;
        keystr_a = realloc(keystr_a, sizeof(unsigned long long int) * (ki + 1));
        keystr_b = realloc(keystr_b, sizeof(unsigned long long int) * (ki + 1));
        a = 0;
        b = 0;
        c = 0;
    }

    write(fd_output, &key, sizeof(char));
    write(fd_output, cipherstr, 7 * sizeof(char));

    for (k = 0; k < ki; ++k) {
        write(fd_output, &keystr_a[k], sizeof(unsigned long long int));
        write(fd_output, &keystr_b[k], sizeof(unsigned long long int));
    }
    closefiles(3, fd_input, fd_output, fd_key);

    return k;
}

long int elgamal_decode(char* input_file) {
    int fd_input, fd_output, fd_key;
    unsigned long long int privkey_x, privkey_p, privkey_g;
    unsigned long long int stream_a = '\0';
    unsigned long long int stream_b = '\0';
    unsigned long long int encode_message = 0;
    char* keystr = malloc(sizeof(char));
    long int k = 0;
    long int ki = 0;
    char cipherstr[7] = "elgamal";
    char out[256] = {0};
    strcat(out, input_file);
    strcat(out, ".decode");
    if ((fd_input = open(input_file, O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", input_file);
        return -1;
    }
    if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(1, fd_input);
        return -1;
    }

    if ((fd_key = open(".keyelgamal", O_RDONLY)) == -1) {
        printf("[ERROR] Can't open file %s\n", out);
        closefiles(2, fd_input, fd_output);
        return -1;
    }
    read(fd_key, &privkey_x, sizeof(unsigned long long int));
    read(fd_key, &privkey_p, sizeof(unsigned long long int));
    read(fd_key, &privkey_g, sizeof(unsigned long long int));

    if (read(fd_input, cipherstr, 8 * sizeof(char)) == 0) return 0;
    while (read(fd_input, &stream_a, sizeof(unsigned long long int)) != 0) {
        read(fd_input, &stream_b, sizeof(unsigned long long int));
        expmod_func(stream_a, privkey_p - 1 - privkey_x, privkey_p,
                    &encode_message);
        encode_message =
            ((encode_message % privkey_p) * (stream_b % privkey_p)) % privkey_p;
        keystr[ki] = encode_message;
        ++ki;
        keystr = realloc(keystr, sizeof(char) * (ki + 1));
        ++k;
    }

    for (k = 0; k < ki; ++k) {
        write(fd_output, &keystr[k], sizeof(char));
    }
    closefiles(3, fd_input, fd_output, fd_key);

    return k;
}
