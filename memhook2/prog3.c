#include <stdio.h>
#include <malloc.h>
#include "leak_check.h"

int main()
{
	struct DLIST *tmp;
	int *t1, *t2, *t3;
	t1 = malloc(sizeof(int));
	t2 = malloc(sizeof(int));
	t3 = malloc(sizeof(int));
	leakcheck_init(t1, sizeof(int));
	dlist_append_node(&_leak_list, t2, sizeof(int));
	dlist_append_node(&_leak_list, t3, sizeof(int));
	dlist_iterator_init(_leak_list);
	while ((tmp = dlist_iterator_next()) != NULL) {
		debug_print("Address %p has %d bytes allocated.",
			((struct DLIST_DATA2 *)tmp->data)->mem,
			((struct DLIST_DATA2 *)tmp->data)->size);
	}
	dlist_destroy(&_leak_list);
	return 0;
}
