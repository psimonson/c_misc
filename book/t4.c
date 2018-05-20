#include "common/helper.h"

int main()
{
	char msg[] = "Hello world, this is a test.";
	char buf[64];
	int len;

	mem_set(buf, 0, sizeof buf);
	len = str_cpy(buf, "I say hey... ");
	puts(buf);
	printf("%d\n", len);
	len = str_cat(buf, msg);
	puts(buf);
	printf("%d\n", len);
	return 0;
}
