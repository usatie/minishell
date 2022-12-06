#include <stdio.h>
int main(void)
{
    int n;
    long k;
    char s[20];

    printf("Enter n :");
    scanf("%d", &n);

    printf("Enter k :");
    scanf("%ld", &k); 

    printf("Enter s :");
    scanf("%s", s);

    printf("print n  : %d\n", n);
    printf("print k  : %ld\n", k);
    printf("print ld : %s\n", s);

    return 0;
}