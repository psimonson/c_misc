#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

int main()
{
	int *mem = NULL;

	mem = malloc(10);
	if (!mem)
		return error_print("Error allocating memory.");
	free(mem);
	return 0;
}
