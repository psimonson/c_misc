#include <stdio.h>
#include <ctype.h>

#define MAXLEN 100
#define NUMBER 0

/* getop:  collects numbers and symbols in buf; returning NUMBER or symbol */
int getop(char *s)
{
	extern int getch(void);
	extern void ungetch(int);
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t');
	*(s+1) = '\0';
	if (!isdigit && c != '.')
		return c;
	if (isdigit(c))
		while (isdigit(*++s = c = getch()));
	if (c == '.')
		while (isdigit(*++s = c = getch()));
	if (c != EOF)
		ungetch(c);
	*++s = '\0';
	return NUMBER;
}
