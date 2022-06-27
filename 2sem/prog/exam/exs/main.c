#include "listr.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *s = "SEREGASEREEEEEEEEGAAAAAAAAAAAAAA";
	char *f = calloc(60, sizeof(char));
	camel_to_snake(s, f);
	printf("s - %s\n", f);
	return 0;
}