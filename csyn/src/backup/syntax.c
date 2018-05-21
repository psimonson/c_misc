#include "common/helper.h"

#define STATE_QUOTE   0
#define STATE_COMMENT 1
#define STATE_CODE    2

#define MAXSTACK      256

static int state = STATE_CODE;
static int stack[MAXSTACK];
static int stackp = 0;

/* search:  search for characters; changing state */
int search(c)
	int c;
{
	extern int getch();
	extern void ungetch(int);

	switch (c) {
		case '/':
			c = getch();
			if (c == '*')
				return STATE_COMMENT;
			else
				ungetch(c);
			break;
		case '*':
			c = getch();
			if (c == '/')
				return STATE_CODE;
			else
				ungetch(c);
			break;
		case '"':
		case '\'':
			return STATE_QUOTE;
			break;
		default:
			return STATE_CODE;
	}

	return -1;
}

/* getch(), ungetch():  used for search function */

#define MAXBUFLEN 100

static char getchbuf[MAXBUFLEN];
static int getchbufp = 0;

int getch()
{
	return (getchbufp > 0) ? getchbuf[--getchbufp] : getchar();
}

void ungetch(c)
	int c;
{
	if (getchbufp >= MAXBUFLEN)
		printf("ungetch: too many characters\n");
	else
		getchbuf[getchbufp++] = c;
}
