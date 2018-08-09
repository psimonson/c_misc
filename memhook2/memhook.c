#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include "debug.h"

int (*new_socket)(int, int, int);
void *(*new_malloc)(size_t);
void (*new_free)(void *);

int socket(int domain, int type, int protocol)
{
	debug_print("socket() call intercepted");
	new_socket = dlsym(RTLD_NEXT, "socket");
	if (!new_socket)
		return error_print("Cannot get next socket() call.");
#ifndef NDEBUG
	debug_print("inside of hook");
#endif
	return new_socket(domain, type, protocol);
}

void *malloc(size_t size)
{
	void *p;
	debug_print("malloc() call intercepted");
	new_malloc = dlsym(RTLD_NEXT, "malloc");
	if (!new_malloc) {
		error_print("Cannot get next malloc() call.");
		return NULL;
	}
#ifndef NDEBUG
	debug_print("inside malloc hook");
#endif
	p = new_malloc(size);
	if (!check_mem(p))
		return NULL;
#ifndef NDEBUG
	debug_print("malloc(%lu) at %p", size, p);
#endif
	return p;
}

void free(void *p)
{
#ifndef NDEBUG
	debug_print("free() call intercepted");
#endif
	if (!p) {
		error_print("Cannot free, block not allocated.");
		return;
	}
	new_free = dlsym(RTLD_NEXT, "free");
	if (!new_free) {
		error_print("Cannot find original free() function.");
		return;
	}
	new_free(p);
#ifndef NDEBUG
	debug_print("memory block (%p) freed.", p);
#endif
}
