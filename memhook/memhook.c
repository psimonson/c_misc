#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include "debug.h"

int (*new_socket)(int, int, int);

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
