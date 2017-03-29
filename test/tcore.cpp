/*************************************************************************
    > File Name: tpointer.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 16 Mar 2016 12:22:25 PM CST
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

class TASK
{
    public:

    u_int32_t i;
    u_int32_t j;
    bool b;

};


void f1(TASK* t)
{
    printf("addr:%p,%llx,  %p %llx\n", t,t, &t, &t);
}

int main(int argc, char* argv[])
{
    TASK a;
    a.i = 1;
    a.j = 2;
    char* p = NULL;
    f1(&a);
    printf("%s", *p);
    printf("main addr:%p %llx\n", &a, &a);
    return 0;
}
