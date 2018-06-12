#include "stack.h"
#include <stdlib.h>
#include <ctype.h>

struct lex_define {
	char *key;
	char *def;
};

/* trim:  strip from line of text; tokens  */
char *trim(char *str, char *end)
{
	while (isspace(*str)) *str++;
	while (isspace(*--end));
	end[1] = '\0';
	return str;
}

/* parse_keyval:  actually parse the string; splitting into tokens */
void parse_keyval(char *str, char *end, struct lex_define *def)
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
int parse_lexdefines(char *line, struct lex_define *defs, int maxdefs)
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
int read_file(FILE *fp)
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
			return errors;
		} else
			fprintf(stderr, "Error: memory allocation error.\n");
	}
	return -1;
}

#define MAXLINE 512

/* analyze:  check code file for syntax errors; return error count */
int analyze(const char *filename, struct lex_define *defs, int count)
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
				push_stack(lineno, old);
				errors++;
			}
			tmp = strtok(NULL, " \r\n\t");
		}
	}
	if (errors)
		for (i = 0; i < errors; i++) {
			char key[64];
			int ln;

			pop_stack(&ln, key);
			printf("Key: %s\tLine:%d\n",
				key, ln);
		}
	fclose(fp);
	return errors;
}
