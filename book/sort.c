#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000		/* max #lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right,
		int (*comp)(void *, void *));
int numcmp(char *, char *);

int main(int argc, char *argv[])
{
	int nlines;		/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */

	if (argc > 1 && !strcmp(argv[1], "-n"))
		numeric = 1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		_qsort((void **)lineptr, 0, nlines-1,
			numeric ? (int (*)(void*,void*))numcmp : (int (*)(void*,void*))strcmp);
		writelines(lineptr, nlines);
		return 0;
	} else
		printf("Input too big...\n");
	return 1;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void _qsort(void *v[], int left, int right,
		int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	_qsort(v, left, last-1, comp);
	_qsort(v, last+1, right, comp);
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	return 0;
}

/* swap:  swap v[j] with v[i] */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#define MAXLEN 1000
char *alloc(int);
int get_line(char*, int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* get_line:  gets a line of input */
int get_line(char *s, int lim)
{
	char *p = s;
	int c;
	
	while ((c = getchar()) != EOF && c != '\n')
		*p++ = c;
	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return p-s;
}

#define ALLOCSIZE (1000*MAXLEN)
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int nsize)
{
	if (allocbuf + ALLOCSIZE - allocp >= nsize) { /* it fits */
		allocp += nsize;
		return allocp-nsize;
	} else
		printf("alloc: out of memory.\n");
	return 0;
}
