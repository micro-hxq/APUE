#include "apue.h"
#include <pthread.h>

static void cleanup(void* arg)
{
    printf("cleanup: %s\n", (char*) arg);
}

static void* thr_f1(void* arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push completed\n");
    if(arg)
        return (void*) 1;
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void*) 1;
}

static void* thr_f2(void* arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    printf("thread 2 push completed\n");
    if(arg)
        pthread_exit((void*) 2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*) 2);
}

int main(int argc, char const *argv[])
{
    int         err;
    pthread_t   tid1, tid2;
    void        *ret;

    err = pthread_create(&tid1, NULL, thr_f1, (void*) 1);
    if(err != 0)
        err_exit(err, "can't create thread 1");
    err = pthread_create(&tid2, NULL, thr_f2, (void*) 2);
    if(err != 0)
        err_exit(err, "can't create thread 2");

    err = pthread_join(tid1, &ret);
    if(err != 0)
        err_exit(err, "can't join with thread 1");
    printf("thread 1 exit code %ld\n", (long) ret);

    err = pthread_join(tid2, &ret);
    if(err != 0)
        err_exit(err, "can't join with thread 2");
    printf("thread 2 exit code %ld\n", (long) ret);

    return 0;
}