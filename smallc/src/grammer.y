%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE char*
extern int yylineno;
extern char *yytext;

void yyerror(const char *msg)
{
	fprintf(stderr, "%s at line %d, %s\n", msg, yylineno, yytext);
	exit(1);
}

int yywrap()
{
	return 1;
}

void write_skeleton()
{
	extern FILE *yyin;
	FILE *out;

	if ((out = fopen("out.s", "wb")) == NULL) {
		yyerror("Cannot create file out.s");
		return;
	}

	fprintf(out, ".text\n");
	fprintf(out, "\t.global _start\n");
	fprintf(out, "_start:\n");
	fprintf(out, "\tmovl $0, %%ebx\n");
	fprintf(out, "\tmovl $1, %%eax\n");
	fprintf(out, "\tint $0x80\n");
	fclose(out);
}
%}

%token INCLUDE HEADER_NAME
%token TYPE IDENTIFIER RETURN NUMBER
%token OPEN_BRACE CLOSE_BRACE

%%
program:
	function | header function
	;

header:
	INCLUDE HEADER_NAME
	;

function:
	TYPE IDENTIFIER '(' ')' OPEN_BRACE expression CLOSE_BRACE
	;

expression:
	/* empty */ | RETURN NUMBER ';'
	;
%%

