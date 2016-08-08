#include "apue.h"

int main(int argc, char const *argv[])
{
    struct stat buf;

    if(argc != 2)
        err_quit("usage: tiny_file <file>");

    if(lstat(argv[1], &buf) < 0)
        err_sys("lstat error for %s", argv[1]);

    if(S_ISREG(buf.st_mode))
        printf("%s is regular file\n", argv[1]);

    else if(S_ISDIR(buf.st_mode))
        printf("%s is directory\n", argv[1]);
    else if(S_ISCHR(buf.st_mode))
        printf("%s is character device", argv[1]);
    else if(S_ISBLK(buf.st_mode))
        printf("%s is block device\n", argv[1]);
    else if(S_ISFIFO(buf.st_mode))
        printf("%s is FIFO\n", argv[1]);
    else if(S_ISLNK(buf.st_mode))
        printf("%s is symbolic link\n", argv[1]);
    else if(S_ISSOCK(buf.st_mode))
        printf("%s is socket\n", argv[1]);
    else
        printf("**unknown file type**");
    
    return 0;
}