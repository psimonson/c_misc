#include <stdio.h>
#define MAXLEN 100

static char getchbuf[MAXLEN];	/* static char array to store characters */
static int getchp = 0;		/* static int to store buffer position */

int getch(void)
{
	return (getchp > 0) ? getchbuf[--getchp] : getchar();
}

void ungetch(int c)
{
	if (getchp >= MAXLEN)
		printf("ungetch: too many characters in buffer.\n");
	else
		getchbuf[getchp++] = c;
}
