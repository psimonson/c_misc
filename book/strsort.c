#include "common/helper.h"

#define MAXLINES 5000	/* max number of lines to be sort */
#define MAXLEN 1000	/* max length of any input line */
#define MAXSTORE 10000	/* max space allocated for all lines */

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *store);
void writelines(char *lineptr[], int nlines);
void _qsort(char *v[], int left, int right);

int main(void)
{
	char linestore[MAXSTORE];
	int nlines;	/* number of input lines read */
	int i;

	if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0) {
		_qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	}
	printf("Error: input too big to sort.\n");
	return 1;
}

int readlines(char *lineptr[MAXLEN], int maxlines, char *store)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	p = store + str_len(store);
	while ((len = getstr(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (str_len(store) + len) > MAXSTORE)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			str_cpy(p, line);
			lineptr[nlines++] = p;
			p += len; /* point p to next empty position */
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void _qsort(char *v[], int left, int right)
{
	int i, last;
	void _swap(char *v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	_swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (str_cmp(v[i], v[left]) < 0)
			_swap(v, ++last, i);
	_swap(v, left, last);
	_qsort(v, left, last-1);
	_qsort(v, last+1, right);
}

void _swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
