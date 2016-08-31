#include "apue.h"

static void sig_handler(int signo)
{
    if(signo == SIGUSR1)
        printf("receive SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("receive SIGUSR2\n");
    else
        err_dump("receive signal %d", signo);
}

static void test()
{
    if(signal(SIGUSR1, sig_handler) == SIG_ERR)
        err_sys("can't catch SIGUSR1");
    if(signal(SIGUSR2, sig_handler) == SIG_ERR)
        err_sys("can't catch SIGUSR2");
    while(1)
        pause();
}

int main(int argc, char const *argv[])
{
    test();
    
    return 0;
}