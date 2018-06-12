#include <stdio.h>
#include <string.h>

typedef enum Boolean { FALSE, TRUE } bool;
#define false 0
#define true 1

int main(int argc, char *argv[])
{
    bool opt_a, opt_b;

    opt_a = opt_b = false;
    while(--argc > 0 && *(++argv)[0] == '-')
            while(*++argv[0])
                switch(*argv[0]) {
                    case 'a':
                        opt_a = true;
                        break;
                    case 'b':
                        opt_b = true;
                        break;
                    default:
                        printf("Unknown option '%c'.\n", (*argv)[0]);
                        argc = 0;
                        break;
                }
    if (argc != 1)
        printf("Usage: %s -[ab] <text>\n", argv[0]);
    else
	while(*argv != NULL) {
            if (opt_a)
                printf("First character of string: %c\n", (*argv)[0]);
            if (opt_b)
                printf("Last character of string: %c\n", (*argv)[strlen(*argv)-1]);
            printf("Full string entered: %s\n", *argv);
	    argv++;
        }
    return 0;
}
