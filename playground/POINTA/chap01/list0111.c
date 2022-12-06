#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main (void)
{
    int a,b;
    puts("2つの整数を入力してください");
    printf("整数A : "); scanf("%d", &a);
    printf("整数B : "); scanf("%d", &b);

    swap(&a, &b);

    puts("AとBを交換しました");

    printf("整数A : %d\n", a);
    printf("整数B : %d\n", b);

    return 0;
}