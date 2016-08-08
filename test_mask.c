#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)


int main(int argc, char const *argv[])
{
    umask(0);
    if(creat("./exec/foo.txt", RWRWRW) < 0)
        err_sys("creat foo.txt error");

    umask(066);

    if(creat("./exec/bar.txt", RWRWRW) < 0)
        err_sys("creat bar.txt error");

    return 0;
}