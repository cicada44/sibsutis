#include "../include/extralib.h"

long long int expmod_func(long long int x, long long int ex, long long int p)
{
   long long int result = 1;
   for (long long int na = abs(ex); na > 0; na >>= 1) {
       if (na % 2 == 1) {
           result = (result * x) % p;
       }
       x = (x * x) % p;
   }
   return result % p;
}

long long int gcd(long long int a, long long int b, long long int *x, long long int *y)
{
    long long int U_array[] = {MAX(a, b), 1, 0};
    long long int V_array[] = {MIN(a, b), 0, 1};
    long long int T_array[3];
    long long int q, *swop_p, *U, *V, *T;

    q = MAX(a, b);
    if (q != a) {
        swop_p = x;
        x = y;
        y = swop_p;
    }

    U = U_array;
    V = V_array;
    T = T_array;
    while (V[0] != 0) {
        q = U[0] / V[0];
        T[0] = U[0] % V[0];
        T[1] = U[1] - q * V[1];
        T[2] = U[2] - q * V[2];
        swop_p = U;
        U = V;
        V = T;
        T = swop_p;
    }
    if (x != NULL) {
        *x = U[1];
    }
    if (y != NULL) {
        *y = U[2];
    }
    return U[0];
}

bool test_prime_num(long long int x)
{
    long long int a;

    if (!(x % 2)) {
        return false;
    }
    for(int i = 0; i < 100; i++){
        a = (rand() % (x - 2)) + 2;
        if (gcd(a, x, NULL, NULL) != 1)
            return false;
        if ( expmod_func(a, x - 1, x) != 1)
            return false;
    }
    return true;
}

long long int simple_rand()
{
    long long int rand_v;

    srand(clock());
    while (1){
        rand_v = rand() + 1;
        if (test_prime_num(rand_v)) {
            return rand_v;
        }
    }
    return -1;
}

long long int generate_prime_number(long long int lim)
{
    long long int rand_v;

    srand(clock());
    while (1){
        rand_v = rand() % lim + 1;
        if (test_prime_num(rand_v)) {
            return rand_v;
        }
    }
    return -1;
}

long long int genrandom()
{
    srand(clock());
    return rand() + 1;
}

long long int DH(long long int *a, long long int *g, long long int *p)
{
    long long int q = 0;
    while (!q) {
        *p = simple_rand();
        if (test_prime_num((*p - 1) / 2)) {
            q = (*p - 1) / 2;
        }
    }
    *g = 0;
    while (!*g) {
        *g = genrandom();
        if (*g >= *p - 1 || expmod_func(*g, q, *p) == 1) {
           *g = 0;
        }
    }
    do {
        *a = simple_rand();
    } while (*a >= *p - 1);

    if (*a == -1 || *g == -1 || *p == -1) return -1;
    long long int A  = expmod_func(*g, *a, *p);
    return A;
}

long long int generation_c_d(long long int *c, long long int *d, long long int p)
{
    long long int x, y;
    long long int big_c, big_d, big_p;

    do {
        *c = genrandom();
    } while (gcd(*c, p, &x, &y) != 1);

    big_c = *c;
    big_p = p;

 //   *d = y < 0 ? p + y : y;
    *d = x < 0 ? p + x : x;
    big_d = *d;

    return (big_c * big_d) % big_p;
}
