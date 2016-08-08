#include "apue.h"

int main(int argc, char const *argv[])
{
    struct stat statbuf;

    if(stat("./exec/foo.txt", &statbuf) < 0)
        err_sys("stat for foo.txt error");

    if(chmod("./exec/foo.txt", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("chmod error for foo.txt");

    if(chmod("./exec/bar.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        err_sys("chmod error for bar.txt");

    return 0;
}