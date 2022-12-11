#include <stdio.h>

int main(void)
{
    char *s1 = "ABC";
    char *s2 = "ABC";

    *s1 = 'Z';

    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);

    return 0;
}
