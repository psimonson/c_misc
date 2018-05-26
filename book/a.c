#include "stack.h"

main()
{
	char key[64];
	int lineno;
	int result;

	result = push_stack(1, "Hello world!");
	if (result)
		printf("Error pushing to stack.\n");
	result = pop_stack(&lineno, key);
	if (result)
		printf("error pop from stack.\n");

	printf("%d: %s\n", lineno, key);
	return 0;
}

