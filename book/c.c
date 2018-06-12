#include <stdio.h>
#include <ctype.h>

#define MAXLINES 10
#define MAXLINE 1000

static char linebuffer[MAXLINE];
static char *linep = linebuffer;

int readline(void);
void scanline(void);

main()
{
	while (readline() > 0) {
		scanline();
		printf("%s", linebuffer);
	}
}

int readline(void)
{
	int c;
	char *line;
	line = linep;
	while ((line-linep) < MAXLINE-1 && (c = getchar()) != EOF && c != '\n')
		*line++ = c;
	if (c == '\n')
		*line++ = c;
	*line = '\0';
	return line-linep;
}

void scanline(void)
{
	char *line;
	line = linep;
	while (*line && ((line-linep) % 80) != 79) line++;
	if (((line-linep) % 80) == 79) {
		while (!isspace(*line)) --line;
		if (isspace(*line))
			*line = '\n';
	}
}
