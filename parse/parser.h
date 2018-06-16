#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS, FUNCARGS };

static void dcl(void);
static void parseerror(void);
static int findqualifier(char *s);
static int gettoken(void);

int iserror;			/* is parse error newline */
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* indentifier name */
char datatype[MAXTOKEN];		/* data type = char, int, etc. */
char qtype[MAXTOKEN];		/* type of qualifier */
char out[1000];			/* output string */

/* qualifiers are defined here; for comparison */
static char *qualifiers[] = {
	"extern", "static", "auto", "register", "const", "volatile",
	"signed", "unsigned", "short", "long"
};

/* dirdcl:  parse a direct declaration */
static void dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
			parseerror();
			return;
		}
	} else if (tokentype == NAME) /* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		parseerror();
		return;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS
		|| type == FUNCARGS)
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == FUNCARGS) {
			strcat(out, "function ");
			strcat(out, token);
			strcat(out, " returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* dcl:  parse a declaration */
static void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; ) /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

static int getch(void);
static void ungetch(int);

/* parseerror:  handle newline character */
static void parseerror(void)
{
	int c;

	if (tokentype != '\n')
		while ((c = getch()) != '\n');
	tokentype = '\n';
	iserror = 1;
}

/* findqualifier:  1 if s matches a qualifier; 0 otherwise */
static int findqualifier(char *s)
{
	int i, len = sizeof(qualifiers)/sizeof(qualifiers[0]);

	for (i = 0; i < len; i++)
		if (!strcmp(qualifiers[i], s))
			return 1;
	return 0;
}

/* gettoken:  return next token */
static int gettoken(void)
{
	char *p = token;
	int c;

	while ((c = getch()) == ' ' || c == '\t');
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			if (c == '*') {
				ungetch(c);
				return tokentype = '(';
			} else {
				*p++ = '(';
				for (*p++ = c; (*p++ = getch()) != ')'; );
				*p = '\0';
				return tokentype = FUNCARGS;
			}
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; );
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

#define BUFMAX	100
char getchbuf[BUFMAX];	/* maximum getch buffer definition */
int getchbufp = 0;	/* pointer to getchbuf */

/* getch:  get character from keyboard; otherwise get from buffer */
static int getch(void)
{
	return (getchbufp > 0) ? getchbuf[--getchbufp] : getchar();
}

/* ungetch:  store character in buffer */
static void ungetch(int c)
{
	if (getchbufp >= BUFMAX)
		printf("ungetch: too many characters.\n");
	else
		getchbuf[getchbufp++] = c;
}
