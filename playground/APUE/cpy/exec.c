#include <sys/wait.h>
#include "../apue.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};


int main(){
    pid_t pid;

// execle()
    if ((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if (pid == 0){ //子プロセス
        if (execle("/Users/hato/programming/42-CURSUS/code/hello_minishell/playground/APUE/own/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
            err_sys("execle error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");
    
    if ((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if (pid == 0){
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
            err_sys("execlp error");
    }
    exit(0);
}