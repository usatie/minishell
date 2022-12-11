#include <stdio.h>

int main(void)
{
    char s1[256], s2[256];

    s1 = "ABC";
    s2 = s1 + "DEF";

    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);

    return 0;
}
