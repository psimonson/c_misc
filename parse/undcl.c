#include <stdio.h>
#include "parser.h"

/* undcl:  convert word description to declaration */
int main()
{
	int type, prevtype = PARENS;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if (prevtype == PARENS ||
					prevtype == BRACKETS) {
					sprintf(temp, "(*%s)", out);
					strcpy(out, temp);
				} else {
					sprintf(temp, "*%s", out);
					strcpy(out, temp);
				}
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		prevtype = type;
		printf("%s\n", out);
	}
	return 0;
}
