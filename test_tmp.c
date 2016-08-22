#include "apue.h"
#include <errno.h>

static void creat_tmp(char* filename);

int main(int argc, char const *argv[])
{
    char tmp_name1[] = "/tmp/tempXXXXXX";
    char tmp_name2[] = "/tmp/temXXXXXXX";

    printf("trying to creat the first temp file...\n");
    creat_tmp(tmp_name1);
    printf("trying to creat the second temp file...\n");
    creat_tmp(tmp_name2);

    return 0;
}


static void creat_tmp(char* temp)
{
    int fd;
    struct stat buf;

    if((fd = mkstemp(temp)) == -1)
        err_sys("can't creat temp file");
    printf("temp name = %s\n", temp);
    close(fd);
    if(stat(temp, &buf) < 0)
    {
        if(errno == ENOENT)
            printf("file doesn't exist\n");
        else
            err_sys("stat error");
    }
    else
    {
        printf("file exist\n");
        sleep(10);
        unlink(temp);
    }
}