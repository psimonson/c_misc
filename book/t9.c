#include "common/helper.h"

int main()
{
	char buf[10];
	int res;

	mem_set(buf, 0, sizeof buf);
	str_cpy(buf, "5000");
	res = p_atoi(buf);

	printf("String: %s\nInteger: %d\n"
		"Int 1: %d\nInt 2: %d\n", buf, res,
		p_atoi("600"), p_atoi("-570"));
	return 0;
}
