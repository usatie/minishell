#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort2(int *n1, int *n2)
{
    if (*n1 > *n2)
        swap(n1, n2);
}

int main (void)
{
    int a, b;

    puts("Please enter two integers");
    printf("int a:"); scanf("%d", &a);
    printf("int b:"); scanf("%d", &b);

    sort2(&a, &b);

    puts("ソートしました");
    printf("int a : %d\n", a);
    printf("int b : %d\n", b);

    return 0;
}