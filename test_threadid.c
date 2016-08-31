#include "apue.h"
#include <pthread.h>
pthread_t   ntid;

static void pr_ids(const char* str)
{
    pid_t   pid;
    pthread_t   tid;

    pid  = getpid();
    tid = pthread_self();

    printf("%s: pid = %ld, tid = %ld (0x%lx)\n", str, (unsigned long) pid,
            (unsigned long) tid, (unsigned long) tid);
}

static void* func_t(void* arg)
{
    pr_ids("new thread");
    return (void*) 0;
}

int main(int argc, char const *argv[])
{
    int err;

    err = pthread_create(&ntid, NULL, func_t, NULL);
    if(err != 0)
        err_exit(err, "can't create thread");
    pr_ids("main thread");
    sleep(1);

    return 0;
}