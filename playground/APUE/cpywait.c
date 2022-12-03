#include <sys/wait.h>

int main()
{
    pid_t pid;

    if((pid = fork()) < 0){
        err_sys("fork error");
    }
}