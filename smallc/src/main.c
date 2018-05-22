#include "common/helper.h"

extern int yyparse();
extern int yyerror(const char *);
extern int yylex();
extern int yylineno;

int main()
{
	int result;

	result = yyparse();
	if (!result)
		printf("The input is valid!\n");
	else
		printf("The input is not valid!\n");
	printf("Lines in input file are: %d\n", yylineno);
	return result;
}
