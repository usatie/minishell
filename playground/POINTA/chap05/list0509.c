#include <stdio.h>

int main(int argc, char **argv)
{
    int i = 0;

    while (argc-- > 0)
        printf("argv[%d] = \"%s\"\n", i++, *argv++);

    return 0;
}
