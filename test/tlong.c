/*************************************************************************
    > File Name: tlong.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Fri 18 Mar 2016 04:14:24 PM CST
 ************************************************************************/

#include<stdio.h>

void main(int argc, char* argv[])
{
    long long a = 222222222222222112;
    long      b = 222222222222222112;
    printf("%lld\n%ld\n,  %d:%d", a, b, sizeof a ,sizeof b);
}
