/*************************************************************************
    > File Name: treadlink.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Tue 12 Sep 2017 02:27:55 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    char buf[10] = {0};
    ssize_t ret = readlink("/proc/self/exe", buf, sizeof(buf)- 1);
    printf("ret:%ld, readlink return: ", ret);
    printf("ret:%ld, readlink: buf:%s", ret, buf);
    return 0;
}
