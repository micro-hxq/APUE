#include "apue.h"
#include <time.h>
#include <stdio.h>

static void tiny_date()
{
    char        buf[128];
    int         n;
    time_t      t;
    struct tm*  ptr;

    time(&t);
    if((ptr = localtime(&t)) == NULL)
        err_sys("localtime error");

    if((n = strftime(buf, sizeof buf, "%Y年 %m月 %d日 ", ptr)) == 0)
        err_sys("strftime error");

    switch(ptr->tm_wday)
    {
    case 0:
        n += snprintf(buf + n, (sizeof buf) - n, "星期日"); break;
    case 1:
        n += snprintf(buf + n, (sizeof buf) - n, "星期一"); break;
    case 2:
        n += snprintf(buf + n, (sizeof buf) - n, "星期二"); break;
    case 3:
        n += snprintf(buf + n, (sizeof buf) - n, "星期三"); break;
    case 4:
        n += snprintf(buf + n, (sizeof buf) - n, "星期四"); break;
    case 5:
        n += snprintf(buf + n, (sizeof buf) - n, "星期五"); break;
    case 6:
        n += snprintf(buf + n, (sizeof buf) - n, "星期六"); break;
    default :
        n += snprintf(buf + n, (sizeof buf) - n, "error");
    }

    if((n = strftime(buf + n, (sizeof buf) - n, " %T %Z\n", ptr)) == 0)
        err_sys("strftime error");

    fputs(buf, stdout);
}

int main(int argc, char const *argv[])
{
    tiny_date();

    return 0;
}