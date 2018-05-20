#include "common/helper.h"

int main()
{
	char buf[64];
	int res;

	mem_set(buf, 0, sizeof buf);
	mem_cpy(buf, "Halo welt", str_len("Halo welt"));
	res = mem_cmp(buf, "Halo welt", str_len("Halo welt"));
	if (res == 0)
		puts("buf matches!");
	else
		puts("buf doesn't match!");

	mem_set(buf, 0, sizeof buf);
	strn_cpy(buf, "Hello", str_len("Hello"));
	strn_cat(buf, " Test", 4);
	res = str_cmp(buf, "Hello Test");
	if (res == 0)
		puts("buf matches!");
	else
		puts("buf doesn't match!");
	return 0;
}
