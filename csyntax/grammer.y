%{
#include <stdio.h>
#include <string.h>
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
	RETURN NUMBER SEMI_COLON
	;

%%
