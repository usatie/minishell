#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[128];
    char sep[] = ".,;";
    char *p;

    printf("文字列を入力してください:");
    scanf("%s", str);

    p = strtok(str, sep);
    while (p != NULL){
        printf("%s\n", p);
        p = strtok(NULL, sep);
    }
    return 0;
}
