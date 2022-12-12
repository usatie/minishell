#include <stdio.h>

int main(void)
{
    char s1[] = {'A', 'B', 'C', '\0'};
    char s2[] = {"ABC"};
    char s3[] = "ABC";

    printf("配列s1に文字列\"%s\"が格納されています\n", s1);
    printf("配列s2に文字列\"%s\"が格納されています\n", s2);
    printf("配列s3に文字列\"%s\"が格納されています\n", s3);
    
    return 0;
}
