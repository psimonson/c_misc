#include "common/helper.h"

int main()
{
	char buf[64];
	char buf2[64];
	int res;

	str_cpy(buf, "Hello world.");
	str_cpy(buf2, "Hello world.");
	res = str_cmp(buf, buf2);
	printf("Buf 1: %s\nBuf 2: %s\nStatus: %s\n", buf, buf2,
		(res == 0) ? "Match" : "Don't match");

	str_cpy(buf, "Hello World.");
	str_cpy(buf2, "Hello world.");
	res = str_cmp(buf, buf2);
	printf("Buf 1: %s\nBuf 2: %s\nStatus: %s\n", buf, buf2,
		(res == 0) ? "Match" : "Don't match");

	str_cpy(buf, "Hellb world.");
	str_cpy(buf2, "Hello world.");
	res = str_cmp(buf, buf2);
	printf("Buf 1: %s\nBuf 2: %s\nStatus: %s\n", buf, buf2,
		(res == 0) ? "Match" : "Don't match");

	return 0;
}
