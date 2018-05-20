#include "common/helper.h"

int main()
{
	char msg[] = "This is some long text.";
	char msg2[50];

	mem_set(msg2, 0, sizeof msg2);
	mem_cpy(msg2, msg, str_len(msg));
	printf("Original: %s\nCopied: %s\n", msg, msg2);
	return 0;
}
