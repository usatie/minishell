#include <stddef.h>
#include <stdio.h>

size_t strspn(const char *s1, const char *s2)
{
    const char *p = s1;

    for ( ; *s1; s1++) {
        const char *t;

        for (t = s2; *t != *s1; t++)
            if (*t == '\0')
                return s1 - p;
    }
    return s1 - p;
}

/*
int main(void)
{
    const char *s1 = "HELLOAhOOOOOhelloWORLDDDDDDDD";
    const char *s2 = "HELO";

    printf("%lu\n", strspn(s1, s2));
    return 0;
}
*/
