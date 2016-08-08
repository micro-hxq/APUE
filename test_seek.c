#include "apue.h"
int main(int argc, char const *argv[])
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("seek ok\n");
    else
        printf("cannot seek\n");
    
    return 0;
}