#include <stdio.h>
#include "debug.h"
#include "d_list.h"

int main() {
  struct DLIST *list1, *list2, *tmp;
  list1 = dlist_init(NULL, NULL, NULL, NULL);
  dlist_append_node(&list1, 1, "Philip");
  dlist_append_node(&list1, 2, "Mark");
  dlist_append_node(&list1, 3, "Mary");
  list2 = dlist_init(NULL, NULL, NULL, NULL);
  dlist_append_node(&list2, 4, "Bob");
  dlist_append_node(&list2, 5, "Rob");
  dlist_append_node(&list2, 6, "Tom");
  dlist_iterator_init(list2);
  while ((tmp = dlist_iterator_next()) != NULL) {
    dlist_append_node(&list1,
      ((struct DLIST_DATA*)tmp->data)->value,
      ((struct DLIST_DATA*)tmp->data)->message);
  }
  dlist_destroy(&list2);
  dlist_iterator_init(list1);
  while ((tmp = dlist_iterator_next()) != NULL) {
    printf("Value: %d\nName: %s\n",
      ((struct DLIST_DATA*)tmp->data)->value,
      ((struct DLIST_DATA*)tmp->data)->message);
  }
  dlist_destroy(&list1);
  return 0;
}
