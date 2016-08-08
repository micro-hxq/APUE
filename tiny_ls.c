#include "apue.h"
#include <dirent.h>


int main(int argc, char const *argv[])
{
    DIR*            dp;
    struct dirent*  dirp;
    if(argc != 2)
        err_quit("usage: tiny_ls <dir>");
    if((dp = opendir(argv[1])) == NULL)
        err_sys("cannot open %s", argv[1]);
    while((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);
    return 0;
}