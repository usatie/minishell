#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int globvar = 6;

int main()
{
    int     var;
    pid_t   pid;

    var = 88;
    puts("before vfolk");
    // warning : vfork() od deprevated
    if ((pid = vfork()) < 0)
    {
        puts("vfork() Error!");
        exit(1);
    }
    else if (pid == 0)
    {
        globvar++;
        var++;
        _exit(0);
        // Result is indefinite　: exit(0);
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}