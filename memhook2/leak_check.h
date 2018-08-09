#ifndef _LEAK_CHECK_H_
#define _LEAK_CHECK_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "d_list.h"
#include "debug.h"

struct DLIST_DATA2 {
	void *mem;
	size_t size;
};

struct DLIST *_leak_list;

static struct DLIST *leakcheck_init(void *p, size_t size)
{
    void *(*add_data_fn)(void *p, size_t size);
    void (*remove_data_fn)(void **list);
    void (*prepend_node_fn)(void **list, void *p, size_t size);
    void (*append_node_fn)(void **list, void *p, size_t size);
	_leak_list = dlist_create_list(add_data_fn,
        remove_data_fn, append_node_fn, prepend_node_fn);
	if (!check_mem(_leak_list)) {
		error_print("Cannot create leak list.");
		return NULL;
	}
	_leak_list->data = dlist_add_data(p, size);
	return _leak_list;
}

void *add_data_fn(void *p, size_t size)
{
    return NULL;
}

void remove_data_fn(void **dat)
{
}

void prepend_node_fn(void **list, void *p, size_t size)
{
}

void append_node_fn(void **list, void *p, size_t size)
{
}

#endif
