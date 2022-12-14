#include <stddef.h>

size_t strcspn(const char *s1, const char *s2)
{
    const char *p = s1;

    for ( ; *s1; s1++){
        const char *t;

        for (t = s2; *t; t++)
            if (*t == *s1)
                return s1 - p;
    }
    return s1 - p;
}

