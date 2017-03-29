/*************************************************************************
    > File Name: tmakestring.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Fri 11 Mar 2016 06:54:17 PM CST
 ************************************************************************/

#include<stdio.h>


#define MAKESTRING(x) #x
#define MAKECHAR(c)  #c

int main (int argc, char* argv[])
{

    int i = 5;
    printf("ha: %c %d = ", MAKECHAR(i), i);
    return 0;
}
