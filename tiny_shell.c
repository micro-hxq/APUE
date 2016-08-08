#include "apue.h"
#include <sys/wait.h>

void sig_int(int signo)
{
    printf("interrupt\n%%");
}

int main(int argc, char const *argv[])
{
    char        buf[MAXLINE];
    pid_t       pid;
    int         statno;

    if(signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");

    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if(pid == 0)
        {
            execlp(buf, buf, (char*) NULL);
            err_ret("can't execute %s", buf);
            exit(127);
        }

        if((pid = waitpid(pid, &statno, 0)) < 0)
            err_sys("waitpid error");

        printf("%% ");
    }
    printf("\n");
    return 0;
}