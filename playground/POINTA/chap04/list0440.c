#include <string.h>
#include <stdio.h>

char *strstr(const char *s1, const char *s2)
{
    if (*s2 == '\0')
        return (char *)s1;

    for ( ; (s1 = strchr(s1, *s2))!= NULL; s1++){
        const char *sc1 = s1;
        const char *sc2 = s2;

        do {
            if (*++sc2 == '\0')
                return (char *)s1;
        } while (*++sc1 == *sc2);
    }
    return NULL;
}

int main(void)
{
    const char *s1 = "ABC";
    const char *s2 = "B";

    printf("%s\n", strstr(s1, s2));
    return 0;
}
