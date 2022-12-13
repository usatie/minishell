#include <string.h>
#include <stdio.h>

char *strstr(const char *s1, const char *s2)
{
    const char *p1 = s1;
    const char *p2 = s2;

    while (*p1 && *p2) {
        if (*p1 == *p2){
            p1++;
            p2++;
        } else {
            printf("s1 = %s, s2 = %s, p1 = %s, p2 = %s\n", s1,s2,p1,p2);
            p1 -= p2 - s2 - 1;
            p2 = s2;
        }
    }
    return *p2 ? NULL : (char *)(p1 - (p2 - s2));
}
/*
int main(void)
{
    const char *s1 = "ABCDEFG";
    const char *s2 = "DEF";

    char *s = strstr(s1, s2);
    printf("strstr = %s\n", s);
    return 0;
}
*/
