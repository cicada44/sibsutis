#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"

void closefiles(int N, ...)
{
  int* p = &N;
  int i = 1;
  p++;
  for (i = 1; i <= N; ++i) {
    if (*p == -1) continue;
    close(*p);
    p++;
  }
}

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int test_prime_num(unsigned long long int p)
{
	unsigned long long int i = 1;

	for (i = 2; i < sqrt(p); ++i)
		if (p % i == 0) return 0;
	return 1;
}

void generate_prime_number(unsigned long long int min, unsigned long long int max, unsigned long long int *p)
{
	*p = 1;
	do {
		*p = (rand()) % (max - min ) + min;
	} while (!test_prime_num(*p));
}

void generate_primitive_root(unsigned long long int	p, unsigned long long *g)
{
	unsigned long long int q = (p - 1) / 2;
	unsigned long long int res = 1;
	for (int i = 2; i < (p - 1); ++i) {
		expmod_func(i, q, p, &res);
		if (res != 1) {
			*g = i;
			return;
		}
	}
}

int test_mutually_prime_num(unsigned long long int p, unsigned long long int e)
{
  unsigned long long int euclid_res[3];
  if (p == e) return 0;
  if (p % e == 0) return 0;
  euclid(p, e, euclid_res);
  if (euclid_res[2] != 1) return 0;
  return 1;
}

long int generate_mutually_prime_number(unsigned long long int e, unsigned long long int min, unsigned long long int max)
{
    long int p = 1;
    do {
        p = (rand()) % (max - min) + min;
    } while (!test_mutually_prime_num(e, p));
    return p;
}

void cleanup()
{
  printf("\nCleaning current directory from extra files...\n");
  char* name[4] = {"vernam.", "shamir.", "elgamal.", "rsa."};
  char* type[2] = {"txt.", "jpg."};
  char* state[2] = {"encode", "encode.decode"};
  char file[255];
  char file_buff_type[255];
  char file_buff_state[255];

  for (int i = 0; i < 4; ++i) {
    strcat(file, name[i]);

    for (int j = 0; j < 2; ++j) {
      strcpy(file_buff_type, file);
      strcat(file, type[j]);

      for (int k = 0; k < 2; k++) {
        strcpy(file_buff_state, file);

        strcat(file, state[k]);
        remove(file);
        strcpy(file, file_buff_state);
      }
      strcpy(file, file_buff_type);
    }
    *file = 0;
  }
}
