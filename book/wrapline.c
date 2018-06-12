#include <stdio.h>
#include <ctype.h>

#define MAXLINES 10
#define MAXLINE 1000
#define WRAPLEN 80

static char linebuffer[MAXLINE];
static char *linep = linebuffer;

int readline(void);
void scanline(const int);

main()
{
	extern char *linep;

	while (readline() > 0) {
		scanline(WRAPLEN);
		printf("%s", linebuffer);
	}
}

int readline(void)
{
	extern char *linep;
	char *line;
	int c;
	line = linep;
	while ((line-linep) < MAXLINE-1 && (c = getchar()) != EOF && c != '\n')
		*line++ = c;
	if (c == '\n')
		*line++ = c;
	*line = '\0';
	return line-linep;
}

void scanline(const int wraplen)
{
	extern char *linep;
	char *line;
	line = linep;
	while (*line) {
		if ((line-linep) > 0 && ((line-linep) % wraplen) == 0) {
			if (!isspace(*line)) {
				int lastpos = (line-linep);
				while (!isspace(*line)) --line;
				*line = '\n';
				while ((line-linep) <= lastpos)
					++line;
			}
			printf("Hello.\n");
		}
		line++;
	}
}
