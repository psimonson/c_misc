%{
#include <stdio.h>
#include "grammer.tab.h"
void comment();
%}


%%
\n		{ yylval = ++yylineno; }
[a-zA-Z][a-zA-Z0-9_] { return PARAMETER; }

"/*"		{ comment(); }
[ \t\n]+	{ /* discard whitespace */ }

"{"		{ return OPEN_BRACE; }
"}"		{ return CLOSE_BRACE; }
"("		{ return '('; }
")"		{ return ')'; }
"["		{ return '['; }
"]"		{ return ']'; }
";"		{ return ';'; }
[0-9]+		{ yylval=atoi(yytext); return NUMBER; }
"return"	{ return RETURN; }

"void"		{ return TYPE; }
"int"		{ return TYPE; }
"main"		{ return IDENTIFIER; }

"#include"	{ return INCLUDE; }
"<"[a-z.]+">"	{ return HEADER_NAME; }
%%

void comment()
{
	int c, prev = 0;

	while ((c = input()) != EOF)
		if (c == '*' && prev == '/')
			return;
	yyerror("unterminated comment");
}
