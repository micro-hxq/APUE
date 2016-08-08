#include "apue.h"

#define BUFSIZE     16

int main(int argc, char const *argv[])
{
    char buf[BUFSIZE];
    int n;

    printf("process id: %d\n", getpid());
    printf("user id: %d, group id: %d\n", getuid(), getgid());
    while((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
    {
        if(write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    }
    if(n < 0)
        err_sys("read error");

    return 0;
}
