%{
	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	void yyerror(const char *);
%}

%define api.value.type {double}

%token NAME COLON RIGHT_ARROW LEFT_BRACE RIGHT_BRACE SEMICOLON
%start input

%%
input:
	NAME COLON RIGHT_ARROW LEFT_BRACE statements RIGHT_BRACE	{}
	| %empty

statements:
	statements statement						{}
	| %empty

statement:
	NAME SEMICOLON							{}
%%

void yyerror(const char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}
