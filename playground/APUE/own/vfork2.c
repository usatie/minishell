#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int globvar = 6;

int main()
{
    int     var;
    pid_t   pid;

    var = 88;
    // warning : vfork() is deprecated

    printf("before vfork() pid = %d\n",pid);
    pid = vfork();
    printf("after  vfork() pid = %d\n",pid);
    if (pid < 0)
    {
        puts("vfork() Error!");
        exit(1);
    }
    else if (pid == 0)
    {
        puts("\n[child]");
        globvar++;
        var++;
        printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
        _exit(0);
        // Result is indefinite　: exit(0);
    }
    puts("\n[parent]");
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0); // ここでpidのメモリをクリアして、pid=0になるので、子のスレッドに入る
}