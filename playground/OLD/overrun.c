#include <stdio.h>

int	main(void)
{
	int	a;
	int	b[2];
	int	c;

	a = __INT_MAX__;
	c = 0;
	printf("a = %p\nb = %p\nc = %p\n", &a, &b, &c);
	for (int i = -5; i < 100; i++)
	{
		b[i] = i;
	}
	printf("a : %d, c : %d\n", a, c);
	printf("b[0] : %d, b[1] : %d\n", b[0], b[1]);
}
