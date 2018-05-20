#include "common/helper.h"

#define MAXBUF 256

static char __getch_buf[MAXBUF];	/* getch buffer max size 256 */
static int __getchp = 0;		/* getch buffer position */

int
getch()
{
	return (__getchp > 0) ? __getch_buf[--__getchp] : getchar();
}

void
ungetch(c)
int c;
{
	if (__getchp >= MAXBUF)
		printf("ungetch: too many characters\n");
	else
		__getch_buf[__getchp++] = c;
}
