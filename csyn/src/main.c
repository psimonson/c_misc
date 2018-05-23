#include "common/helper.h"
#include "stack.h"

#define STATE_QUOTE   0
#define STATE_COMMENT 1
#define STATE_CODE    2

int main()
{
	extern int search(int);
	extern int getch();
	extern struct stack mystack[];
	extern int state;
	extern int lines;
	int c, i;

	while ((c = getch()) != EOF)
		state = search(c);
	for (i = 0; i < lines; i++) {
		printf("%d: %s\n", mystack[i].lineno, mystack[i].text);
	}
	if (state == STATE_CODE)
		printf("No errors found!\n");
	else
		printf("Code ended inside : %s\n", (state == STATE_QUOTE) ? "Quotations" : "Comment");
	return 0;
}
