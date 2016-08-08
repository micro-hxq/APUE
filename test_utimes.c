#include "apue.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int             fd;
    struct stat     statbuf;
    struct timespec times[2];

    if(argc < 2)
        err_quit("usage: test_utimes <file...>");

    for(int i = 1; i < argc; ++i)
    {
        if(stat(argv[i], &statbuf) < 0)
        {
            err_ret("stat error for %s", argv[i]);
            continue;
        }
        if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)
            err_sys("open error for %s", argv[i]);

        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;

        if(futimens(fd, times) < 0)
            err_ret("futimens for %s", argv[1]);

        close(fd);
    }
    return 0;
}
