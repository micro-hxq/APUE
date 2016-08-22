#include "apue.h"
#include <shadow.h>

static void show_passwd(const char* username)
{
    struct spwd *ptr;

    if((ptr = getspnam(username)) == NULL)
        err_sys("getspnam error");

    printf("%s password: %s\n", username, ptr->sp_pwdp == NULL || 
            ptr->sp_pwdp[0] == 0 ? ("null") : ptr->sp_pwdp);
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
        err_quit("usage: show_pwd <username>");

    show_passwd(argv[1]);
    
    return 0;
}