/************************************************************************
 * stack.h - Stack Header Library
 *
 * info: Simple stack header library, useful for creating simple stacks.
 * Can also be used to create a custom stack of your own. Very simple
 * implementation was used in designing this header.
 *
 * Created by Philip '5n4k3' Simonson.                  (2018)
 ************************************************************************
 */

#ifndef PRS_STACK_H
#define PRS_STACK_H

#include <stdio.h>
#include <string.h>

#ifndef STACK_CUSTOM
#define STACKSIZE 128
#define MAXKEYLEN 64
struct stack {
	int lineno;
	char key[MAXKEYLEN];
};
#else
#ifndef STACKSIZE
#define STACKSIZE 128
#endif
#endif

/* stack push and pop default function prototypes */
static int push_stack(int, char*);
static int pop_stack(int*, char*);

static struct stack prs_stack[STACKSIZE];
static int prs_stackp = 0;

#ifndef STACK_CUSTOM
/* push_stack:  push values onto stack; default function */
static int push_stack(int lineno, char *key)
{
	if (prs_stackp >= STACKSIZE)
		fprintf(stderr, "Error: stack full\n");
	else {
		if (strlen(key) <= MAXKEYLEN) {
			prs_stack[prs_stackp].lineno = lineno;
			strcpy(prs_stack[prs_stackp].key, key);
			prs_stackp++;
			return 0;
		} else
			fprintf(stderr, "Error: key value too large.\n");
	}
	return -1;
}

/* push_stack:  pop values off top of stack; default function */
static int pop_stack(int *lineno, char *key)
{
	if (prs_stackp <= 0)
		fprintf(stderr, "Error: stack empty.\n");
	else {
		--prs_stackp;
		*lineno = prs_stack[prs_stackp].lineno;
		strcpy(key, prs_stack[prs_stackp].key);
		return 0;
	}
	return -1;
}
#endif

#endif
