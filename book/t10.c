#include "common/helper.h"

/* str_pbrk:  find first occurrence of t in s, return s */
char *str_pbrk(const char *s, const char *t)
{
	while (*s != '\0') {
		const char *a = t;
		while (*a != '\0')
			if (*a++ == *s)
				return (char*)s;
		++s;
	}
	return NULL;
}

#define MAXLEN 64

int main(int argc, char *argv[])
{
	char line[MAXLEN];
	char pattern[MAXLEN];
	char *tmp;

	get_input("Enter string: ", line, MAXLEN);
	get_input("Enter pattern: ", pattern, MAXLEN);
	(void)trim(line);
	(void)trim(pattern);
	tmp = str_pbrk(line, pattern);
	printf("Original string: %s\n", line);
	printf("Returned string: %s\n", tmp);
	return 0;
}
