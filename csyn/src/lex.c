#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct lex_define {
	char *key;
	char *def;
};

/* trim:  strip from line of text; tokens  */
char *trim(str, end)
	char *str;
	char *end;
{
	while (isspace(*str)) *str++;
	while (isspace(*--end));
	end[1] = '\0';
	return str;
}

/* parse_keyval:  actually parse the string; splitting into tokens */
void parse_keyval(str, end, def)
	char *str;
	char *end;
	struct lex_define *def;
{
	char *sep = strstr(str, "::=");
	if (!sep) {
		fprintf(stderr, "Parse error, missing \"::=\"\n");
		def->key = def->def = NULL;
		return;
	}
	def->key = trim(str, sep);
	def->def = trim(sep+3, end);
}

/* parse_lexdefines:  parses lex defines; calling parse_keyval on every one */
int parse_lexdefines(line, defs, maxdefs)
	char *line;
	struct lex_define *defs;
	int maxdefs;
{
	int count = 0;
	char *str = line;
	char *end;

	while (count < maxdefs && (end = strchr(str, '\n'))) {
		parse_keyval(str, end, &defs[count++]);
		str = end+1;
	}
	return count;
}

#define MAXDEFINES 128

/* read_file:  gets a line of input from a file pointer */
int read_file(fp)
	FILE *fp;
{
	extern int analyze();

	if (fp) {
		struct lex_define defs[MAXDEFINES];
		char *buffer;
		int count, i;
		size_t size;

		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		rewind(fp);

		buffer = (char*)malloc(size+1);
		if (buffer) {
			int errors;

			fread(buffer, 1, size, fp);
			buffer[size+1] = '\0';
			count = parse_lexdefines(buffer, defs, MAXDEFINES);
#ifdef DEBUG
			for (i = 0; i < count; i++)
				printf("read_file: key %s, def %s\n", defs[i].key, defs[i].def);
#endif
			errors = analyze("code.txt", defs, count);
			free(buffer);
			printf("Errors in code.txt: %d\n", errors);
			return 0;
		} else
			fprintf(stderr, "Error: memory allocation error.\n");
	}
	return -1;
}

#define MAXLINE 512

/* analyze:  check code file for syntax errors; return error count */
int analyze(filename, defs, count)
	const char *filename;
	struct lex_define *defs;
	int count;
{
	extern void push();
	extern void pop();
	char line[MAXLINE];
	int errors, i;
	int lineno;
	FILE *fp;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Error: opening code.txt for reading.\n");
		return -1;
	}
	errors = lineno = 0;
	while (fgets(line, MAXLINE, fp) != NULL) {
		char *tmp, *old = NULL;
		char found;

		++lineno;
		found = 0;
		tmp = strtok(line, " \r\n\t");
		while (tmp) {
			old = tmp;
			for (i = 0; i < count; i++)
				if (!strcmp(tmp, defs[i].key)) {
					found = 1;
					break;
				} else
					found = 0;
			if (!found) {
				push(lineno, old);
				errors++;
			}
			tmp = strtok(NULL, " \r\n\t");
		}
	}
	if (errors)
		for (i = 0; i < errors; i++) {
			char key[64];
			int ln;

			pop(&ln, key);
			printf("Key: %s\tLine:%d\n",
				key, ln);
		}
	fclose(fp);
	return errors;
}

#define MAXSTACK 100
#define MAXKEY   64

struct stack {
	int lineno;
	char key[MAXKEY];
};

struct stack stack[MAXSTACK];
static int stackp = 0;

/* push:  push line,key to stack */
void push(line, key)
	int line;
	char *key;
{
	if (stackp >= MAXSTACK)
		printf("Error: stack full.\n");
	else {
		stack[stackp].lineno = line;
		strcpy(stack[stackp].key, key);
		stackp++;
	}
}

/* pop:  pop line,key from stack */
void pop(line, key)
	int *line;
	char *key;
{
	if (stackp <= 0)
		printf("Error: stack empty.\n");
	else {
		--stackp;
		*line = stack[stackp].lineno;
		strcpy(key, stack[stackp].key);
	}
}
