#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../apue.h"

void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP

        WCOREDUMP(status) ? " (code file generated)" : "");
#else
        "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",
            WSTOPSIG(status));
}




int main(){
    pid_t   pid;
    int     status;

    if ((pid = fork()) < 0)
    {
        /*
        puts("fork Error!");
        exit(1);
        */
        err_sys("fork error");
    }
    else if (pid == 0)
        exit(4);

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status /= 0;
    
    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    exit(0);
}