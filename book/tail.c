#include <stdio.h>
#include <stdlib.h>

typedef enum Boolean { FALSE, TRUE } bool;
#define false 0
#define true 1

#define MAXLINES 10
#define MAXLINE 512

int process_file(FILE *fp, int maxlines)
{
    char *linep, line[MAXLINE];
    int c, i, linecnt;

    i = 0;
    do {
        c = fgetc(fp);
        if (c == '\n')
            i++;
    } while(c != EOF);
    rewind(fp);
    linecnt = 0;
    do {
        linep = fgets(line, sizeof(line), fp);
        if (linep != NULL && linecnt >= i-maxlines) {
		printf("%s", line);
	}
	linecnt++;
    } while (linep != NULL);
    return i;
}

int main(int argc, char *argv[])
{
    bool op_n = false;
    while(--argc > 0 && (*++argv)[0] == '-')
        while(*++argv[0])
            switch(*argv[0]) {
                case 'n':
                    op_n = true;
                    break;
                default:
                    printf("tail: Unknown option '%c'.\n", (*argv)[0]);
                    break;
            }
    if (argc < 1 || argc > 2)
        printf("Usage: tail [-n count] <filename.ext>\n");
    else {
        FILE *fp;
        int nlines = MAXLINES;

        if (op_n)
            nlines = atoi(*argv++);
        if ((fp = fopen(*argv, "rt")) == NULL) {
            printf("tail: Cannot open '%s' for reading.\n", *argv);
            return 1;
        }
        (void)process_file(fp, nlines);
        fclose(fp);
    }
    return 0;
}
