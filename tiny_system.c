#include "apue.h"
#include <errno.h>
#include <sys/wait.h>

int my_system(const char* cmd)
{
    pid_t   pid;
    int     status;

    if(cmd == NULL)
        return -1;

    if((pid = fork()) < 0)
        status = -1;
    else if(pid == 0)
    {
        execl("/bin/bash", "bash", "-c", cmd, (char*)0);
        _exit(127);
    }
    else
    {
        while(waitpid(pid, &status, 0) < 0)
        {
            if(errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }
    return status;
}

