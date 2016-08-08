#include "apue.h"

int main(int argc, char const *argv[])
{
    char*   pathname;
    size_t  size;

    if(argc != 2)
        err_quit("usage: tiny_cd <pathname>");

    if(chdir(argv[1]) < 0)
        err_sys("chdir error");

    pathname = path_alloc(&size);

    if(getcwd(pathname, size) == NULL)
        err_sys("getcwd error");

    printf("cwd: %s\n", pathname);
    
    return 0;
}