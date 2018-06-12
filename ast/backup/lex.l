%{
#include "grammer.tab.h"
extern int yylineno;
extern char *yytext;
extern void yyerror(const char *);
void comment();
%}

%%
\n		{ ++yylineno; }
"/*"		{ comment(); }
"+"		{ return BINARY_OP; }
"-"		{ return BINARY_OP; }
"*"		{ return BINARY_OP; }
"/"		{ return BINARY_OP; }

[0-9]+		{ return NUMBER; }
[a-zA-Z0-9]	{ return IDENTIFIER; }
[ \n\r\t\v\f]	{ return WHITESPACE; }
"return"	{ return RETURN; }
"int"		{ return TYPE; }
"void"		{ return TYPE; }
"char"		{ return TYPE; }
"short"		{ return TYPE; }
"long"		{ return TYPE; }
"float"		{ return TYPE; }
"double"	{ return TYPE; }

"#include"	{ return INCLUDE; }
[a-zA-Z0-9.*]+	{ return HEADER_NAME; }
.		{}
%%

void comment()
{
	int c, prev = 0;
	while ((c = input()) != 0) {
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	yyerror("Unterminated comment");
}
