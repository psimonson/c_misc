#include "common/helper.h"

int main(void)
{
	char buf[64];

	mem_set(buf, 0, sizeof buf);
	printf("Original: %s\n", buf);
	strn_cat(buf, "Hello world!\n", 12);
	printf("Current: %s\n", buf);
	return 0;
}
