#include "common/helper.h"

int main()
{
	char test[10] = "Hello.";

	printf("Original: %s\n", test);
	mem_set(test, 0, sizeof test);
	printf("Current: %s\n", test);
	return 0;
}
