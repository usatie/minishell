#include <stdio.h>
#include <string.h>

int main(void)
{
    int i;
    char s1[128], s2[128];
    char *p;

    printf("文字列s1:"); scanf("%s", s1);
    printf("文字列s2:"); scanf("%s", s2);

    p = strstr(s1, s2);

    if (p == NULL)
        printf("文字列s1中には文字列s2は存在しません\n");
    else {
        int ofs = p - s1;
        printf("\n%s\n", s1);
        printf("%*s|\n", ofs, "");
        printf("%*s%s\n", ofs, "", s2);
    }
    return 0;
}
