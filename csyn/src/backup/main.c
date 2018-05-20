#include "common/helper.h"

#define MAXBUF 256

#define STRING   0
#define OPERATOR 1
#define NUMBER   2

int main()
{
	extern void pushnum(int);
	extern int num_empty();
	extern int popnum();
	extern int pop();
	char buf[MAXBUF];
	int type, a, b;

	while ((type = getop(buf)) != EOF)
		switch (type) {
			case OPERATOR:
				push(buf[0]);
				printf("Operator: '%c'\n", pop());
				break;
			case NUMBER:
				pushnum(atoi(buf));
				break;
			case STRING:
				printf("String found: %s\n", buf);
				break;
			case '+':
				if (!num_empty()) {
					b = popnum();
					a = popnum();
					printf("%d + %d = %d\n",
						a, b, a+b);
					pushnum(a+b);
				} else
					printf("Need two numbers for sign.\n");
				break;
			case '-':
				if (!num_empty()) {
					b = popnum();
					a = popnum();
					printf("%d - %d = %d\n",
						a, b, a-b);
					pushnum(a-b);
				} else
					printf("Need two numbers for sign.\n");
				break;
			case '/':
				if (!num_empty()) {
					b = popnum();
					a = popnum();
					printf("%d / %d = %d\n",
						a, b, a/b);
					pushnum(a/b);
				} else
					printf("Need two numbers for sign.\n");
				break;
			case '*':
				if (!num_empty()) {
					b = popnum();
					a = popnum();
					printf("%d * %d = %d\n",
						a, b, a*b);
					pushnum(a*b);
				} else
					printf("Need two numbers for sign.\n");
				break;
			case '%':
				if (!num_empty()) {
					b = popnum();
					a = popnum();
					printf("%d %% %d = %d\n",
						a, b, a%b);
					pushnum(a%b);
				} else
					printf("Need two numbers for sign.\n");
				break;
			default:
				break;
		}
	return 0;
}
