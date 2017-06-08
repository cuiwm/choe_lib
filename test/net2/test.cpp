/*************************************************************************
    > File Name: test.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 24 May 2017 11:41:23 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT printf

void activate_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        ERR_EXIT("fcntl");
    flags |= O_NONBLOCK;
    ret = fcntl(fd, F_SETFL, flags);
    if (ret == -1)
        ERR_EXIT("fcntl");
}


void deactivate_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        ERR_EXIT("fcntl");
    flags &= ~O_NONBLOCK;
    ret = fcntl(fd, F_SETFL, flags);
    if (ret == -1)
        ERR_EXIT("fcntl");
}

char buf[500000];

int main(int argc, const char *argv[])
{
    int ntowrite, nwrite;

    ntowrite = read(STDIN_FILENO, buf, sizeof buf);
    fprintf(stderr, "read %d bytes\n", ntowrite);

    activate_nonblock(STDOUT_FILENO);// O_NONBLOCK);

    char *ptr = buf;
    int nleft = ntowrite; //剩余的字节数
    while(nleft > 0)
    {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, nleft);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if(nwrite > 0)
        {
            ptr += nwrite;
            nleft -= nwrite;
        }
    }

    deactivate_nonblock(STDOUT_FILENO);

    return 0;
}
