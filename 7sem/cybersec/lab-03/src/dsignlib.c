#include "../include/extralib.h"
#include "../include/md5.h"

int hashMD5(FILE* input_file, MD5_CTX* md5handler) {
    int bytes;
    unsigned char data[1024];

    if (input_file == NULL) {
        return 1;
    }

    MD5Init(md5handler);
    while ((bytes = fread(data, 1, 1024, input_file)) != 0)
        MD5Update(md5handler, data, bytes);
    MD5Final(md5handler);
    return 0;
}

int RSA_sign(char* input_file) {
    long long int p, q, n, eiler_res, d, c, s[16];
    FILE* in_file = fopen(input_file, "rb");
    char* fd_input = strcat(input_file, ".pkey");
    FILE* fd_public = fopen(input_file, "wb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".rsa_sgn");
    FILE* sgn_file = fopen(input_file, "wb");

    p = generate_prime_number(RSA_RAND_LIM);
    q = generate_prime_number(RSA_RAND_LIM);
    n = p * q;
    eiler_res = (p - 1) * (q - 1);
    generation_c_d(&c, &d, eiler_res);
    fwrite(&d, 8, 1, fd_public);
    fwrite(&n, 8, 1, fd_public);

    MD5_CTX md5handler;
    if (hashMD5(in_file, &md5handler)) {
        return 1;
    }

    for (int i = 0; i < 16; i++) {
        s[i] = expmod_func((long long int)md5handler.digest[i], c, n);
        fwrite(&s[i], 8, 1, sgn_file);
    }

    fclose(sgn_file);
    fclose(in_file);
    fclose(fd_public);
    return 0;
}

int RSA_sign_check(char* input_file) {
    FILE* in_file = fopen(input_file, "rb");
    char* fd_input = strcat(input_file, ".pkey");
    FILE* fd_public = fopen(input_file, "rb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".rsa_sgn");
    FILE* sgn_file = fopen(input_file, "rb");

    long long int n, d, s[16];

    MD5_CTX md5handler;
    if (hashMD5(in_file, &md5handler)) {
        return 1;
    }

    fread(&d, 8, 1, fd_public);
    fread(&n, 8, 1, fd_public);
    // printf("d: %ld, n: %ld\n", d, n);

    int flg = 0;
    for (int i = 0; i < 16; i++) {
        fread(&s[i], 8, 1, sgn_file);
        //   printf("s[%d] %ld ", i, s[i]);
        if (md5handler.digest[i] != expmod_func(s[i], d, n)) {
            flg = 1;
            break;
        }
    }

    fclose(sgn_file);
    fclose(in_file);
    fclose(fd_public);

    if (flg) {
        return 1;
    }

    return 0;
}

int ELG_sign(char* input_file) {
    FILE* in_file = fopen(input_file, "rb");

    char* fd_input = strcat(input_file, ".pelg");
    FILE* fd_public = fopen(input_file, "wb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".selg");
    FILE* s_keys_file = fopen(input_file, "wb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".sgn_elg");
    FILE* out_file = fopen(input_file, "wb");
    long long int secret_a, g, p;
    long long int free_a;

    free_a = DH(&secret_a, &g, &p);
    fwrite(&secret_a, 8, 1, s_keys_file);
    fwrite(&free_a, 8, 1, fd_public);
    fwrite(&g, 8, 1, fd_public);
    fwrite(&p, 8, 1, fd_public);

    long long int k, k_inv, r, h, s, u;

    MD5_CTX md5handler;
    if (hashMD5(in_file, &md5handler)) {
        return 1;
    }

    for (int i = 0; i < 16; i++) {
        generation_c_d(&k, &k_inv, p - 1);
        h = (long long int)md5handler.digest[i];
        if ((long long int)h >= p) {
            return -1;
        }
        r = expmod_func(g, k, p);
        u = (h - secret_a * r) % (p - 1);
        u += u < 0 ? p - 1 : 0;
        s = (k_inv * u) % (p - 1);
        fwrite(&r, 8, 1, out_file);
        fwrite(&s, 8, 1, out_file);
    }

    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(fd_public);
    return 0;
}

int ELG_sign_check(char* input_file) {
    FILE* in_file = fopen(input_file, "rb");

    char* fd_input = strcat(input_file, ".pelg");
    FILE* fd_public = fopen(input_file, "rb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".sgn_elg");
    FILE* out_file = fopen(input_file, "rb");
    long long int g, p;
    long long int free_a;

    fread(&free_a, 8, 1, fd_public);
    fread(&g, 8, 1, fd_public);
    fread(&p, 8, 1, fd_public);

    long long int r, h, s;

    MD5_CTX md5handler;
    if (hashMD5(in_file, &md5handler)) {
        return 1;
    }

    long long int left, right;
    int flg = 0;
    for (int i = 0; i < 16; i++) {
        h = (long long int)md5handler.digest[i];
        if ((long long int)h >= p) {
            return -1;
        }
        fread(&r, 8, 1, out_file);
        fread(&s, 8, 1, out_file);
        left = (expmod_func(free_a, r, p) * expmod_func(r, s, p)) % p;
        right = expmod_func(g, h, p);
        if (left != right) {
            flg = 1;
            break;
        }
    }

    fclose(out_file);
    fclose(in_file);
    fclose(fd_public);

    if (flg) return 1;
    return 0;
}

int GOST_sign(char* input_file) {
    long long int q, b, y;
    long long int p;
    long long int a, s, r, k, h, x;

    FILE* in_file = fopen(input_file, "rb");
    char* fd_input = strcat(input_file, ".pgst");
    FILE* fd_public = fopen(input_file, "wb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".sgst");
    FILE* s_keys_file = fopen(input_file, "wb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".sgn_gst");
    FILE* out_file = fopen(input_file, "wb");

    do {
        q = generate_prime_number(5000);
        b = random() % 10000;
        p = b * q + 1;
    } while (!test_prime_num(p));

    do {
        a = random() % p;
        a = expmod_func(a, q, p);
    } while (a != 1);
    x = random() % q;
    y = expmod_func(a, x, p);

    fwrite(&p, sizeof(long long int), 1, fd_public);
    fwrite(&q, sizeof(long long int), 1, fd_public);
    fwrite(&a, sizeof(long long int), 1, fd_public);
    fwrite(&y, sizeof(long long int), 1, fd_public);
    fwrite(&x, sizeof(long long int), 1, s_keys_file);

    MD5_CTX md5handler;
    if (hashMD5(in_file, &md5handler)) {
        return 1;
    }

    for (int i = 0; i < 16; i++) {
        h = (long long int)md5handler.digest[i];
        while (1) {
            k = random() % q;
            r = expmod_func(a, k, p) % q;
            if (r == 0) {
                continue;
            }
            s = (k * h + x * r) % q;
            if (s > 0) {
                break;
            }
        }
        fwrite(&r, 8, 1, out_file);
        fwrite(&s, 8, 1, out_file);
    }

    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(fd_public);
    return 0;
}

int GOST_sign_check(char* input_file) {
    FILE* in_file = fopen(input_file, "rb");

    char* fd_input = strcat(input_file, ".pgst");
    FILE* fd_public = fopen(input_file, "rb");
    fd_input[strlen(input_file) - 5] = '\0';

    fd_input = strcat(input_file, ".sgn_gst");
    FILE* out_file = fopen(input_file, "rb");
    long long int q, p, a, y;

    fread(&p, sizeof(long long int), 1, fd_public);
    fread(&q, sizeof(long long int), 1, fd_public);
    fread(&a, sizeof(long long int), 1, fd_public);
    fread(&y, sizeof(long long int), 1, fd_public);

    long long int r, h, h_inv, s, gcd_x, u1, u2, v;

    MD5_CTX md5handler;
    if (hashMD5(in_file, &md5handler)) {
        return 1;
    }

    int flg = 0;
    for (int i = 0; i < 16; i++) {
        h = (long long int)md5handler.digest[i];
        fread(&r, 8, 1, out_file);
        fread(&s, 8, 1, out_file);
        if (r >= q || s >= q) {
            flg = 1;
            break;
        }
        gcd(h, q, &gcd_x, NULL);
        h_inv = gcd_x < 0 ? q + gcd_x : gcd_x;
        u1 = (s * h_inv) % q;
        u2 = (-r * h_inv) % q;
        u2 += u2 < 0 ? q : 0;
        v = ((expmod_func(a, u1, p) * expmod_func(y, u2, p)) % p) % q;
        if (v != r) {
            flg = 1;
            break;
        }
    }

    fclose(out_file);
    fclose(in_file);
    fclose(fd_public);

    if (flg) return 1;
    return 0;
}
