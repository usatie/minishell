#include <stdio.h>

int main(void)
{
    printf("sizeof(\"\")           = %u\n", (unsigned)sizeof(""));
    printf("sizeof(\"abc\")        = %u\n", (unsigned)sizeof("abc"));
    printf("sizeof(\"UVW\\0XYZ\")  = %u\n", (unsigned)sizeof("UVW\0XYZ"));

    return 0;
}
