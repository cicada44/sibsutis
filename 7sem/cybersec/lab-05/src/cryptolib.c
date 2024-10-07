#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"

struct listnode *hashtab[HASHTAB_SIZE];

void expmod_func(unsigned long int base, unsigned long int exponent, unsigned long int module, unsigned long int *result)
{
	*result = 1;
	while (exponent) {
		if (exponent & 0x1) {
			*result = (*result * base) % module;
		}
		base = (base * base) % module;
		exponent = exponent >> 1;
	}
	*result = *result % module;
}

void euclid(unsigned long int a, unsigned long int b, unsigned long int *res)
{
	long int U[2] = {1, 0};
	long int V[2] = {0, 1};
	long int T[2];
	long int buff;

	while (b > 0) {
		double q = a / b;
		T[0] = U[0] - q * U[1];
		T[1] = V[0] - q * V[1];

		U[0] = U[1];
		V[0] = V[1];

		U[1] = T[0];
		V[1] = T[1];

		buff = a % b;
		a = b;
		b = buff;
	}

	res[0] = U[0];
	res[1] = V[0];
	res[2] = a;
}

void diffyhellman(unsigned long int *K1, unsigned long int *K2)
{
	srand(time(NULL));
	unsigned long int p;
	unsigned long int q;
	unsigned long int g;

	generate_prime_number(1, 1000, &q);
	p = 2 * q + 1;

	while (test_prime_num(p)) {
		generate_prime_number(1, 1000, &q);
		p = 2 * q - 1;
	}
	generate_primitive_root(p, &g);

	unsigned long int a, b;
	unsigned long int KeyA = 0, KeyB = 0;

	a = rand() % (1000000 - 10000) + 10000;
	expmod_func(g, a, p, &KeyA);
	b = rand() % (1000000 - 10000) + 10000;
	expmod_func(g, b, p, &KeyB);

	expmod_func(KeyB, a, p, &*K1);
	expmod_func(KeyA, b, p, &*K2);
}

void babygiant_steps(long long base, long long module, long long answer, unsigned long int *x)
{
	hashtab_init(hashtab);
	struct listnode *node;
	int m = sqrt(module) + 2;
	int k = sqrt(module) + 1;

	unsigned long int *row_y = (unsigned long int*)malloc(m + 1);
	unsigned long int *row_a = (unsigned long int*)malloc(k + 1);

	double time;
	time = wtime();

	for(int i = 0; i < m; i++) {
		expmod_func(base, i, module, &row_y[i]);
		row_y[i] = (row_y[i] * (answer % module)) % module;
		hashtab_add(hashtab, row_y[i], i);
	}

	for(int j = 1; j < k + 1; j++) {
		expmod_func(base, j * m, module, &row_a[j]);
		node = hashtab_lookup(hashtab, row_a[j]);
		if(node != NULL) {
				*x = j * m - node->value;
				time = wtime() - time;
				//printf("Elapsed Time for BGS:\t%.7f sec\n", time);
				return;
		}
	}
}
