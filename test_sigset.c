#include "apue.h"

static void quit_handler(int signo)
{
    printf("SIGQUIT handler\n");
    Signal(SIGQUIT, SIG_DFL);
}

static void test()
{
    sigset_t newset, oldset, pendingset;

    Signal(SIGQUIT, quit_handler);

    sigemptyset(&newset);
    sigaddset(&newset, SIGQUIT);
    printf("Blocking SIGQUIT\n");
    if(sigprocmask(SIG_BLOCK, &newset, &oldset) == -1)
        err_sys("sigprocmask error");
    sleep(5);

    if(sigpending(&pendingset) == -1)
        err_sys("sigpending error");
    if(sigismember(&pendingset, SIGQUIT))
        printf("Pending SIGQUIT\n");

    if(sigprocmask(SIG_SETMASK, &oldset, NULL) == -1)
        err_sys("sigprocmask error");
    printf("Unblocking SIGQUIT\n");

    sleep(5);
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}