#include <stdio.h>

int main(void)
{
	int n;
	int *p;

	printf("The size of int  = %u bite\n", (unsigned)sizeof(int));
	printf("The size of int *= %u bite\n", (unsigned)sizeof(int *));

	printf("The size of   n  = %u bite\n", (unsigned)sizeof(n));
	printf("The size of  *p  = %u bite\n", (unsigned)sizeof(*p));
	printf("The size of   p  = %u bite\n", (unsigned)sizeof(p));
	printf("The size of  &n  = %u bite\n", (unsigned)sizeof(&n));

	return 0;
}
