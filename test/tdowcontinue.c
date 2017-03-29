/*************************************************************************
    > File Name: tdowcontinue.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Fri 13 May 2016 03:01:07 PM CST
 ************************************************************************/

#include <stdio.h>


int main(int argc, char* argv[])
{
    int i = 1;
    printf("i:%d\n", i);
    do {
        printf("haha\n");
        continue;
    }while(--i);

    printf("i:%d\n", i);
    return 0;
}
