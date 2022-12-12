#include <stdio.h>

char *strcat(char *s1, const char *s2)
{
    char *p = s1;
    while (*s1)
        s1++;
    while ((*s1++ = *s2++))
        ;
    return p;
}

char *strncat(char *s1, const char *s2, size_t n)
{
    char *p = s1;
    while (*s1)
        s1++;
    while (n--) {
        if (!(*s1++ = *s2++))
            break;
    }
    *s1 = '\0';

    return p;
}

char *strcpy(char *s1, const char *s2)
{
    char *p = s1;

    while ((*s1++ = *s2++));
    return p;
}

int main(void)
{
    char s[16];
    char *x = "ABC";

    strcpy(s, "QWE");
    strcat(s, "RTY");
    printf("s = %s\n", s);


    strcat(s, x); strncat(s, "123", 1);       printf("s = %s\n", s);
    strcat(s, x); strncat(s, "123", 3);       printf("s = %s\n", s);
    strcat(s, x); strncat(s, "123", 5);       printf("s = %s\n", s);
    strcat(s, x); strncat(s, "12345", 5);     printf("s = %s\n", s);
    strcat(s, x); strncat(s, "123456789", 5); printf("s = %s\n", s);

    return 0;
}
