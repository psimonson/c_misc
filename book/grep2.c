#include <stdio.h>
#include <string.h>
#define MAXLINE 256

#undef getline
int getline(char *line, int lim);

main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("%s: illegal option %c\n", argv[0], c);
				argc = 0;
				found = -1;
				break;
			}
	if (argc != 1)
		printf("Usage: %s -x -n pattern\n", argv[0]);
	else
		while (getline(line, MAXLINE) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld: ", lineno);
				printf("%s", line);
				found++;
			}
		}
	return found;
}

int getline(char *line, int lim)
{
	int c, i;

	for (i = 0; lim-- > 0 && (c = getchar()) != EOF && c != '\n'; i++)
		*line++ = c;
	if (c == '\n') {
		*line++ = c;
		i++;
	}
	*line = '\0';
	return i;
}
