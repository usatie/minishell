#include <sys/wait.h>
#include "../apue.h"
#include <stdlib.h>
#include <unistd.h>


int main(){
    pid_t pid;


    if ((pid = fork()) < 0){
        err_sys("fork_error");
    }

    else if (pid == 0){
        if (execl("/Users/hato/programming/42-CURSUS/code/hello_minishell/playground/APUE/bin/testinterp", "testinterp", "myarg1", "MYARG2", (char *)0) < 0){
            err_sys("execel error");
        }
    }
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid error");
    exit(0);
}

