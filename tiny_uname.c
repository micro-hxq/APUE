#include "apue.h"

#include <sys/utsname.h>

static void get_uname()
{
    struct utsname info;

    if(uname(&info) == -1)
        err_sys("uname error");

    if(info.sysname[0] != '\0')
        printf("system name: %s\n", info.sysname);

    if(info.nodename[0] != '\0')
        printf("node   name: %s\n", info.nodename);

    if(info.release[0] != '\0')
        printf("release:     %s\n", info.release);

    if(info.version[0] != '\0')
        printf("version:     %s\n", info.version);

    if(info.machine[0] != '\0')
        printf("machine:     %s\n", info.machine);
}

int main(int argc, char const *argv[])
{
    get_uname();

    return 0;
}
