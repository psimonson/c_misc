#include <stdio.h>
#include <ctype.h>
#include "getch.h"

#define MAXTOKEN 100

#define RVALUE 0
#define LVALUE 1

int gettoken(void);
int tokentype;
char token[MAXTOKEN];

int main(void)
{
	while (gettoken() != EOF)
		switch (tokentype) {
			case LVALUE:
				printf("LVALUE: %s\n", token);
			break;
			case RVALUE:
				printf("RVALUE: %s\n", token);
			break;
			default:
			break;
		}
	return 0;
}

int gettoken(void)
{
	char *p = token;
	int c;

	while ((c = getch()) == ' ' || c == '\t');
	if (c == '=') {
		while ((c = getch()) == ' ' || c == '\t');
		ungetch(c);
		while ((*p = getch()) != '\n')
			p++;
		*p = '\0';
		return tokentype = RVALUE;
	} else if (isalnum(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = LVALUE;
	} else
		return tokentype = c;
}
