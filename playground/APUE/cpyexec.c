#include <sys/wait.h>
#include "apue.h"
#include <unistd.h>
#include <stdio.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(){
    pid_t pid;


// execle()
    if ((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if (pid == 0){ //子プロセス
        if (execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY_ARG2", (char *)0, env_init) < 0)
            err_sys("execle error");
    }

    printf("%d\n", pid);
}