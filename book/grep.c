#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getln(char *line, int lim)
{
	int c, i;

	for (i = 0; --lim > 0 && (c = getchar()) != EOF && c != '\n'; i++)
		*line++ = c;
	if (c == '\n') {
		*line++ = c;
		i++;
	}
	*line = '\0';
	return i;
}

main(int argc, char *argv[])
{
	char line[MAXLINE];
	int found = 0;

	if (argc != 2)
		printf("Usage: %s pattern\n", *argv);
	else {
		++argv;
		while (getln(line, MAXLINE) > 0)
			if (strstr(line, *argv) != NULL) {
				printf("%s", line);
				found++;
			}
	}
	return found;
}
