#include "apue.h"

#define BFS 48

int main(int argc, char const *argv[])
{
    char    buf[BFS];
    FILE*   fp;


    memset(buf, 'a', BFS - 2);
    buf[BFS - 2] = '\0';
    buf[BFS - 1] = 'X';

    if((fp = fmemopen(buf, sizeof buf, "w+")) == NULL)
        err_sys("fmemopen error");

    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush:   %s\n", buf);
    fflush(fp);
    printf("after flush:    %s\n", buf);
    printf("length of string %ld\n", (long)strlen(buf));

    memset(buf, 'b', BFS - 2);
    buf[BFS - 2] = '\0';
    buf[BFS - 1] = 'X';
    fprintf(fp, "hello, world");
    printf("\nbefore fseek:     %s\n", buf);
    fseek(fp, 0, SEEK_SET);
    printf("after fseek:      %s\n", buf);
    printf("length of string %ld\n", (long)strlen(buf));

    memset(buf, 'c', BFS - 2);
    buf[BFS - 2] = '\0';
    buf[BFS - 1] = 'X';
    fprintf(fp, "hello, world");
    printf("\nbefore fclose:    %s\n", buf);
    fclose(fp);
    printf("after fclose:     %s\n", buf);
    printf("length of string %ld\n", (long)strlen(buf));

    return 0;
}