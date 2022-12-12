#include <stdio.h>

int main(void)
{
    char s[10];

    printf("文字列を入力してください:");
    scanf("%s", s);

    if (s == "ABC")
        puts("あなたは\"ABC\"と入力しましたね");
    else
        puts("あなたは\"ABC\"と入力しませんでしたね");

    return 0;
}
