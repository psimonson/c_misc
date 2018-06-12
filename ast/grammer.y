%{
extern char *yytext;
extern int yylineno;
extern int yylex(void);
int yywrap(void);
void yyerror(const char *);
%}

%token INCLUDE HEADER_NAME
%token TYPE IDENTIFIER RETURN NUMBER
%token BINARY_OP WHITESPACE
%start program

%%
program:
	function | header function
	;

header:
	INCLUDE '<' HEADER_NAME '>' | INCLUDE '"' HEADER_NAME '"'
	;

function:
	/* empty */ | functions function
	;

functions:
	TYPE IDENTIFIER '(' ')' '{' expression '}'
	;

expression:
	/* empty */ | expressions expression
	;

expressions:
	IDENTIFIER '(' ')' ';' | RETURN NUMBER ';'
	;
%%

#include <stdio.h>

int yywrap()
{
	return 1;
}

void yyerror(const char *msg)
{
	fprintf(stderr, "%s: line %d \"%s\"\n", msg, yylineno, yytext);
}
