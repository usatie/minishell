#include <stdio.h>

void swap(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

int main()
{
	int a,b;

	puts("Please enter two integers");
	printf("a : "); scanf("%d", &a);
	printf("b : "); scanf("%d", &b);

	swap(a, b); // Tada no cpy   Error!!!!!

	 
	puts("Did you think I swapped?????????");

	printf("a : %d\n", a);
	printf("b : %d\n", b);

	return 0;
}
