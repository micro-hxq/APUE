#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main(int argc, char const *argv[])
{
    pid_t       pid;
    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        if(execle("/home/hxq/Document/APUE/exec/echoall", "echoall", "arg1", "arg2",
                  (char*)0, env_init) == -1)
            err_sys("execle error");
    }

    if(waitpid(pid, NULL, 0) == -1)
        err_sys("waitpid error");

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        if(execl("/home/hxq/Document/APUE/exec/echoall", "echoall", "arg1", "arg2",
                (char*)0) == -1)
            err_sys("execl error");
    }

    return 0;
}
