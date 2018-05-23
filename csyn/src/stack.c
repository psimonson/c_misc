#include "common/helper.h"
#include "stack.h"

static struct stack stack[MAXSTACK];
static int stackp = 0;

void push(line, text)
	int line;
	char *text;
{
	if (stackp >= MAXSTACK)
		printf("stack: full already.\n");
	else {
		stack[stackp].lineno = line;
		stack[stackp].text = str_dup(text);
		stackp++;
	}
}

struct stack pop()
{
	struct stack rstack;

	rstack.lineno = -1;
	rstack.text = NULL;

	if (stackp <= 0)
		printf("stack: empty.\n");
	else {
		--stackp;
		rstack.lineno = stack[stackp].lineno;
		rstack.text = stack[stackp].text;
		return rstack;
	}
	return rstack;
}
