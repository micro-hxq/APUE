#include "apue.h"
#include <pthread.h>

static void test()
{
    char    buf[128];
    int     err;
    pthread_mutex_t     lock = PTHREAD_MUTEX_INITIALIZER;
    struct timespec     ts;
    struct tm           *ptm;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");

    clock_gettime(CLOCK_REALTIME, &ts);
    ptm = localtime(&ts.tv_sec);
    strftime(buf, sizeof buf, "%r", ptm);
    printf("current time is %s\n", buf);

    ts.tv_sec += 10;
    err = pthread_mutex_timedlock(&lock, &ts);
    clock_gettime(CLOCK_REALTIME, &ts);
    ptm = localtime(&ts.tv_sec);
    strftime(buf, sizeof buf, "%r", ptm);
    printf("now is %s\n", buf);

    if(err == 0)
        printf("mutex lock again\n");
    else
        printf("can't lock mutex again: %s\n", strerror(err));
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}