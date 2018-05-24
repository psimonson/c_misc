#include <stdio.h>

main()
{
	extern int parse_lexdefines();
	int result;
	FILE *fp;

	if ((fp = fopen("lex.txt", "r")) == NULL) {
		fprintf(stderr, "Error: opening file for reading.\n");
		return 1;
	}
	result = read_file(fp);
	fclose(fp);
	if (!result)
		printf("File processed okay!\n");
	else
		printf("Failed to process!\n");
	return 0;
}
