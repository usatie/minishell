# include <stdio.h>

void fill_zero(int a[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		a[i] = 0;
}

int main(void)
{
	int i;
	int x[5] = {1, 2, 3, 4, 5};
	int x_size = sizeof(x) / sizeof(x[0]);

	fill_zero(x, x_size);

	for (i = 0; i < x_size; i++)
		printf("x[%d] = %d\n", i, x[i]);

	return 0;
}
