#ifndef _PRS_DEBUG_H_
#define _PRS_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

void debug_print(const char *format, ...)
{
	char msg[512];
	va_list ap;
	va_start(ap, format);
	strcpy(msg, "[DEBUG]: ");
	strcat(msg, format);
	strcat(msg, "\n");
	vfprintf(stderr, msg, ap);
	va_end(ap);
}

int error_print(const char *format, ...)
{
	char msg[512];
	va_list ap;
	va_start(ap, format);
	strcpy(msg, "[DEBUG]: ");
	strcat(msg, format);
	strcat(msg, "\n");
	vfprintf(stderr, msg, ap);
	va_end(ap);
	assert(errno);
}

void check_mem(void *mem)
{
	assert(mem);
#ifndef NDEBUG
	debug_print("memory block (%p) okay.", mem);
#endif
}

void free_mem(void *mem)
{
	assert(mem);
	free(mem);
#ifndef NDEBUG
	debug_print("memory block (%p) freed.", mem);
#endif
}

#endif
