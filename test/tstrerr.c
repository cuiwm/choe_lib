/*************************************************************************
    > File Name: tstrerr.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Fri 13 May 2016 03:56:55 PM CST
 ************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(int argc, char* argv[])
{
    char buf[256] = {0};
    char *err_desc = strerror_r(EINTR, buf, sizeof(buf));
    printf("buf:%s ret_ptr:%s", buf, err_desc); 
    return 0;
}
