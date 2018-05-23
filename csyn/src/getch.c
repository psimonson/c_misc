#include "common/helper.h"

#define MAXBUFLEN 100

static char getchbuf[MAXBUFLEN];
static int getchbufp = 0;

int getch()
{
	return (getchbufp > 0) ? getchbuf[--getchbufp] : getchar();
}

void ungetch(c)
	int c;
{
	if (getchbufp >= MAXBUFLEN)
		printf("ungetch: too many characters\n");
	else
		getchbuf[getchbufp++] = c;
}
