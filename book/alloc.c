#include <stdio.h>
#include <string.h>

main()
{
	extern char *alloc(int);
	extern void afree(char*);
	char *text;

	text = alloc(10);
	if (!text)
		return 1;
	strcpy(text, "Hello");
	puts(text);
	afree(text);
	return 0;
}

#define ALLOCSIZE 100

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf+ALLOCSIZE-allocp >= n) {	/* it fits */
		allocp += n;
		return allocp-n; /* old p */
	} else	/* not enough room */
		return 0;
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf+ALLOCSIZE)
		allocp = p;
}
