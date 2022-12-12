#include <stddef.h>
#include <stdio.h>

char *strpbrk(const char *s1, const char *s2)
{
    for ( ; *s1; s1++) {
        const char *t = s2;
        for ( ; *t; t++)
            if (*t == *s1)
                return (char *)s1;
    }
    return NULL;
}

int main()
{
    const char *s1 = "RADIANCE";
    const char *s2 = "ABCD";

    printf("%s\n", strpbrk(s1, s2));
    return 0;
}
