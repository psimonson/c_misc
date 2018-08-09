#include <stdio.h>
#include <malloc.h>
#include "debug.h"

int main()
{
	int *p;

#ifndef NDEBUG
	debug_print("Calling from main...");
#endif
	p = (int*)malloc(sizeof(int));
#ifndef NDEBUG
	debug_print("Freeing memory...");
#endif
	free(p);
	return 0;
}
