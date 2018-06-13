#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

main() /* convert declaration to words */
{
	while (gettoken() != EOF) {
		strcpy(datatype, token); /* 1st token is data type */
		out[0] = '\0';
		dcl();	/* parse rest of line */
		if (tokentype == '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

/* dirdcl:  parse a direct declaration */
void dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME) /* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* dcl:  parse a declaration */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; ) /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* gettoken:  return next token */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t');
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; );
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		return tokentype = NAME;
	} else
		return tokentype = c;
}

#define BUFMAX	100
char getchbuf[BUFMAX];	/* maximum getch buffer definition */
int getchbufp = 0;	/* pointer to getchbuf */

/* getch:  get character from keyboard; otherwise get from buffer */
int getch(void)
{
	return (getchbufp > 0) ? getchbuf[--getchbufp] : getchar();
}

/* ungetch:  store character in buffer */
void ungetch(int c)
{
	if (getchbufp >= BUFMAX)
		printf("ungetch: too many characters.\n");
	else
		getchbuf[getchbufp++] = c;
}
