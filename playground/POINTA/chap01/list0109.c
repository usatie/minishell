#include <stdio.h>

int main(void)
{
	int n;
	int *p = &n;

	printf("&n : %lu\n", (unsigned long)&n);
	printf(" p : %lu\n", (unsigned long)p);

	return 0;
}
