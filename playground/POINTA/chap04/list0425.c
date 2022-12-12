#include <stdio.h>

char *strcpy(char *s1, const char *s2)
{
    char *p = s1;

    while ((*s1++ = *s2++));
    return p;
}

int main(void)
{
    const char *s1 = "123";
    char s2[128];
    char *ret;
    ret = strcpy(s2, s1);

    printf("s1 = %s, s2 = %s, ret = %s\n", s1, s2, ret);
    return 0;
}
