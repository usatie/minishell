#include "../apue.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

static void sig_int(int sign)
{
    (void)sign;
    printf("caught SIGINT\n");
}

static void sig_chld(int sign)
{
    (void)sign;
    printf("caught SIGCHLD\n");
}

int main(void)
{
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal(SIGINT) error");
    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        err_sys("signal(SIGCHLD) error");
//    if (system("/bin/ed") < 0)
//        err_sys("system() error");
    while(1){
        ;
    }
    exit(0);
}
