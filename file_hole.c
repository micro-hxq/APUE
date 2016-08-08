#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char const *argv[])
{
    int fd;

    if((fd = creat("file.hole", FILE_MODE)) == -1)
        err_sys("creat error");

    if(write(fd, buf1, 10) != 10)    
        err_sys("write buf1 error");

    if(lseek(fd, 1024, SEEK_SET) == -1)
        err_sys("lseek error");

    if(write(fd, buf2, 10) != 10)
        err_sys("write buf2 error");

    close(fd);

    if((fd = creat("file2.hole", FILE_MODE)) == -1)
        err_sys("open error");

    int count = 1034;
    char buf3[] = "x";
    while(count)
    {
        if(write(fd, buf3, 1) != 1)
            err_sys("write buf3 error");
        --count;
    }
    close(fd);
    return 0;
}