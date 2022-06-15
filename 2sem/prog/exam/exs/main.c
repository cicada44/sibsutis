#include "listr.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *s = "str2";
	char *s2 = "str";
	char *str_o = calloc(12, sizeof(char));
	int cmp = strcmp_r(s, s2);
	printf("cmp - %d\n", cmp);
	return 0;
}