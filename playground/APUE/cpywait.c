#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "apue.h"


int main()
{
    pid_t pid;

    if((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if(pid == 0){
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            exit(0);

        // 上の文で実の親がexit()を呼ぶと、init が親になる？？？
        // >> init は全てのプロセスの親である。 "/etc/inittab"

        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid()); //　= 最初の子
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");

    exit(0);
}