#include <string.h>

char *strstr(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;

    while (*p1 && *p2) {
        if (*p1 == *p2){
            p1++;
            p2++;
        } else {
            p1 -= p2 - s2 - 1;
            p2 = s2;
        }
    }
    return *p2 ? NULL : (char *)(p1 - (p2 - s2));
}
