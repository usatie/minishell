#include <stdio.h>

void scan2double(double *x1, double *x2)
{
    printf("First : ");
    scanf("%lf", x1);

    do {
        printf("Second : ");
        scanf("%lf", x2);
    } while (*x2 < *x1);
}

int main(void)
{
    double a,b,c,d;

    puts ("AとBを昇順に入力せよ");
    scan2double(&a, &b);

    printf("Diff a and b : %f\n", b - a);

    return 0;
}