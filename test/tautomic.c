/*************************************************************************
  > File Name: tautomic.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Fri 04 Mar 2016 05:24:52 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static int count = 0;


void *test_func(void *arg)
{
    int i=0;
    for(i=0;i<2000;++i){
        
        printf("%d --before\n", count);
        printf("%d ret:\n",  __sync_fetch_and_add(&count,1));
        printf("%d after-- \n", count);
        printf("%d ret2:\n",  __sync_add_and_fetch(&count,1));
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t id[20];
    int i = 0;

    for(i=0;i<20;++i){
        pthread_create(&id[i],NULL,test_func,NULL);
    }

    for(i=0;i<20;++i){
        pthread_join(id[i],NULL);
    }

    printf("%s %d oops,  ", __PRETTY_FUNCTION__, __LINE__);

    printf("%d\n",count);
    return 0;
}
