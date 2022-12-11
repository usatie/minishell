#include<stdio.h>

int main(void)
{
    printf("文字数リテラル\"abc\"=\"%s\"\n",        "abc");
    printf("文字数リテラル\"UVW\\0WYZ\"=\"%s\"\n",  "UVW\0XYZ");
    
    printf("文字数リテラル\"abc\"は%p番地に格納されています\n","abc");

    return 0;
}
