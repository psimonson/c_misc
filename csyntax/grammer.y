%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern char *yytext;
extern int yylineno;

int yywrap(void)
{
	return 1;
}

void yyerror(const char *msg)
{
	fprintf(stderr, "%s: %s at line %d.\n", msg, yytext, yylineno);
	exit(1);
}
%}

%token OPEN_PAREN CLOSE_PAREN
%token OPEN_BRACE CLOSE_BRACE
%token RETURN IDENTIFIER NUMBER TYPE
%token INCLUDE INCLUDE_NAME
%token SEMI_COLON

%start program

%%

program:
	function | header function
	;

header:
	INCLUDE INCLUDE_NAME
	;

function:
	TYPE IDENTIFIER OPEN_PAREN CLOSE_PAREN OPEN_BRACE expression CLOSE_BRACE
	;

expression:
	/* empty */ | expressions expression
	;

expressions:
	SEMI_COLON | IDENTIFIER OPEN_PAREN CLOSE_PAREN SEMI_COLON | RETURN NUMBER SEMI_COLON
	;

%%
