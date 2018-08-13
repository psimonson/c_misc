#ifndef _LEAK_CHECK_H_
#define _LEAK_CHECK_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "debug.h"
#include "d_list.h"

struct DLIST_DATA2 {
	void *mem;
	size_t size;
};

struct DLIST *_leak_list;

static void *add_data_fn(void *p, size_t size)
{
    struct DLIST_DATA2 *data;
    if (!p || size < 0)
        return NULL;
    data = (struct DLIST_DATA2 *)malloc(sizeof(struct DLIST_DATA2));
    if (!data)
        return NULL;
    data->mem = p;
    data->size = size;
    return data;
}

static void remove_data_fn(void **dat)
{
    struct DLIST_DATA2 *data = *((struct DLIST_DATA2 **)dat);
    if (data->mem)
        free(data->mem);
    free(*dat);
    *dat = NULL;
}

static void prepend_node_fn(void **list, void *p, size_t size)
{
	struct DLIST *node, *tmp;
	node = (struct DLIST *)malloc(sizeof(struct DLIST));
	if (!node)
		return;
	if (!(*list)) {
		node->count = 1;
		node->data = dlist_add_data(p, size);
		node->next = NULL;
		(*list) = node;
	} else {
		((struct DLIST *)*list)->count++;
		tmp = (*list);
		node->count = ((struct DLIST *)*list)->count;
		node->data = dlist_add_data(p, size);
		node->next = tmp;
		(*list) = node;
	}
}

static void append_node_fn(void **list, void *p, size_t size)
{
	struct DLIST *node;
	node = (struct DLIST *)malloc(sizeof(struct DLIST));
	if (!node)
		return;
	if (!(*list)) {
		node->count = 1;
		node->data = dlist_add_data(p, size);
		node->next = NULL;
		(*list) = node;
	} else {
		dlist_iterator_init(*list);
		while (dlist_iterator_next() != NULL);
		((struct DLIST *)*list)->count++;
		node->count = ((struct DLIST *)*list)->count;
		node->data = dlist_add_data(p, size);
		node->next = NULL;
		dlist_iterator_last()->next = node;
	}
}

static struct DLIST *leakcheck_init()
{
	_leak_list = dlist_init(add_data_fn,
        remove_data_fn, prepend_node_fn, append_node_fn);
	return _leak_list;
}

#endif
