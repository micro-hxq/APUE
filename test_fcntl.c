#include "apue.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int val;

    if(argc != 2)
        err_quit("usage: test_fcntl <file_descriptor>");

    if((val = fcntl(atoi(argv[1]), F_GETFD, 0)) < 0)
        err_sys("fcntl error for fd %d", atoi(argv[1]));

    switch(val & O_ACCMODE)
    {
        case O_RDONLY:
            printf("read only");
            break;

        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default :
            err_dump("unknown access mode");
    }

    if(val & O_APPEND)
        printf(", append");
    if(val & O_NONBLOCK)
        printf(", nonblock");
    if(val & O_SYNC);
        printf(", sync write");

# if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if(val & O_FSYNC)
        printf(", fsync write");
# endif

    printf("\n");
    return 0;
}