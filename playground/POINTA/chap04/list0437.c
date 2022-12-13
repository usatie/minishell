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

/*
int main()
{
    const char *s1 = "hello '$PATH' world";
    const char *s2 = " $'";
    char *s = s1;

    printf("%s\n", s);
    while (s = strpbrk(s, s2)){
        printf("%s\n", s);
        s++;
    }

    return 0;
}
*/

// list0438.c
/*
int main(void)
{
    char s1[128], s2[128];
    char *p;

    printf("文字列s1:");  scanf("%s", s1);
    printf("文字列s2:");  scanf("%s", s2);

    if ((p = strpbrk(s1, s2)) == NULL)
        printf("文字列s2中のどの文字も文字列s1中には存在しません\n");
    else
        printf("文字列s2中に含まれる文字の文字列s1での最初の出現以降は\"%s\"です\n", p);
    return 0;
}
*/

// list0439.c
int main (void)
{
    char str[128];
    char ultr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p;

    printf("文字列を入力してください:");
    scanf("%s", str);

    puts("その文字列に含まれる英大文字は以下の通りです");

    p = str;

    while ((p = strpbrk(p, ultr)) != NULL)
        putchar(*p++);
    putchar('\n');

    return 0;
}
