#include "common/helper.h"

#define MAXLEN 64

int getop(char *);

int main(void)
{
	char s[MAXLEN];
	int type;

	while ((type = getop(s)) != EOF)
		switch (type) {
		case 1:
			(void)trim(s);
			printf("String entered: %s\n", s);
			break;
		default:
			break;
		}
	return 0;
}

int getch(void);
void ungetch(int);

int getop(char *s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t');
	*(s+1) = '\0';
	if (!isalnum(c) && c != '.')
		return c;
	if (isalnum(c))
		while (isalnum(*++s = c = getch()));
	if (c == '.')
		while (isalnum(*++s = c = getch()));
	*++s = '\0';
	if (c != EOF)
		ungetch(c);
	return 1;
}

#define MAXBUF 64

char buf[MAXBUF];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c)
{
	if (bufp >= MAXBUF)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
