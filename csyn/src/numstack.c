#include "common/helper.h"

#define MAXSTACK 256			/* max integers for stack */

static int __numstack[MAXSTACK];	/* stack definition using MAXSTACK */
static int __numstackp = 0;		/* stack position definition */

void pushnum(int n)
{
	if (__numstackp >= MAXSTACK)
		printf("stack_num: too full\n");
	else
		__numstack[__numstackp++] = n;
}

int popnum()
{
	if (__numstackp <= 0)
		printf("stack_num: empty\n");
	else
		return __numstack[--__numstackp];
	return -1;
}

int num_empty()
{
	if (__numstackp == 0)
		return 1;
	return 0;
}
