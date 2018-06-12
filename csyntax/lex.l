%{
#include <stdio.h>
#include <string.h>
#include "grammer.tab.h"

extern int yylineno;
extern void yyerror(const char*);
void comment();
%}

%%
\n			{ ++yylineno; }
"/*"			{ comment(); }
[ \t\n]		{}

"{"			{ return OPEN_BRACE; }
"}"			{ return CLOSE_BRACE; }
"("			{ return OPEN_PAREN; }
")"			{ return CLOSE_PAREN; }
";"			{ return SEMI_COLON; }

"int"			{ return TYPE; }
"void"			{ return TYPE; }
"char"			{ return TYPE; }

"return"		{ return RETURN; }
[a-zA-Z_][a-zA-Z0-9_]*	{ return IDENTIFIER; }
[0-9]+			{ return NUMBER; }

"#include"		{ return INCLUDE; }
"<"[a-zA-Z.]+">"	{ return INCLUDE_NAME; }
%%

#define INPUT_EOF 0
#define MAXLEN 256

void comment()
{
	char msg[MAXLEN];
	int c, prev = 0;

	while ((c = input()) != INPUT_EOF) {
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	sprintf(msg, "Unterminated comment, line %d.\n", yylineno);
	yyerror(msg);
}
