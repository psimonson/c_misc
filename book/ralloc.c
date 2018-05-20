#include <stdio.h>

int strlength(const char*);
void strcopy(char*, char*);

char *alloc(int n);
void afree(char*);

int main()
{
	char *buf;

	buf = alloc(10);
	if (buf == 0)
		return 1;

	strcopy(buf, "Hello!");
	puts(buf);
	printf("Length: %d\n", strlength(buf));
	afree(buf);
	return 0;
}

int strlength(const char *s)
{
	const char *p = s;

	while (*p != '\0')
		p++;
	return p-s;
}

void strcopy(char* s, char* t)
{
	while ((*s++ = *t++) != '\0');
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];	/* alloc buffer */
static char *allocp = allocbuf;		/* pointer to next free space */

char* alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else		/* not enough room */
		return 0;
}

void afree(char* p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
