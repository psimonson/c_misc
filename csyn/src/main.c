#include "common/helper.h"
#include <string.h>
#include "stack.h"

#define STATE_QUOTE   0
#define STATE_COMMENT 1
#define STATE_CODE    2

main()
{
	void check_phase2();
	extern int search(int);
	extern int getch();
	extern int state;
	int c;

	while ((c = getch()) != EOF)
		state = search(c);
	if (state == STATE_CODE)
		check_phase2();
	else if (state == STATE_COMMENT)
		printf("Unterminated comment.\n");
	else if (state == STATE_QUOTE)
		printf("Unterminated quotes.\n");
	else
		printf("No errors found.\n");
	return 0;
}

void check_phase2()
{
	extern struct stack stack[];
	extern int lines;
	int i;

	for (i = 0; i < lines; i++) {
		char *tmp;
		
		tmp = strtok(stack[i].text, " \n\r\t()");
		while (tmp) {
			if (!strcmp(tmp, "int") || !strcmp(tmp, "void")
				|| !strcmp(tmp, "char") || !strcmp(tmp, "long")
				|| !strcmp(tmp, "main") || !strcmp(tmp, "{")
				|| !strcmp(tmp, "}") || !strcmp(tmp, "(")
				|| !strcmp(tmp, ")"))
				printf("No errors on line %d.\n", stack[i].lineno);
			else
				printf("Error: %s at line %d.\n", tmp, stack[i].lineno);
			tmp = strtok(NULL, " \n\r\t()");
		}
	}
}
