/*************************************************************************
  > File Name: set_thread_name.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Wed 09 Mar 2016 10:19:07 AM CST
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <string>
#include <unistd.h>

using namespace std;

string   g_thread_name("mytheadname");


void *foo(void *arg)
{
    int idx = (long)arg;
    printf("idx = %d\n", idx);
    switch(idx)
    {
        case 1:
            prctl(PR_SET_NAME, g_thread_name.c_str());
            break;
        case 2:
            prctl(PR_SET_NAME, "ThreadName2");
            break;
        case 3:
            prctl(PR_SET_NAME, "ThreadName3");
            break;
        default:
            break;
    }

    sleep(50);
    return 0;
}

int main(void)
{
    pthread_t threadIdx[3];
    int threadArgIdx[] = {1, 2, 3};

    int i;
    for(i = 0; i < 3; i++)
    {
        pthread_create(threadIdx + i, NULL, foo, (void *)threadArgIdx[i]);
    }

    for(i = 0; i < 3; i++)
    {
        pthread_join(threadIdx[i], NULL);
    }
    return 0;
}
