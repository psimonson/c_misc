#include <stdio.h>
#include "getch.h"

#define MAXBUF 100

char getchbuf[MAXBUF];
int getchp = 0;

int getch(void)
{
	return (getchp > 0) ? getchbuf[--getchp] : getchar();
}

void ungetch(int c)
{
	if (getchp >= MAXBUF)
		printf("ungetch: Too many characters\n");
	else
		getchbuf[getchp++] = c;
}
