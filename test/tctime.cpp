/*************************************************************************
    > File Name: tctime.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Thu 23 Feb 2017 05:44:25 PM CST
 ************************************************************************/
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
    time_t timep;
    time(&timep);
    char* p = ctime(&timep);
    char* q = strtok(p, "\n");
    printf("[%s]%x\n", p, p);
    printf("[%s]%x\n", q, q);

return 0;
}
