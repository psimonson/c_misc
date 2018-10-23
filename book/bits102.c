#include <stdio.h>

#define SET_BIT(var, pos) var |= 1 << pos
#define CLR_BIT(var, pos) var &= ~(1 << pos)

#define SET_VAR(var) var |= ~var
#define CLR_VAR(var) var &= ~var

/* program for bit manipulation */

int main()
{
	char byte = 0xff;
	int i;

	CLR_VAR(byte);
	printf("Byte is now %x = %d\n", byte, byte);
	for (i=0; i<8; i++) {
		CLR_VAR(byte);
		SET_BIT(byte, i);
		printf("bit %d = %d\n", i, byte);
	}
	SET_VAR(byte);
	printf("Byte is now %x = %d\n", byte, byte);
	return 0;
}
