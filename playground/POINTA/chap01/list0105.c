#include <stdio.h>

// ERROR!!
int main (void)
{
	register int n;
	printf("&n = %p\n", &n);
	return 0;
}
