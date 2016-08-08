#include "apue.h"
#include <dirent.h>
#include <limits.h>

#define FTW_F   1
#define FTW_D   2
#define FTW_DNR 3
#define FTW_NS  4

typedef int Func(const char*, const struct stat*, int);

static Func     myfunc;
static int      myftw(char*, Func*);
static int      dopath(Func*);
static long     nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char const *argv[])
{
    int ret;

    if(argc != 2)
        err_quit("usage: tiny_ftw <dir>");

    ret = myftw(argv[1], myfunc);

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if(ntot == 0)
        ntot = 1;

    printf("regular file    = %7ld, %5.2f%%\n", nreg, 100.0*nreg / ntot);
    printf("directory file  = %7ld, %5.2f%%\n", ndir, 100.0*ndir / ntot);
    printf("block special   = %7ld, %5.2f%%\n", nblk, 100.0*nblk / ntot);
    printf("char special    = %7ld, %5.2f%%\n", nchr, 100.0*nchr / ntot);
    printf("FIFOs           = %7ld, %5.2f%%\n", nfifo, 100.0*nfifo / ntot);
    printf("symbolic links  = %7ld, %5.2f%%\n", nslink, 100.0*nslink / ntot);
    printf("sockets         = %7ld, %5.2f%%\n", nsock, 100.0*nsock / ntot);

    return ret;
}

static char*    fullpath;
static size_t   pathlen;

static int myftw(char* pathname, Func* func)
{
    fullpath = path_alloc(&pathlen);
    if(pathlen <= strlen(pathname))
    {
        pathlen = strlen(pathname) * 2;
        if((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc error");
    }
    strcpy(fullpath, pathname);
    return dopath(func);
}

static int dopath(Func* func)
{
    struct stat     statbuf;
    struct dirent   *dirp;
    DIR             *dp;
    int             ret, n;

    if(lstat(fullpath, &statbuf) < 0)
        return func(fullpath, &statbuf, FTW_NS);

    if(S_ISDIR(statbuf.st_mode) == 0)
        return func(fullpath, &statbuf, FTW_F);

    if((ret = func(fullpath, &statbuf, FTW_D)) != 0)
        return ret;
    n = strlen(fullpath);

    if(n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc error");
    }

    fullpath[n++] = '/';
    fullpath[n] = 0;

    if((dp = opendir(fullpath)) == NULL)
        return func(fullpath, &statbuf, FTW_DNR);

    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        strcpy(fullpath + n, dirp->d_name);

        if((ret = dopath(func)) != 0)
            break;
    }

    fullpath[n - 1] = 0;
    if(closedir(dp) < 0)
        err_ret("can't close directory %s", fullpath);

    return ret;
}

static int myfunc(const char* pathname, const struct stat* statptr, int type)
{
    switch(type)
    {
    case FTW_F:
        switch(statptr->st_mode & S_IFMT)
        {
        case S_IFREG:   ++nreg;     break;
        case S_IFBLK:   ++nblk;     break;
        case S_IFCHR:   ++nchr;     break;
        case S_IFIFO:   ++nfifo;    break;
        case S_IFLNK:   ++nslink;   break;
        case S_IFSOCK:  ++nsock;    break;
        case S_IFDIR:   err_dump("S_IFDIR for %s", pathname);
        }
        break;
    case FTW_D:
        ++ndir;
        break;
    case FTW_NS:
        err_ret("stat error for %s", pathname);
        break;
    case FTW_DNR:
        err_ret("can't read directory %s", pathname);
        break;
    default :
        err_dump("unknown type %d for pathname %s", type, pathname);
    }

    return 0;
}