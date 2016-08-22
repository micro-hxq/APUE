#include "apue.h"
#include <stdlib.h>

extern char** environ;

static void show_env()
{
    for(char **curenv = environ;*curenv != NULL; ++curenv)
        printf("%s\n", *curenv);
}

int main(int argc, char const *argv[])
{
    show_env();

    printf("login name: %s\n", getlogin());
    return 0;
}