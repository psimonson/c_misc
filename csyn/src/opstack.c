#include "common/helper.h"

#define MAXSTACK 1024			/* max characters for stack */

static char __stackbuf[MAXSTACK];	/* stack buffer size=MAXSTACK */
static int __stackp = 0;		/* stack position */

void push(c)
	int c;
{
	if (__stackp >= MAXSTACK)
		printf("push: stack at max, no more room\n");
	else
		__stackbuf[__stackp++] = c;
}

int pop()
{
	if (__stackp <= 0)
		printf("pop: no characters on stack\n");
	else
		return __stackbuf[--__stackp];
	return 0;
}
