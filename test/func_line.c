/*************************************************************************
    > File Name: func_line.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Fri 11 Mar 2016 04:37:33 PM CST
 ************************************************************************/

#include<stdio.h>

#define  DBGEXT(fmt, args...)                                       printf("%s:%u "fmt "%s",__PRETTY_FUNCTION__, __LINE__, ##args, __FILE__)

int main(int argc, char* argv[])
{

    DBGEXT("%s %u\n", "haha", 107);

    return 0;
}

