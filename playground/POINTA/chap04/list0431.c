#include <stdio.h>

int strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2){
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int main(void)
{
    char *s1 = "123";
    char *s2 = "673";

    printf("%d\n", strcmp(s1, s2));
    return 0;
}

