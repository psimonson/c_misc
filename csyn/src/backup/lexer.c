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
			fread(buffer, 1, size, fp);
			buffer[size+1] = '\0';
			count = parse_lexdefines(buffer, defs, MAXDEFINES);

			for (i = 0; i < count; i++)
				printf("read_file: key %s, def %s\n", defs[i].key, defs[i].def);
			free(buffer);
			return 0;
		} else
			fprintf(stderr, "Error: memory allocation error.\n");
	}
	return -1;
}
