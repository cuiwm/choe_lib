/*************************************************************************
    > File Name: match_ip.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Mon 10 Jul 2017 03:30:51 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdin.h>


int main(int argc, char* argv[])
{
    int mask_len = atoi(argv[1]);

    uint32_t mask = 0xFFFFFFFF << (32 -mask_len);

    printf("mask:%x", mask);

    return 0;
}
