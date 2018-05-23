#include "common/helper.h"
#include "stack.h"

#define STATE_QUOTE   0
#define STATE_COMMENT 1
#define STATE_CODE    2

#define MAXLINE       1024

int state = STATE_CODE;
char text[MAXLINE];
int lines;

/* search:  search for characters; changing state */
int search(c)
	int c;
{
	extern int getch();
	extern void ungetch(int);
	extern void push(int, char*);
	static int i = 0;

	text[i++] = c;
	switch (c) {
		case '/':
			c = getch();
			if (c == '*')
				state = STATE_COMMENT;
			else
				ungetch(c);
			break;
		case '*':
			c = getch();
			if (c == '/')
				state = STATE_CODE;
			else
				ungetch(c);
			break;
		case '"':
		case '\'':
			state = STATE_QUOTE;
			break;
		case EOF:
			state = EOF;
			break;
		case '\n':
			++lines;
			text[i] = '\0';
			push(lines, text);
			i = 0;
			state = STATE_CODE;
			break;
		default:
			state = STATE_CODE;
			break;
	}

	return state;
}
