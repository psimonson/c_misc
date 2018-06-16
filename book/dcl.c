#include <stdio.h>
#include "parser.h"

extern int tokentype;

main() /* convert declaration to words */
{
	while (gettoken() != EOF) {
		strcpy(datatype, token); /* 1st token is data type */
		out[0] = '\0';
		dcl();	/* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
