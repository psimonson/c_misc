%{
#include <stdio.h>
#include "grammer.tab.h"
void comment();
extern int yylineno;
%}


%%
\n		{ ++yylineno; }

"/*"		{ comment(); }
[ \t\n]+	{ /* discard whitespace */ }

"{"		{ return OPEN_BRACE; }
"}"		{ return CLOSE_BRACE; }
"("		{ return '('; }
")"		{ return ')'; }
";"		{ return ';'; }
[0-9]+		{ return NUMBER; }
"return"	{ return RETURN; }

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
