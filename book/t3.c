#include "common/helper.h"

int main()
{
	char buf[256];
	char msg[] = "Hello world!";

	mem_set(buf, 0, sizeof buf);
	str_cat(buf, msg);
	printf("Original: %s\nConcatenated: %s\n", msg, buf);
	return 0;
}
