#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Boolean { FALSE, TRUE } bool;
#define false 0
#define true 1

#define MAXLINES 10
#define MAXLINE 512
#define TOTAL_LINES 1000

int process_file(FILE *fp, char *lines[], int maxlines)
{
	extern char* alloc(int);
	char *linep, line[MAXLINE];
	char *tmp;
	int c, i, j, linecnt;

	i = 0;
	do {
		c = fgetc(fp);
		if (c == '\n')
			i++;
	} while(c != EOF);
	rewind(fp);
	linecnt = 0;
	j = 0;
	do {
		linep = fgets(line, sizeof(line), fp);
		if (linep != NULL && linecnt >= i-maxlines) {
			if ((tmp = alloc(strlen(linep)+1)) != NULL) {
				strcpy(tmp, linep);
				tmp[strlen(linep)+1] = '\0';
				lines[j++] = tmp;
			}
		}
		linecnt++;
	} while (linep != NULL);
	return j;
}

int main(int argc, char *argv[])
{
	bool op_n = false;
	bool op_o = false;
	while(--argc > 0 && (*++argv)[0] == '-')
		while(*++argv[0])
			switch(*argv[0]) {
				case 'n':
					op_n = true;
					break;
				case 'o':
					op_o = true;
					break;
				default:
					printf("tail: Unknown option '%c'.\n",
						(*argv)[0]);
					argc = 0;
					break;
			}
	if (argc < 1 || argc > 3)
		printf("Usage: tail [-n count] <filename.ext> [outfile.ext]\n");
	else {
		FILE *fp;
		char *lines[TOTAL_LINES];
		int nlines = MAXLINES;
		int i;
		FILE *out;
		if ((argc == 2 || argc == 3) && op_n)
			nlines = atoi(*argv++);
		if ((fp = fopen(*argv, "rt")) == NULL) {
			printf("tail: Can't open '%s' for reading.\n",
				*argv);
			return 1;
		}
		if ((argc == 2 || argc == 3) && op_o)
			if ((out = fopen(*++argv, "wt")) == NULL) {
				printf("tail: Can't open '%s' for writing.\n",
					*argv);
				fclose(fp);
				return 2;
			}
		nlines = process_file(fp, lines, nlines);
		fclose(fp);
		if (op_o) {
			for(i = 0; i < nlines; i++)
				fprintf(out, "%s", lines[i]);
			fclose(out);
			printf("Done writing file: %s\n", *argv);
		} else {
			for(i = 0; i < nlines; i++)
				printf("%s", lines[i]);
		}
	}
	return 0;
}

#define ALLOCSIZE (TOTAL_LINES*MAXLINE)

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int nsize)
{
	if (allocbuf + ALLOCSIZE - allocp >= nsize) { /* it fits */
		allocp += nsize;
		return allocp-nsize;
	} else
		printf("alloc: Out of memory.\n");
	return 0;
}


