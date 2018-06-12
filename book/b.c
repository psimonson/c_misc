#define STACK_CUSTOM
#define MAXLEN 64

struct stack {
	int lineno;
	char key[MAXLEN];
};

static int push_stack(int, char*);
static int pop_stack(int*, char*);

#define push_stack PUSH_STACK
#define pop_stack POP_STACK
#include "stack.h"

main()
{
	char key[64];
	int lineno;
	int result;

	result = push_stack(1, "Hello world from b.c!");
	if (result) {
		printf("Error occured while pushing to stack.\n");
		return 1;
	}
	result = pop_stack(&lineno, key);
	if (result) {
		printf("Error occured while poping from stack.\n");
		return 1;
	}
	printf("%d: %s\n", lineno, key);
	return 0;
}

static int push_stack(int lineno, char *key)
{
	if (prs_stackp >= STACKSIZE)
		fprintf(stderr, "error: stack overflow\n");
	else {
		if (strlen(key) <= MAXLEN) {
			prs_stack[prs_stackp].lineno = lineno;
			strcpy(prs_stack[prs_stackp].key, key);
			prs_stackp++;
			return 0;
		} else
			fprintf(stderr, "error: key value too big\n");
	}
	return -1;
}

static int pop_stack(int *lineno, char *key)
{
	if (prs_stackp <= 0)
		fprintf(stderr, "error: stack empty\n");
	else {
		--prs_stackp;
		*lineno = prs_stack[prs_stackp].lineno;
		strcpy(key, prs_stack[prs_stackp].key);
		return 0;
	}
	return -1;
}
