#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <dlfcn.h>
#include "debug.h"

/* lcheck() is for memory leak checking */
void lcheck(void);

void *malloc(size_t size)
{
	void *(*my_malloc)(size_t);
	my_malloc = dlsym(RTLD_NEXT, "malloc");
	check_mem(my_malloc);
	void *p = my_malloc(size);
	debug_print("malloc(%lu) = %p", size, p);
	lcheck();
	return p;
}

void lcheck(void)
{
	debug_print("Display memory leaks...");
}
