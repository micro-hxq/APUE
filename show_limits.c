#include "apue.h"
#include <sys/resource.h>

#define PRINT(name)     print_limits(#name, name)

static void print_limits(char* name, int resource)
{
    struct rlimit       limit;
    unsigned long long  lim;

    if(getrlimit(resource, &limit) != 0)
        err_sys("getrlimit error");
    printf("%-18s   ", name);
    if(limit.rlim_cur == RLIM_INFINITY)
        printf("(Infinite)  ");
    else
    {
        lim = limit.rlim_cur;
        printf("%10lld  ", lim);
    }

    if(limit.rlim_max == RLIM_INFINITY)
        printf("(Infinite)");
    else
    {
        lim = limit.rlim_max;
        printf("%10lld  ", lim);
    }

    putchar('\n');
}

static void show_limits()
{
#ifdef  RLIMIT_AS
    PRINT(RLIMIT_AS);
#endif

    PRINT(RLIMIT_CORE);
    PRINT(RLIMIT_CPU);
    PRINT(RLIMIT_DATA);
    PRINT(RLIMIT_FSIZE);

#ifdef  RLIMIT_MEMLOCK
    PRINT(RLIMIT_MEMLOCK);
#endif

#ifdef  RLIMIT_MSGQUEUE
    PRINT(RLIMIT_MSGQUEUE);
#endif

#ifdef  RLIMIT_NICE
    PRINT(RLIMIT_NICE);
#endif

    PRINT(RLIMIT_NOFILE);

#ifdef  RLIMIT_NPROC
    PRINT(RLIMIT_NPROC);
#endif

#ifdef  RLIMIT_NPTS
    PRINT(RLIMIT_NPTS);
#endif

#ifdef  RLIMIT_RSS
    PRINT(RLIMIT_RSS);
#endif

#ifdef  RLIMIT_SBSIZE
    PRINT(RLIMIT_SBSIZE);
#endif

#ifdef  RLIMIT_SIGPENDING
    PRINT(RLIMIT_SIGPENDING);
#endif

    PRINT(RLIMIT_STACK);

#ifdef  RLIMIT_SWAP
    PRINT(RLIMIT_SWAP);
#endif

#ifdef  RLIMIT_VMEM
    PRINT(RLIMIT_VMEM);
#endif
}

int main(int argc, char const *argv[])
{
    show_limits();

    return 0;
}