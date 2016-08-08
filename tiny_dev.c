#include "apue.h"
#include <sys/sysmacros.h>

int main(int argc, char const *argv[])
{
    struct stat statbuf;

    for(int i = 1; i < argc; ++i)
    {
        if(stat(argv[i], &statbuf) < 0)
            err_ret("stat error for %s", argv[i]);

        printf("%s: ", argv[i]);
        printf("dev = %d/%d", major(statbuf.st_dev), minor(statbuf.st_dev));

        if(S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode))
        {
            printf(" (%s) rdev = %d/%d", S_ISBLK(statbuf.st_mode) ? "block" : "character",
                    major(statbuf.st_rdev), minor(statbuf.st_rdev));
        }
        putchar('\n');
    }
    return 0;
}