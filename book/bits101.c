#include <stdio.h>

typedef char bool;

enum { FALSE, TRUE };

#define true 1
#define false 0

#define SET_BIT(var, bit) var |= (1 << bit)
#define CLR_BIT(var, bit) var &= ~(1 << bit)
#define GET_BIT(var, bit) ((bit >= 0 && bit < 8) ? (var >> bit) & 1 : 2)

#define BYTE_SIZE(var) sizeof(var)*8
#define OUT_OF_RANGE 2

int main()
{
	bool byte = 0;
	int i;

	for (i=0; i<BYTE_SIZE(byte); i++) {
		printf("%d ", GET_BIT(byte, i));
		if ((i % 4) == 3)
			printf("\n", GET_BIT(byte, i));
	}
	SET_BIT(byte, 0);
	SET_BIT(byte, 2);
	SET_BIT(byte, 4);
	SET_BIT(byte, 6);
	for (i=0; i<BYTE_SIZE(byte); i++) {
		printf("%d ", GET_BIT(byte, i));
		if ((i % 4) == 3)
			printf("\n", GET_BIT(byte, i));
	}
	printf("Bit number 20: %s\n",
	(GET_BIT(byte, 20) == OUT_OF_RANGE) ? "Out of range" : "In range");
	return byte;
}
