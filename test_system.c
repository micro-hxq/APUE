#include "apue.h"

int main(int argc, char const *argv[])
{
    int status;

    if((status = my_system("date")) < 0)
        err_sys("my_system error");
    print_exit(status);

    if((status = my_system("nosuchcommand")) < 0)
        err_sys("my_system error");
    print_exit(status);

    if((status = my_system("who; exit 44")) < 0)
        err_sys("my_system error");
    print_exit(status);
    return 0;
}