#include "common/helper.h"

#define STATE_QUOTE   0
#define STATE_COMMENT 1
#define STATE_CODE    2

int main()
{
	extern int search(int);
	extern int getch();
	int state, c;

	while ((c = getch()) != EOF)
		state = search(c);
	if (state == STATE_CODE)
		printf("No errors found!\n");
	else
		printf("Code ended inside : %s\n", (state == STATE_QUOTE) ? "Quotations" : "Comment");
	return 0;
}
