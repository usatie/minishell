# include <stdio.h>


void func(int p[])
{
	printf("sizeof(p) = %u\n", (unsigned)sizeof(p));
}

int main(void)
{
	int a[5];

	printf("sizeof(a) = %u\n", (unsigned)sizeof(a));

	func(a);

	return 0;
}
