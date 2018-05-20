#include "common/helper.h"

#define STRING    0
#define OPERATOR  1
#define NUMBER    2

#define PERIOD '.'
#define COMMA  ','
#define EQUALS '='

int getop(s)
	char *s;
{
	extern int getch();
	extern void ungetch(int);
	extern void push(int);
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t');
	*(s+1) = '\0';
	if (!isalnum(c) && (c == PERIOD || c == COMMA || c == EQUALS)) {
		*++s = c;
		return OPERATOR;
	}
	if (!isalnum(c))
		return c;
	if (isdigit(c)) {
		while (isdigit(c = getch()))
			*++s = c;
		*++s = '\0';
		if (!isdigit(c))
			ungetch(c);
		return NUMBER;
	}
	if (isalpha(c))
		while (isalpha(c = getch()))
			*++s = c;
	if (c != EOF)
		ungetch(c);
	*++s = '\0';
	return STRING;
}
