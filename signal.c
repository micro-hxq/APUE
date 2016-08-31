#include "apue.h"

static Sigfunc* my_signal(int signo, Sigfunc* func)
{
    struct sigaction act, old_act;

    sigemptyset(&act.sa_mask);
    act.sa_handler = func;
    act.sa_flags = 0;
    if(signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
        act.sa_flags |= SA_RESTART;
    }
    if(sigaction(signo, &act, &old_act) == -1)
        return SIG_ERR;
    return old_act.sa_handler;
}

Sigfunc* Signal(int signo, Sigfunc* func)
{
    Sigfunc* ptr;
    if((ptr = my_signal(signo, func)) == SIG_ERR)
        err_sys("sigaction err_sys");
    return ptr;
}