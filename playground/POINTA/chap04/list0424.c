#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[8] = "";
    char s2[8] = "ABC";
    char s3[8] = "AB\0CDEF";

    printf("strlen(s1)            = %u\n",(unsigned)strlen(s1));
    printf("strlen(s2)            = %u\n",(unsigned)strlen(s2));
    printf("strlen(&s2[1])        = %u\n",(unsigned)strlen(&s2[1]));
    printf("strlen(s3)            = %u\n",(unsigned)strlen(s3));
    printf("strlen(\"XYZ\")       = %u\n",(unsigned)strlen("XYZ"));
    printf("strlen(&\"XYZ\"[1])   = %u\n",(unsigned)strlen(&"XYZ"[1]));
    printf("strlen(\"ABC\\0DEF\") = %u\n",(unsigned)strlen("ABC\0DEF"));
    printf("sizeof(\"ABC\\0DEF\") = %u\n",(unsigned)sizeof("ABC\0DEF"));

    return 0;
}
