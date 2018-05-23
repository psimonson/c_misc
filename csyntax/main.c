#include <stdio.h>

extern int yywrap(void);
extern int yyparse(void);
extern int yylineno;
extern void *yytext;

int main(argc, argv)
	int argc;
	char **argv;
{
	int result;
	result = yyparse();
	if (!result)
		printf("Scanned: No errors!\n");
	else
		printf("Scanned: With error %s at line %d\n", yytext, yylineno);
	return 0;
}
