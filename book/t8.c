#include "common/helper.h"

/* program to test reverse and p_itoa */
int main()
{
	char buf[32];
	int p;

	mem_set(buf, 0, sizeof buf);
	p = 5000;
	p_itoa(p, buf);
	printf("%s\n", buf);
	mem_set(buf, 0, sizeof buf);

	str_cpy(buf, "Hello world.");
	printf("Before: %s\n", buf);
	reverse(buf);
	printf("After: %s\n", buf);

	return 0;
}
