#include <stdio.h>

#define swap(t, x, y) do {t temp = x; x = y; y = temp;} while(0)

int main()
{
	int a = 50;
	int b = 100;

	swap(int, a, b);
	return a-b;
}
