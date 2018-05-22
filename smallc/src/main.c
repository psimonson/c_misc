#include "common/helper.h"

extern FILE *yyin;
extern int yyparse();
extern int yyerror(const char *);

int main(int argc, char **argv)
{
	if (argc > 1)
		if ((yyin = fopen(*++argv, "rb")) == NULL) {
			fprintf(stderr, "File: %s open error.\n", *argv);
			return 1;
		}
	else
		yyin = stdin;

	yyparse();
	write_skeleton();
	printf("Written out.s\n");
	return 0;
}
